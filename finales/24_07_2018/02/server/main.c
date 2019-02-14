#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdbool.h>

#define SIZE_OF_CHAR 1
#define SIZE_OF_INT  4
#define MAX_STANDBY_CONNS 10

void send_buffer(int skt_fd, const char* buffer, const int length) {
    int bytes_sent = 0;
    int skt_still_open = 1;
    while (length > bytes_sent && skt_still_open) {
        int s = send(skt_fd, &buffer[bytes_sent], length - bytes_sent, MSG_NOSIGNAL);
        if (s == -1) { 
            break;
        } else if (s == 0) {
            skt_still_open = 0;
            break;
        } else {
            bytes_sent += s;
        }
    }
}

void recv_buffer(int skt_fd, char *buffer, const int lenght) {
    int bytes_recv = 0;
    int skt_still_open = 1;
    while (lenght > bytes_recv && skt_still_open) {
        int s = read(skt_fd, &buffer[bytes_recv], lenght - bytes_recv);
        if (s == -1) {
            break;
        } else if (s == 0) {
            skt_still_open = 0;
            break;
        } else {
            bytes_recv += s;
        }
    }
}

void send_char(int skt_fd, const char c) {
    send_buffer(skt_fd, (char*)&c, SIZE_OF_CHAR);
}

int recv_int(int skt_fd) {
    int i;
    recv_buffer(skt_fd, (char*)&i, SIZE_OF_INT);
    i = ntohl(i);
    return i;
}

int main() {	
    // Create
    int skt_fd_acceptor = socket(AF_INET, SOCK_STREAM, 0);

    // Bind
    struct sockaddr_in skt_addr;
    skt_addr.sin_family = AF_INET;
    skt_addr.sin_port = htons(8080);
    skt_addr.sin_addr.s_addr = INADDR_ANY;
    bind(skt_fd_acceptor, (struct sockaddr *) &skt_addr, sizeof(skt_addr));

    // Listen
    listen(skt_fd_acceptor, MAX_STANDBY_CONNS);
    printf("Aceptor\n");
    int skt_fd = accept(skt_fd_acceptor, (struct sockaddr*) NULL, NULL);
    
    printf("Empezando Transmicion de Datos\n");
    
    send_char(skt_fd, '3');
    send_char(skt_fd, '4');
    send_char(skt_fd, '5');
    send_char(skt_fd, '\n');
    printf("%d\n", recv_int(skt_fd));
    send_char(skt_fd, '6');
    send_char(skt_fd, '4');
    send_char(skt_fd, '\n');
    printf("%d\n", recv_int(skt_fd));
    send_char(skt_fd, '1');
    send_char(skt_fd, '9');
    send_char(skt_fd, '\n');
    printf("%d\n", recv_int(skt_fd));
    send_char(skt_fd, '0');

    close(skt_fd);
    close(skt_fd_acceptor);

	return 0;
}
