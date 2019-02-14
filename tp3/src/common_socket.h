#ifndef __SOCKET_H__
#define __SOCKET_H__

/*** Socket ***/

#include <cstddef>
#include <string>

class Socket {
	int skt_fd;
	
	explicit Socket(const int skt_fd);
	int send(const void *buffer, const int length);
	int recv(void *buffer, const int length);
	void send_buffer(const char* buffer, const int length);
	void recv_buffer(char *buffer, const int length);

public:
	// Contruye el socket.
	// Deja inicializado el objeto.
	Socket();
	// Constructor por movimiento.
	Socket(Socket &&other);
	// Destructor del socket.
	// Libera todos los recursos utilizados por el socket.
	~Socket();
	// Asignacion pr movimiento.
	Socket& operator=(Socket &&other);
	// Prohibo la construccion por copia.
	Socket(const Socket&) = delete;
	// Prohibo la asignacion por copia.
	Socket& operator=(const Socket&) = delete;
	// Establece a que puerto se quiere asociar el socket.
	// Si sucede un error se arroja una excepcion (std::runtime_error).
	void bind(const unsigned short port);
	/* Establece una conneccion a la maquina remota, indicada 
 	 * mediante host_name y port.
     */
	// Si sucede un error se arroja una excepcion (std::runtime_error).
	void connect(const char *host_name, const unsigned short port);
	/* Define cuantas conecciones en espera pueden esperar hasta ser 
     * aceptadas en el Socket.
     */
	// Si sucede un error se arroja una excepcion (std::runtime_error).
	void listen(const int max_standby_conn);
	// Crea un nuevo socket servidor para la comunicacion con el socket cliente.
	// Retorna el nuevo socket.
	// Si sucede un error se arroja una excepcion (std::runtime_error).
	Socket accept();
	// El socket envia el entero pasado como parametro.
	void send_int(const int i);
	// El socket envia el entero sin signo pasado como parametro.
	void send_unsigned_int(const unsigned int i);
	// El socket envia el caracter pasado como parametro.
	void send_char(const char c);
	// El socket envia el string pasado como parametro.
	void send_str(const std::string &str);
	// El socket recibe un entero.
	// Este dato es retornado.
	int           recv_int();
	// El socket recibe un entero sin signo.
	// Este dato es retornado.
	unsigned int  recv_unsigned_int();
	// El socket recibe un caracter.
	// Este dato es retornado.
	char          recv_char();
	// El socket recibe un caracter sin signo.
	// Este dato es retornado.
	unsigned char recv_unsigned_char();
	// El socket recibe un string.
	// Este dato es retornado.
	std::string   recv_str();
	// Deshabilita la lectura de datos del socket.
	// Si sucede un error se arroja una excepcion (std::runtime_error).
	void shutdown_read();
	// Deshabilita la escritura de datos del socket.
	// Si sucede un error se arroja una excepcion (std::runtime_error).
	void shutdown_write();
	// Deshabilita la lectura y escritura de datos del socket.
	// Si sucede un error se arroja una excepcion (std::runtime_error).
	void shutdown();
};

#endif
