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

int main() {
  struct sockaddr_in server_addr, client_addr;
  int sock;

  // Clean the memory of the sockaddr_in variable
  bzero((char *)&server_addr, sizeof(server_addr));
  bzero((char *)&client_addr, sizeof(client_addr));

  // Fill server_addr data
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(SERVER_PORT);

  // Create socket file descriptor
  if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("error on socket");
    exit(1);
  }

  // Bind the socket with the server address
  if ((bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr))) < 0) {
    perror("error on bind");
    exit(1);
  }

  // Declare variables used to receive and send data
  unsigned int len, n;
  char buf[MESSAGE_MAX_SIZE];

  len = sizeof(client_addr);

  // Loop that maintain the program running
  while (1) {
    /*
     * Receive the data from the client
     * Note that the client address is also saved
     * This address is essential to send the message back
     */
    while ((n = recvfrom(sock, buf, sizeof(buf), 0,
                         (struct sockaddr *)&client_addr, &len))) {
      // Send the received message to the client
      sendto(sock, buf, strlen(buf), 0, (const struct sockaddr *)&client_addr,
             len);
    }

    close(sock);
  }
}