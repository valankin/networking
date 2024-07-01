/**
 * @file tcp_settings.h
 * @author Yuri Valankin (valankin@.com)
 * @brief TCP settings
 * @version 0.1
 * @date 2024-07-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef TCP_SETTINGS_H
#define TCP_SETTINGS_H

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

/**
 * @brief Port to bind to
 * 
 */
#define PORT 8080

/**
 * @brief Socker settings
 * AF_INET - internetwork: UDP, TCP, etc.
 * SOCK_STREAM - stream socket
 * SOCKET_PROTOCOL - socker ptotocol
 */ 
#define SOCKET_DOMAIN AF_INET
#define SOCKET_TYPE SOCK_STREAM
#define SOCKET_PROTOCOL 0 // ip

/**
 * @brief Network/external number representation conversion.
 * INADDR_ANY means the server will accept connections on any of the host's IP addresses.
 * htonl, htonl convert values between host and network byte order
 */ 
#define LISTEN_IP htonl(INADDR_ANY) // Listen to any internal ip address
#define SIN_PORT htons(PORT) // port number


#define SERVER_IP inet_addr("127.0.0.1")


/**
 * @brief Structure for socker info
 * MacOS: [XSI] Structure used by kernel to store most addresses.
 * struct sockaddr {
 *      __uint8_t       sa_len;         total length
 *      sa_family_t     sa_family;      [XSI] address family
 *      char            sa_data[14];     [XSI] addr value
 * };
 */
#define SA struct sockaddr

/**
 * @brief Number of chars in the buffer
 * 
 */
#define CHAR_BUFFER_SIZE 256
#define SOCK_MAX_CONNECTIONS 5

// Socket connection codes
#define SOCK_CREATE_OK 0
#define SOCK_CREATE_ERR -1

#define SOCK_BIND_OK 0
#define SOCK_BIND_ERR -1

#define SOCK_LISTEN_OK 0
#define SOCK_LISTEN_ERR -1

#define SOCK_ACCEPT_OK 0
#define SOCK_ACCEPT_ERR -1

#define SOCK_CONN_OK 0
#define SOCK_CONN_ERR -1



#define SOCK_CLOSE_OK 0
#define SOCK_CLOSE_ERR -1

// Fill value used in memset
#define BUFFER_FILL_VALUE 0

// Exit string
#define EXIT_STR "exit"
#define MAX_CHARS_CMP sizeof(EXIT_STR)
#define STR_EQUALS_CODE 0



#endif // TCP_SETTINGS_H
