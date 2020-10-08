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

int main() {
  struct sockaddr_in server_addr, client_addr;
  int sock_file_descriptor;

  bzero((char *)&server_addr, sizeof(server_addr));
  bzero((char *)&client_addr, sizeof(client_addr));

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(SERVER_PORT);

  if ((sock_file_descriptor = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("error on socket");
    exit(1);
  }

  if ((bind(sock_file_descriptor, (struct sockaddr *)&server_addr, sizeof(server_addr))) < 0) {
    perror("error on bind");
    exit(1);
  }

  unsigned int len, n;
  char buf[MESSAGE_MAX_SIZE];

  len = sizeof(client_addr);

  while (1) {
    while ((n = recvfrom(sock_file_descriptor, buf, sizeof(buf), 0,
                         (struct sockaddr *)&client_addr, &len))) {

      sendto(sock_file_descriptor, buf, strlen(buf), 0, (const struct sockaddr *)&client_addr,
             len);
    }
    close(sock_file_descriptor);
  }
}