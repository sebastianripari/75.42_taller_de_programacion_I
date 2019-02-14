#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stddef.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <errno.h>
#include <string> 
#include "common_socket.h"

#include <iostream>

#define SUCCESS 0
#define ERROR -1

#define SIZE_OF_INT   4 // bytes
#define SIZE_OF_CHAR  1 // bytes


Socket::Socket() {
    this->skt_fd = ::socket(AF_INET, SOCK_STREAM, 0);
}

Socket::Socket(const int skt_fd) {
    this->skt_fd = skt_fd;
}

Socket::Socket(Socket&& other) {
    this->skt_fd = other.skt_fd;
    other.skt_fd = 0;
}

Socket& Socket::operator=(Socket &&other) {
    if (this == &other) return *this;

    ::close(this->skt_fd);
    this->skt_fd = other.skt_fd;
    other.skt_fd = 0;
    return *this;
}

Socket::~Socket() {
    if (this->skt_fd != 0) ::close(this->skt_fd);
}

void Socket::bind(const unsigned short port) {
	struct sockaddr_in skt_addr;
	skt_addr.sin_family = AF_INET;
    skt_addr.sin_port = htons(port);
    skt_addr.sin_addr.s_addr = INADDR_ANY;

    if (::bind(
            this->skt_fd,
            (struct sockaddr *) &skt_addr,
            sizeof(skt_addr)) == ERROR)
        throw std::runtime_error(std::string("bind error"));
}

void Socket::connect(const char* hostname, const unsigned short port) {
    bool are_we_connected = false;
    int s = 0;
    struct addrinfo hints;
    struct addrinfo *result, *ptr;

    char portString[6];
    snprintf(portString, sizeof(portString), "%d", port);

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       // IPv4 (or AF_INET6 for IPv6)     
    hints.ai_socktype = SOCK_STREAM; // TCP  (or SOCK_DGRAM for UDP)    
    hints.ai_flags = 0;              // None (or AI_PASSIVE for server) 

    s = getaddrinfo(hostname, portString, &hints, &result);

    for (
        ptr = result;
        ptr != NULL && are_we_connected == false;
        ptr = ptr->ai_next
    ) {
        if (this->skt_fd != ERROR) {
            s = ::connect(this->skt_fd, ptr->ai_addr, ptr->ai_addrlen);
            if (s == ERROR) ::close(this->skt_fd);
            are_we_connected = (s != -1); 
        }
    }

    freeaddrinfo(result);

    if (are_we_connected == false)
        throw std::runtime_error(std::string("connect error"));
}

void Socket::listen(const int max_standby_conn) {
    if (::listen(this->skt_fd, max_standby_conn) == ERROR)
        throw std::runtime_error(std::string("listen error"));
}

Socket Socket::accept() {
    int skt_fd = ::accept(this->skt_fd, (struct sockaddr*) NULL, NULL);
    if (skt_fd == -1) throw std::runtime_error(std::string("accept error"));
    else 
        return std::move(Socket(skt_fd));
}

int Socket::send(const void *buffer, const int length) {
	return ::send(this->skt_fd, buffer, length, MSG_NOSIGNAL);
}

void Socket::send_buffer(const char* buffer, const int length) {
    int bytes_sent = 0;
    int skt_still_open = 1;
    while (length > bytes_sent && skt_still_open) {
        int s = this->send(&buffer[bytes_sent], length - bytes_sent);
        if (s == -1) { 
            throw std::runtime_error(std::string("send error")); 
        } else if (s == 0) {
            skt_still_open = 0;
            throw std::runtime_error(std::string("socket desconectado"));
        } else {
            bytes_sent += s;
        }
    }
}

void Socket::send_int(const int i) {
    int i_big_endian = htonl(i);
    this->send_buffer((char*)&i_big_endian, SIZE_OF_INT);
}

void Socket::send_unsigned_int(const unsigned int i) {
    unsigned int i_big_endian = htonl(i);
    this->send_buffer((char*)&i_big_endian, SIZE_OF_INT);
}

void Socket::send_char(const char c) {
    this->send_buffer(&c, SIZE_OF_CHAR);
}

void Socket::send_str(const std::string &str) {
    for (const char c : str) this->send_char(c);
}

int Socket::recv(void *buffer, const int lenght) {
    return ::read(this->skt_fd, buffer, lenght);
}

void Socket::recv_buffer(char *buffer, const int lenght) {
    int bytes_recv = 0;
    int skt_still_open = 1;
    while (lenght > bytes_recv && skt_still_open) {
        int s = this->recv(&buffer[bytes_recv], lenght - bytes_recv);
        if (s == -1) {
            throw std::runtime_error(std::string("recv error"));
        } else if (s == 0) {
            skt_still_open = 0;
            throw std::runtime_error(std::string("socket desconectado"));
        } else {
            bytes_recv += s;
        }
    }
}

int Socket::recv_int() {
    int i;
    this->recv_buffer((char*)&i, SIZE_OF_INT);
    i = ntohl(i);
    return i;
}

unsigned int Socket::recv_unsigned_int() {
    unsigned int i;
    this->recv_buffer((char*)&i, SIZE_OF_INT);
    i = ntohl(i);
    return i;
}

char Socket::recv_char() {
    char c;
    this->recv_buffer((char*)&c, SIZE_OF_CHAR);
    return c;
}

unsigned char Socket::recv_unsigned_char() {
    unsigned char c;
    this->recv_buffer((char*)&c, SIZE_OF_CHAR);
    return c;
}

std::string Socket::recv_str() {
    std::string str;
    char c;
    while ((c = recv_char()) != '\0') str += c;
    return str;
}

void Socket::shutdown_read() {
    if (::shutdown(this->skt_fd, SHUT_RD) == ERROR)
        throw std::runtime_error(std::string("shutdown error"));
}

void Socket::shutdown_write() {
    if (::shutdown(this->skt_fd, SHUT_WR) == ERROR)
        throw std::runtime_error(std::string("shutdown error"));
}

void Socket::shutdown() {
    if (::shutdown(this->skt_fd, SHUT_RDWR) == ERROR)
        throw std::runtime_error(std::string("shutdown error"));
}
