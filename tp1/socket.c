#define _POSIX_C_SOURCE 200112L

#include <string.h>
#include "socket.h"
#include <stddef.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

#define SUCCESS 0
#define ERROR -1

#define SIZE_OF_INT   4 // bytes
#define SIZE_OF_CHAR  1 // bytes

int socket_create(socket_t *self) {
	self->skt_fd = socket(AF_INET, SOCK_STREAM, 0);
	return self->skt_fd;
}

int socket_bind(socket_t *self, unsigned short port) {
	struct sockaddr_in skt_addr;
	skt_addr.sin_family = AF_INET;
    skt_addr.sin_port = htons(port);
    skt_addr.sin_addr.s_addr = INADDR_ANY;

	return bind(self->skt_fd, (struct sockaddr *) &skt_addr, sizeof(skt_addr));
}

int socket_connect(socket_t *self, const char* hostname, const char* port) {
    struct addrinfo hints = { 0 };
    hints.ai_family = AF_INET;       /* IPv4 */
    hints.ai_socktype = SOCK_STREAM; /* TCP */
    
    struct addrinfo *result, *ptr;
    getaddrinfo(hostname, port, &hints, &result);

    bool connected = false;
    for (
        ptr = result;
        ptr != NULL && connected == false;
        ptr = ptr->ai_next
    ) {
        self->skt_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (self->skt_fd != ERROR) {
            if (connect(self->skt_fd, ptr->ai_addr, ptr->ai_addrlen) == ERROR) {
                close(self->skt_fd);
            } else {
                connected = true;
                break;
            }
        }
    }

    freeaddrinfo(result);

    return connected ? SUCCESS : ERROR;
}

int socket_listen(socket_t *self, int max_standby_conn) {
	return listen(self->skt_fd, max_standby_conn);
}

int socket_accept(socket_t *self, socket_t *socket_accepted) {
	socket_accepted->skt_fd = accept(self->skt_fd, NULL, NULL);
	return socket_accepted->skt_fd;
}

int socket_send(socket_t *self, const void *buffer, size_t lenght) {
	return send(self->skt_fd, buffer, lenght, MSG_NOSIGNAL);
}

int socket_send_int(socket_t *socket, int i) {
    int i_big_endian = htonl(i);
    int bytes_sent = 0;
    int skt_still_open = 1;
    while (SIZE_OF_INT > bytes_sent && skt_still_open) {
        int s = socket_send(socket, &i_big_endian , SIZE_OF_INT - bytes_sent);
        if (s == -1) { 
            socket_shutdown(socket);
            socket_destroy(socket);
            return ERROR;   
        } else if (s == 0) {
            skt_still_open = 0;
            return ERROR;
        } else {
            bytes_sent += s;
        }
    }

    return SUCCESS;
}

int socket_send_char(socket_t *socket, char i) {
    int bytes_sent = 0;
    int skt_still_open = 1;
    while (SIZE_OF_CHAR > bytes_sent && skt_still_open) {
        int s = socket_send(socket, &i , SIZE_OF_CHAR - bytes_sent);
        if (s == -1) { 
            socket_shutdown(socket);
            socket_destroy(socket);
            return ERROR;   
        } else if (s == 0) {
            skt_still_open = 0; 
            return ERROR;
        } else {
            bytes_sent += s;
        }
    }
    return SUCCESS;
}

int socket_receive(socket_t *self, void *buffer, size_t lenght) {
    return read(self->skt_fd, buffer, lenght);
}

int socket_recv_int(socket_t *socket, int *i) {
    int bytes_recv = 0;
    int skt_still_open = 1;
    while (SIZE_OF_INT > bytes_recv && skt_still_open) {
        int s = socket_receive(socket, i, SIZE_OF_INT - bytes_recv);
        if (s == -1) {
            socket_shutdown(socket);
            socket_destroy(socket);
            return ERROR;
        } else if (s == 0) {
            skt_still_open = 0;
            return ERROR;
        } else {
            bytes_recv += s;
        }
    }

    *i = ntohl(*i);

    return SUCCESS;
}

int socket_recv_char(socket_t *socket, char *c) {
    int bytes_recv = 0;
    int skt_still_open = 1;
    while (SIZE_OF_CHAR > bytes_recv && skt_still_open) {
        int s = socket_receive(socket, c, SIZE_OF_CHAR - bytes_recv);
        if (s == -1) { 
            socket_shutdown(socket);
            socket_destroy(socket);
            return ERROR;
        } else if (s == 0) {
            skt_still_open = 0; 
            return ERROR;
        } else {
            bytes_recv += s;
        }
    }
    return SUCCESS;
}

int socket_recv_unsigned_char(
    socket_t *socket,
    unsigned char *c
) {
    int bytes_recv = 0;
    int skt_still_open = 1;
    while (SIZE_OF_CHAR > bytes_recv && skt_still_open) {
        int s = socket_receive(socket, c, SIZE_OF_CHAR - bytes_recv);
        if (s == -1) {
            socket_shutdown(socket);
            socket_destroy(socket);
            return ERROR;
        } else if (s == 0) {
            skt_still_open = 0; 
            return ERROR;
        } else {
            bytes_recv += s;
        }
    }
    return SUCCESS;
}

int socket_shutdown_read(socket_t *self) {
	return shutdown(self->skt_fd, SHUT_RD);
}

int socket_shutdown_write(socket_t *self) {
	return shutdown(self->skt_fd, SHUT_WR);
}

int socket_shutdown(socket_t *self) {
    return shutdown(self->skt_fd, SHUT_RDWR);
}

int socket_destroy(socket_t *self) {
	return close(self->skt_fd);
}

int socket_shutdown_destroy(socket_t *self) {
    if (
        (shutdown(self->skt_fd, SHUT_RDWR) == ERROR) ||
        (close(self->skt_fd)               == ERROR)
    ) {
        return ERROR;
    } else {
        return SUCCESS;
    }
}
