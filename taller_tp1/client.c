#include <stdlib.h>
#include <stdio.h>
#include "socket.h"

#define ERROR -1
#define SUCCESS 0

int client(char *argv[]) {  
	// argv[2] = Hostname 
	// argv[3] = Port 
	// argv[4] = N
	// argv[5] = Namefile

	if(argv[2] == NULL || argv[3] == NULL || argv[4] == NULL) return ERROR;

	FILE* input;
		
	if (argv[5] == NULL) {
		input = stdin;
	} else {
		input = fopen(argv[5], "rb");
	}

	if (input == NULL) return ERROR;

	socket_t skt_client;
	
	int N = (int) strtol(argv[4], NULL, 10);
	
	if (socket_connect(&skt_client, argv[2], argv[3]) == ERROR) return ERROR;

	if (socket_send_int(&skt_client, N) == ERROR) return ERROR;

	do {
		char c = fgetc(input);
		if(socket_send_char(&skt_client, c) == ERROR) {
			if(input != stdin) fclose(input);
			return ERROR;	
		} 
	} while (!feof(input));

	if(input != stdin) fclose(input);

	socket_shutdown_write(&skt_client);

	printf("%s\n", "Variables dump");

	for(int i = 0; i<N; ++i) {
		int number;
		if (socket_recv_int(&skt_client, &number) == ERROR) return ERROR;
		printf("%08x\n", number);
	}

	socket_shutdown_read(&skt_client);

	socket_destroy(&skt_client);

	return SUCCESS;
}
