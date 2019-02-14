/*
Escriba un programa que reciba paquetes 
de 10 bytes por el puerto TCP 815 y los 
imprima por pantalla. Al recibir el byte
0xff debe cerrarse ordenadamente.
No considere errores.
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>

#define MAX_STANDBY_CONN 10
#define PORT 815

int main() {
	/////////////// Creo Socket Pasivo /////////////////
	// SOCK_STREAM: Es que se usa en TCP.
	// AF_INET: IPv4.
	int skt_fd_passive = socket(AF_INET, SOCK_STREAM, 0);

	/////////////////////// Bind ////////////////////////
	struct sockaddr_in skt_addr;
	skt_addr.sin_family = AF_INET;
    skt_addr.sin_port = htons(PORT);
    skt_addr.sin_addr.s_addr = INADDR_ANY;
	bind(skt_fd_passive, (struct sockaddr *) &skt_addr, sizeof(skt_addr));

	////////////////////// Listen ///////////////////////
	listen(skt_fd_passive, MAX_STANDBY_CONN);

	////////////////////// Accept ///////////////////////
	int skt_server = accept(skt_fd_passive, 0, 0);

	////////////////////// Read ////////////////////////
	bool keep_going = true;
	int s = 0;
	while(keep_going) {
		unsigned char bytes[10];
		int bytes_recv = 0;
		while(keep_going) {
			s = read(skt_server, &bytes[bytes_recv], 10 - bytes_recv);
			for(int i = 0; i < s; ++i) if(bytes[bytes_recv + i] == 0xff) keep_going = false;
			bytes_recv += s;
			if(bytes_recv == 10) {
				printf("%s\n", bytes);
				break;
			}
		}
	}
	
	return 0;
}