#ifndef __SOCKET_H__
#define __SOCKET_H__

/*** Socket ***/

#include <stddef.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

typedef struct {
	int skt_fd; // socket file descriptor 
} socket_t;

// Crea un socket. 
// Pre: self apunta a un sector valido de memoria. 
int socket_create(socket_t *self);
// Deshabilita la lectura de datos del socket.
// Pre: self apunta un sector valido de memoria. 
int socket_shutdown_read(socket_t *self);
// Deshabilita la escritura de datos del socket.
// Pre: self apunta un sector valido de memoria. 
int socket_shutdown_write(socket_t *self);
// Deshabilita la lectura y escritura de datos del socket.
// Pre: self apunta un sector valido de memoria. 
int socket_shutdown(socket_t *self);
// Destruye la instancia self liberando sus recursos. 
// Pre: self fue inicializado mediante socket_create o socket_accept. 
int socket_destroy(socket_t *self);
// Deshabilita la lectura y escritura de datos del socket.
// Destruye la instancia self liberando sus recursos. 
// Pre: self fue inicializado mediante socket_create o socket_accept. 
int socket_shutdown_destroy(socket_t *self);
// Establece a que IP y puerto se quiere asociar el Socket. 
// Pre: self apunta un sector valido de memoria. 
int socket_bind(socket_t *self, unsigned short port);
/* Define cuantas conecciones en espera pueden esperar hasta ser 
 * aceptadas en el Socket.
 */
// Pre: self apunta un sector valido de memoria 
int socket_listen(socket_t *self, int max_standby_conn);
/* Establece una conneccion a la maquina remota, indicada 
 * mediante host_name y port.
 */
// Pre: self apunta un sector valido de memoria. 
int socket_connect(socket_t *self, const char *host_name, const char *port);
// Crea un nuevo socket servidor para la comunicacion con el socket cliente.
// Pre: self apunta un sector valido de memoria. 
// Post: Retorna el file descriptor del socket aceptado (socket servidor).
int socket_accept(socket_t *self, socket_t *socket_accepted);
// Envia el contenido de buffer en forma de bytes.  
// Pre: self apunta un sector valido de memoria. 
/* Post: Valores de retorno:
 * s < 0 : Hubo un error inesperado.	
 * s == 0 : El socket fue cerrado.
 * s > 0 : s bytes fueron enviados.
 */
int socket_send(socket_t *self, const void *buffer, size_t length);
// Envia el int con signo "i" a traves del socket.
// Si detecta un error aplica un shutdown y destroy del socket.
// Post: Retorna  0 en caso de funcionar bien.
//       Retorna -1 en caso de error. 
int socket_send_int(socket_t *self, int i);
// Envia el char con signo "c" a traves del socket.
// Si detecta un error aplica un shutdown y destroy del socket.
// Post: Retorna  0 en caso de funcionar bien.
//       Retorna -1 en caso de error. 
int socket_send_char(socket_t *socket, char c);
// Recibe el contenido de buffer en forma de bytes. 
// Pre: self apunta un sector valido de memoria.
/* Post: Valores de retorno:
 * s < 0 : Hubo un error inesperado.	
 * s == 0 : El socket fue cerrado.
 * s > 0 : s bytes fueron recibidos.
 */
int socket_receive(socket_t *self, void *buffer, size_t length);
// Recive el int con signo "i" a traves del socket.
// Si detecta un error aplica un shutdown y destroy del socket.
// Post: Retorna  0 en caso de funcionar bien.
//       Retorna -1 en caso de error. 
int socket_recv_int(socket_t *socket, int *i);
// Recive el char con signo "c" a traves del socket.
// Si detecta un error aplica un shutdown y destroy del socket.
// Post: Retorna  0 en caso de funcionar bien.
//       Retorna -1 en caso de error. 
int socket_recv_char(socket_t *socket, char *c);
// Recive el char sin signo "c" a traves del socket.
// Si detecta un error aplica un shutdown y destroy del socket.
// Post: Retorna  0 en caso de funcionar bien.
//       Retorna -1 en caso de error. 
int socket_recv_unsigned_char(socket_t *socket, unsigned char *c);

#endif
