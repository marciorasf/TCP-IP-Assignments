#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>  // function exit is declared on this lib
#include <string.h>  // function strlen is declared on this lib
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>  // function close is declared on this lib

#include "test.h"

#define SERVER_PORT 54321

int main(int argc, char *argv[]) {
  int sock;
  char *host;
  struct sockaddr_in server_addr;

  if (argc == 2) {
    host = argv[1];
  } else {
    fprintf(stderr, "usage: simplex-talk host\n");
    exit(1);
  }

  server_addr.sin_family = AF_INET;
  inet_aton(host, &server_addr.sin_addr);
  server_addr.sin_port = htons(SERVER_PORT);

  if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("error on socket");
    exit(1);
  }

  char buf[MESSAGE_MAX_SIZE];
  unsigned int len, n;

  while (fgets(buf, sizeof(buf), stdin)) {
    sendto(sock, buf, sizeof(buf), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

    recvfrom(sock, buf, strlen(buf), 0, (struct sockaddr *)&server_addr, &len);

    fputs(buf, stdout);
  }

  // run_test_a(sock, &server_addr, "test_a_rtt_in_ms.csv");
  // run_test_b(sock, &server_addr, "test_b_throughput_in_bits_per_second.csv");
}