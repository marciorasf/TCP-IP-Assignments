#include "test.h"
#include <stdio.h>
#include <time.h>
#include <sys/socket.h>
#include <string.h>

#define N_MESSAGES 100
#define TESTS_PER_SIZE 3
#define MESSAGE_MAX_SIZE 1000

void generate_n_bytes_string(int n, char *string);

void run_test_a(int sock, char *filename)
{
    char buf[MESSAGE_MAX_SIZE];
    int len;

    int message_sizes[] = {2, 10, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
    int n_tests = sizeof(message_sizes) / sizeof(message_sizes[0]);

    FILE *file_pointer;
    file_pointer = fopen(filename, "w");

    clock_t begin;
    clock_t end;

    char test_message[MESSAGE_MAX_SIZE];

    for (int size_index = 0; size_index < n_tests; size_index++)
    {
        int size = message_sizes[size_index];
        fprintf(file_pointer, "%d,", size);
        generate_n_bytes_string(size, test_message);

        for (int i = 0; i < TESTS_PER_SIZE; i++)
        {
            begin = clock();

            for (int counter = 0; counter < N_MESSAGES; counter++)
            {
                strcpy(buf, test_message);
                len = strlen(buf);
                send(sock, buf, len, 0);
                char recv_buf[MESSAGE_MAX_SIZE];
                recv(sock, recv_buf, sizeof(recv_buf), 0);
            }

            end = clock();
            float rtt = (float)(end - begin) / (TESTS_PER_SIZE);
            fprintf(file_pointer, "%.1f,", rtt);
        }

        fprintf(file_pointer, "\n");
    }

    fclose(file_pointer);
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