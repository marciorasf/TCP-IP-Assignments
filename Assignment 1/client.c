#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <stdlib.h> // function exit is declared on this lib
#include <unistd.h> // function close is declared on this lib
#include <string.h> // function strlen is declared on this lib

#define h_addr h_addr_list[0] /* for backward compatibility */
#define SERVER_PORT 54321
#define MAX_LINE 256

int main(int argc, char *argv[]) {
    struct sockaddr_in sin;
    char buf[MAX_LINE];
    int s;
    int len;
    char *host;

    if (argc == 2) {
        host = argv[1];
    }
    else {
        fprintf(stderr, "usage: simplex-talk host\n");
        exit(1);
    }

    /* translate host name into peer's IP address */
    inet_aton(host, &sin.sin_addr);

    /* build address data structure */
    bzero((char *)&sin, sizeof(sin));
    
    sin.sin_family = AF_INET;
    
    sin.sin_port = htons(SERVER_PORT);
    
    /* active open */
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("simplex-talk: socket");
        exit(1);
    }

    if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        perror("simplex-talk: connect");
        close(s);
        exit(1);
    }

    /* main loop: get and send lines of text */
    while (fgets(buf, sizeof(buf), stdin)) {
        buf[MAX_LINE - 1] = '\0';
        len = strlen(buf) + 1;
        send(s, buf, len, 0);
    }
}
