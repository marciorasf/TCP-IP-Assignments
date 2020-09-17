#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h> // function exit is declared on this lib
#include <unistd.h> // function close is declared on this lib
#include <string.h> // function strlen is declared on this lib

#define SERVER_PORT 54321
#define MAX_LINE 256

int main() {
    struct sockaddr_in sin;
    char buf[MAX_LINE];
    unsigned int len; 
    int s;

    /* build address data structure */
    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(SERVER_PORT);

    /* setup passive open */
    if ((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("simplex-talk: socket");
        exit(1);
    }
    if ((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
        perror("simplex-talk: bind");
        exit(1);
    }

    /* wait for connection, then receive and print text */
    while (1) {
        while ((len = recv(s, buf, sizeof(buf), 0))) {
            fputs(buf, stdout);
        }
        close(s);
    }
}