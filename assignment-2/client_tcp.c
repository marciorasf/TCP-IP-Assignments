#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdlib.h> // function exit is declared on this lib
#include <unistd.h> // function close is declared on this lib
#include <string.h> // function strlen is declared on this lib
#include <time.h>   //used to calculate tests time

#define SERVER_PORT 54321
#define MAX_LINE 256
#define N_MESSAGES 10
#define TESTS_PER_SIZE 3
#define MESSAGE_MAX_SIZE 100

void generate_n_bytes_string(int n, char *string);

int main(int argc, char *argv[])
{
    struct sockaddr_in sin;
    char *host;
    char buf[MAX_LINE];
    int s;
    int len;

    if (argc == 2)
    {
        host = argv[1];
    }
    else
    {
        fprintf(stderr, "usage: simplex-talk host\n");
        exit(1);
    }

    /* build address data structure */
    bzero((char *)&sin, sizeof(sin));

    sin.sin_family = AF_INET;

    /* parse dotted IP to in_addr_t format and assign to sin.sin_addr */
    inet_aton(host, &sin.sin_addr);

    sin.sin_port = htons(SERVER_PORT);

    /* active open */
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("simplex-talk: socket");
        exit(1);
    }
    if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("simplex-talk: connect");
        close(s);
        exit(1);
    }

    /*----------------------------------------------------------------
    * Tests
    */
    FILE *file_pointer;

    clock_t begin;
    clock_t end;

    char test_message[MESSAGE_MAX_SIZE];

    /* ---------------------------------
    * Test 1
    */

    printf("Beggining test 1\n\n");

    file_pointer = fopen("test1_tcp.txt", "w");

    for (int size = 10; size < 100; size += 10)
    {
        printf("%d,", size);
        fprintf(file_pointer, "%d,", size);

        generate_n_bytes_string(size, test_message);

        for (int i = 0; i < TESTS_PER_SIZE; i++)
        {
            begin = clock();

            for (int counter = 0; counter < N_MESSAGES; counter++)
            {
                strcpy(buf, test_message);
                len = strlen(buf);
                send(s, buf, len, 0);
                char recv_buf[MAX_LINE];
                recv(s, recv_buf, sizeof(recv_buf), 0);
            }

            end = clock();

            float rtt = (float) (end-begin) / (TESTS_PER_SIZE);
            printf("%.1f,", rtt);
            fprintf(file_pointer, "%.1f,", rtt);
        }

        printf("\n");
        fprintf(file_pointer, "\n");
    }

    fclose(file_pointer);

    printf("\nEnding test 1\n\n");

    return 0;
}

void generate_n_bytes_string(int n, char *string)
{
    // In C, one char has 1 byte, so a n-bytes string is a string with n char
    for (int i = 0; i < n - 1; i++)
    {
        string[i] = 'm';
    }

    string[n - 1] = '\0';
    return;
}