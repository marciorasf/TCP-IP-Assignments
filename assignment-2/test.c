#include "test.h"

#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>

/********** FUNCTIONS SIGNATURES **********/
// RTT is calculated in ms and throughput in bits/s

void run_test(int sock, struct sockaddr_in *server_addr, int *message_sizes,
              int n_messages, double latency_matrix[][TESTS_PER_SIZE],
              double throughput_matrix[][TESTS_PER_SIZE]);

void print_result_on_file(char *filename, int *message_sizes, int n_messages,
                          double result_matrix[][TESTS_PER_SIZE]);

/*
 * The functions below are just auxiliary, and the name describes what they do
 */
void generate_n_bytes_string(int size, char *string);

double convert_seconds_to_ms(double n);

int convert_bytes_to_bits(int n);

int convert_kbytes_to_bytes(int n);

void print_result_on_file(char *filename, int *message_sizes, int n_messages,
                          double result_matrix[][TESTS_PER_SIZE]);

/********** FUNCTIONS DEFINITIONS **********/
void run_test_a(int sock, struct sockaddr_in *server_addr, char *filename) {
  // Define messages to use on test
  int message_sizes[] = {2, 10, 25, 50, 75, 100, 150, 200, 250, 300, 350, 400, 450,
                         500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000};
  int n_messages = sizeof(message_sizes) / sizeof(message_sizes[0]);

  // Declare matrices to store results 
  double latency_matrix[n_messages][TESTS_PER_SIZE];
  double throughput_matrix[n_messages][TESTS_PER_SIZE];

  run_test(sock, server_addr, message_sizes, n_messages, latency_matrix,
           throughput_matrix);

  print_result_on_file(filename, message_sizes, n_messages, latency_matrix);

  return;
}

void run_test_b(int sock, struct sockaddr_in *server_addr, char *filename) {
  int n_messages = 32;
  int message_sizes[n_messages];

  // Generate messages to use on test
  for (int i = 0; i < n_messages; i++) {
    message_sizes[i] = convert_kbytes_to_bytes(i + 1);
  }

  // Declare matrices to store results 
  double latency_matrix[n_messages][TESTS_PER_SIZE];
  double throughput_matrix[n_messages][TESTS_PER_SIZE];

  run_test(sock, server_addr, message_sizes, n_messages, latency_matrix,
           throughput_matrix);

  print_result_on_file(filename, message_sizes, n_messages, throughput_matrix);

  return;
}

void run_test(int sock, struct sockaddr_in *server_addr, int *message_sizes,
              int n_messages, double latency_matrix[][TESTS_PER_SIZE],
              double throughput_matrix[][TESTS_PER_SIZE]) {

  clock_t begin;
  clock_t end;

  int size;
  unsigned int len;
  char message[MESSAGE_MAX_SIZE];
  char buffer[MESSAGE_MAX_SIZE];

  // Run tests for every message size
  for (int size_index = 0; size_index < n_messages; size_index++) {
    size = message_sizes[size_index];
    generate_n_bytes_string(size, message);


    // Run the test TEST_PER_SIZE times
    for (int test_index = 0; test_index < TESTS_PER_SIZE; test_index++) {
      // Get the the start time
      begin = clock();

      // Send MESSAGES_PER_TEST messages, always waiting for the server answer,
      // before sending another message
      for (int counter = 0; counter < MESSAGES_PER_TEST; counter++) {
        sendto(sock, message, size, 0, (struct sockaddr *)server_addr,
               sizeof(*server_addr));

        recvfrom(sock, buffer, sizeof(buffer), 0,
                 (struct sockaddr *)server_addr, &len);
      }

      // Get the end time
      end = clock();

      // The time is got in clocks, so is necessary to convert to seconds
      double total_time_in_seconds = (double)(end - begin) / CLOCKS_PER_SEC;

      // Calculate the metrics and save on the matrix
      double rtt =
          convert_seconds_to_ms(total_time_in_seconds) / MESSAGES_PER_TEST;
      latency_matrix[size_index][test_index] = rtt;

      double throughput = convert_bytes_to_bits(size) / total_time_in_seconds;
      throughput_matrix[size_index][test_index] = throughput;
    }

    printf("Finished test for message of size = %d\n", size);
  }

  printf("\n ---------------------------------------------------------\n");

  return;
}

void generate_n_bytes_string(int n, char *string) {
  // In C, one char has 1 byte, so a n-bytes string is a string with n char
  for (int i = 0; i < n - 1; i++) {
    string[i] = 'o';
  }

  // End char must be null
  string[n - 1] = '\0';
  return;
}

double convert_seconds_to_ms(double n) { return n * 1000; }

int convert_bytes_to_bits(int n) { return n * 8; }

int convert_kbytes_to_bytes(int n) { return n * 1024; }

void print_result_on_file(char *filename, int *message_sizes, int n_messages,
                          double result_matrix[][TESTS_PER_SIZE]) {
  FILE *file_pointer;
  file_pointer = fopen(filename, "w");

  for (int size_index = 0; size_index < n_messages; size_index++) {
    fprintf(file_pointer, "%d", message_sizes[size_index]);

    for (int test_index = 0; test_index < TESTS_PER_SIZE; test_index++) {
      fprintf(file_pointer, ",%f", result_matrix[size_index][test_index]);
    }

    fprintf(file_pointer, "\n");
  }

  fclose(file_pointer);

  return;
}