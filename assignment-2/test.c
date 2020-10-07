#include "test.h"
#include <stdio.h>
#include <time.h>
#include <sys/socket.h>
#include <string.h>

/***** CONSTANTS *****/

#define MESSAGES_PER_TEST 100
#define TESTS_PER_SIZE 3
#define MESSAGE_MAX_SIZE 32768

/***** FUNCTIONS SIGNATURES *****/

void run_test_a(int sock, char *filename);

void run_test_b(int sock, char *filename);

// RTT is calculated in ms and throughput in bits/s
void run_test(
    int sock,
    int *message_sizes,
    int n_messages,
    double rtt_matrix[][TESTS_PER_SIZE],
    double throughput_matrix[][TESTS_PER_SIZE]);

void print_result_on_file(
    char *filename,
    int *message_sizes,
    int n_messages,
    double result_matrix[][TESTS_PER_SIZE]);

void generate_n_bytes_string(int size, char *string);

double convert_seconds_to_ms(double n);

int convert_bytes_to_bits(int n);

int convert_kbytes_to_bytes(int n);

/***** FUNCTIONS DEFINITION *****/

void run_test_a(int sock, char *filename)
{
    int message_sizes[] = {2, 10, 50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
    int n_messages = sizeof(message_sizes) / sizeof(message_sizes[0]);

    double rtt_matrix[n_messages][TESTS_PER_SIZE];
    double throughput_matrix[n_messages][TESTS_PER_SIZE];

    run_test(sock, message_sizes, n_messages, rtt_matrix, throughput_matrix);

    print_result_on_file(filename, message_sizes, n_messages, rtt_matrix);

    return;
}

void run_test_b(int sock, char *filename)
{
    int message_sizes[] = {2, 10, 50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
    int n_messages = sizeof(message_sizes) / sizeof(message_sizes[0]);

    double rtt_matrix[n_messages][TESTS_PER_SIZE];
    double throughput_matrix[n_messages][TESTS_PER_SIZE];

    run_test(sock, message_sizes, n_messages, rtt_matrix, throughput_matrix);

    print_result_on_file(filename, message_sizes, n_messages, throughput_matrix);

    return;
}

void run_test(
    int sock,
    int *message_sizes,
    int n_messages,
    double rtt_matrix[][TESTS_PER_SIZE],
    double throughput_matrix[][TESTS_PER_SIZE])
{
    char buffer[MESSAGE_MAX_SIZE];
    int buffer_length;

    clock_t begin;
    clock_t end;

    char test_message[MESSAGE_MAX_SIZE];

    for (int size_index = 0; size_index < n_messages; size_index++)
    {
        int size = message_sizes[size_index];
        generate_n_bytes_string(size, test_message);

        for (int test_index = 0; test_index < TESTS_PER_SIZE; test_index++)
        {
            begin = clock();

            for (int counter = 0; counter < MESSAGES_PER_TEST; counter++)
            {
                strcpy(buffer, test_message);
                buffer_length = strlen(buffer);
                send(sock, buffer, buffer_length, 0);
                char recv_buf[MESSAGE_MAX_SIZE];
                recv(sock, recv_buf, sizeof(recv_buf), 0);
            }

            end = clock();
            double total_time_in_seconds = (double)(end - begin) / CLOCKS_PER_SEC;

            double rtt = convert_seconds_to_ms(total_time_in_seconds) / MESSAGES_PER_TEST;
            rtt_matrix[size_index][test_index] = rtt;

            double throughput = convert_bytes_to_bits(size) / total_time_in_seconds;
            throughput_matrix[size_index][test_index] = throughput;
        }
    }

    return;
}

void print_result_on_file(
    char *filename,
    int *message_sizes,
    int n_messages,
    double result_matrix[][TESTS_PER_SIZE])
{
    FILE *file_pointer;
    file_pointer = fopen(filename, "w");

    for (int size_index = 0; size_index < n_messages; size_index++)
    {
        fprintf(file_pointer, "%d", message_sizes[size_index]);

        for (int test_index = 0; test_index < TESTS_PER_SIZE; test_index++)
        {
            fprintf(file_pointer, ",%f", result_matrix[size_index][test_index]);
        }

        fprintf(file_pointer, "\n");
    }

    fclose(file_pointer);

    return;
}

void generate_n_bytes_string(int n, char *string)
{
    // In C, one char has 1 byte, so a n-bytes string is a string with n char
    for (int i = 0; i < n - 1; i++)
    {
        string[i] = 'o';
    }

    // End char must be null
    string[n - 1] = '\0';
    return;
}

double convert_seconds_to_ms(double n)
{
    return n * 1000;
}

int convert_bytes_to_bits(int n)
{
    return n * 8;
}

int convert_kbytes_to_bytes(int n)
{
    return n * 1024;
}
