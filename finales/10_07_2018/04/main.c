/*
Enunciado.
Defina una rutina en C que se conecte a la IP 8.8.8.8,
al puerto 8192 y reciba un archivo binario. El archivo
recibido debe ser descargado a un archivo llamado
recibido.bin cuidando el uso de recursos de memoria.
El archivo finaliza al detectar conexion cerrada.
*/

#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

int main() {
	// Creo filtro de las direcciones que me interesan.
	struct addrinfo hints, *result, *ptr;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;      // IPv4
	hints.ai_socktype = SOCK_STREAM; // TCP 
	hints.ai_flags = 0;
	getaddrinfo("8.8.8.8", "8192", &hints, &result);
	int r = 0;
	int skt_fd;
	// Connect.
	for (ptr = result; ptr != NULL && (skt_fd != -1); ptr = ptr->ai_next) {
		skt_fd = socket(AF_INET, SOCK_STREAM, 0);
		r = connect(skt_fd, ptr->ai_addr, ptr->ai_addrlen);
		if (r == -1) close(skt_fd);
	}
	freeaddrinfo(result);
	// Read bytes and write file.
	FILE* f = fopen("recibido.bin", "wb");
	bool keep_going = false;
	while(keep_going) {
		char bytes[1024];
		int bytes_recv = 0;
		int bytes_read = 0;
		while(keep_going && bytes_recv < 1024) {
			bytes_read = read(skt_fd, &bytes[bytes_recv], 1024 - bytes_recv);
			if (bytes_read == 0) /* Socket desconectado */ keep_going = false; 
			fwrite(&bytes[bytes_recv], sizeof(char), bytes_read, f);
		}
	}
	fclose(f);

	return 0;
}