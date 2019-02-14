#include <string.h>

#include "client.h"
#include "server.h"

#include "stack.h"
#include <stdio.h>

#define SUCCESS 0
#define ERROR -1

int main(int argc, char* argv[]) {
	if (argv[1] == NULL) return ERROR;

	if      (strcmp(argv[1], "client")  == SUCCESS) return client(argv);
	else if (strcmp(argv[1], "server")  == SUCCESS) return server(argv);
	else 											return ERROR;
}
