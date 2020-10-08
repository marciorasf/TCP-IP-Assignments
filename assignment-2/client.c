#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "test.h"

#define SERVER_PORT 54321

int main(int argc, char *argv[]) {
  int sock;
  char *host;
  struct sockaddr_in server_addr;

  // Get host from program input
  if (argc == 2) {
    host = argv[1];
  } else {
    fprintf(stderr, "host not provided\n");
    exit(1);
  }

  // Fill server_addr fields
  server_addr.sin_family = AF_INET;
  inet_aton(host, &server_addr.sin_addr);
  server_addr.sin_port = htons(SERVER_PORT);

  // Create UDP socket file descriptor
  if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("error on socket");
    exit(1);
  }

  char buf[MESSAGE_MAX_SIZE];
  unsigned int len, n;

  /*
  * The code below is used to manual tests
  * To use it, uncomment it and comment the 2 run_test calls
  */ 

  // while (fgets(buf, sizeof(buf), stdin)) {
  //   sendto(sock, buf, sizeof(buf), 0, (struct sockaddr *)&server_addr,
  //   sizeof(server_addr));

  //   recvfrom(sock, buf, strlen(buf), 0, (struct sockaddr *)&server_addr,
  //   &len);

  //   fputs(buf, stdout);
  // }

  // Run automated tests
  // These functions run the book's tests and save results on csv files
  run_test_a(sock, &server_addr, "test_a_rtt_in_ms.csv");
  run_test_b(sock, &server_addr, "test_b_throughput_in_bits_per_second.csv");
}