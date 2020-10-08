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
#define MAX_LINE 256

int main(int argc, char *argv[]) {
  struct sockaddr_in sin;
  char *host;
  int sock;

  if (argc == 2) {
    host = argv[1];
  } else {
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
  if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    perror("simplex-talk: socket");
    exit(1);
  }
  if (connect(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
    perror("simplex-talk: connect");
    close(sock);
    exit(1);
  }

  run_test_a(sock, "test_a_rtt_in_ms.csv");
  run_test_b(sock, "test_b_throughput_in_bits_per_second.csv");
}