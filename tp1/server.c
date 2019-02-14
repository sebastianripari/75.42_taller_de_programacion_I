#include <stdio.h>
#include <stdlib.h>
#include "socket.h"
#include "java_virtual_machine.h"
#include "bytecodes.h"

#define MAX_STANDBY_CONNS 10

#define ERROR  -1
#define SUCCESS 0

int server(char *argv[]) {
	// argv[2] = Port 

	if (argv[2] == NULL) return ERROR;

	short unsigned int port = (short unsigned int) strtol(argv[2], NULL, 10);

	socket_t skt_acceptor;
	socket_t skt_server;

	if (socket_create(&skt_acceptor) == ERROR)                    return ERROR;
	if (socket_bind(&skt_acceptor, port) == ERROR)                return ERROR;
	if (socket_listen(&skt_acceptor, MAX_STANDBY_CONNS) == ERROR) return ERROR;
	if (socket_accept(&skt_acceptor, &skt_server) == ERROR)       return ERROR;

	int N;

	if (socket_recv_int(&skt_server, &N) == ERROR) {
		socket_shutdown_destroy(&skt_acceptor);
		return ERROR;
	}

	unsigned char bytecode;
	char c;

	jvm_t java_virtual_machine;
	jvm_create(&java_virtual_machine, N);

	printf("%s\n", "Bytecode trace");

	while(socket_recv_unsigned_char(&skt_server, &bytecode) == SUCCESS) {
		switch(bytecode) {
			case BIPUSH: printf("bipush\n");
				if (socket_recv_char(&skt_server, &c) == ERROR) {
					socket_shutdown_destroy(&skt_acceptor);
					jvm_destroy(&java_virtual_machine);
					return ERROR;
				}
				jvm_execute_instruction_bipush(&java_virtual_machine, c);  break;
			case DUP: printf("dup\n");
				jvm_execute_instruction_dup(&java_virtual_machine);        break;
			case ISTORE: printf("istore\n");
				if (socket_recv_char(&skt_server, &c) == ERROR) {
					socket_shutdown_destroy(&skt_acceptor);
					jvm_destroy(&java_virtual_machine);
					return ERROR;
				}
				jvm_execute_instruction_istore(&java_virtual_machine, c);  break;
			case ILOAD: printf("iload\n");
				if (socket_recv_char(&skt_server, &c) == ERROR) {
					socket_shutdown_destroy(&skt_acceptor);
					jvm_destroy(&java_virtual_machine);
					return ERROR;
				}
				jvm_execute_instruction_iload(&java_virtual_machine, c);  break;
			case IADD: printf("iadd\n");
				jvm_execute_instruction_iadd(&java_virtual_machine);      break;
			case ISUB: printf("isub\n");
				jvm_execute_instruction_isub(&java_virtual_machine);      break;
			case IMUL: printf("imul\n");
				jvm_execute_instruction_imul(&java_virtual_machine);      break;			
			case IDIV: printf("idiv\n");
				jvm_execute_instruction_idiv(&java_virtual_machine);      break;
			case IREM: printf("irem\n");
				jvm_execute_instruction_irem(&java_virtual_machine);      break;
			case INEG: printf("ineg\n");
				jvm_execute_instruction_ineg(&java_virtual_machine);      break;
			case IAND: printf("iand\n");
				jvm_execute_instruction_iand(&java_virtual_machine);      break;
			case IOR: printf("ior\n");
				jvm_execute_instruction_ior(&java_virtual_machine);       break;
			case IXOR: printf("ixor\n");
				jvm_execute_instruction_ixor(&java_virtual_machine);      break;
		}
	}

	printf("\nVariables dump\n");

	int *variables_array = jvm_get_variables_array(&java_virtual_machine);
	for(int i=0; i<N; ++i) {
		printf("%08x\n", variables_array[i]);
		int n = variables_array[i];
		if(socket_send_int(&skt_server, n) == ERROR) {
			socket_shutdown_destroy(&skt_acceptor);
			jvm_destroy(&java_virtual_machine);
			return ERROR;
		}
	}

	socket_shutdown_destroy(&skt_acceptor);
	socket_shutdown_destroy(&skt_server);
	jvm_destroy(&java_virtual_machine);

	return SUCCESS;
}
