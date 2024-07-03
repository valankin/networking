/**
 * @file tcp_server.c
 * @author Yuri Valankin (valankin@.com)
 * @brief A TCP Server
 * @date 2024-07-01
 *  
 */

// #include <stdlib.h>
#include <stdio.h> // For printf and getchar
#include <string.h> // For bzero and strncmp
#include <unistd.h> // For POSIX read and write
#include <errno.h> // error codes

#include <sys/socket.h>
// #include <netdb.h>  

#include "tcp_server.h"
#include "tcp_settings.h"
#include "tcp_functions.h"

/**
 * @brief Init address to which server socket is bound
 * 
 * @return struct sockaddr_in 
 */
struct sockaddr_in listen_address()
{
    struct sockaddr_in servaddr;
    memset(&servaddr, BUFFER_FILL_VALUE, sizeof(servaddr));
     /**
     * @brief Assigns the IP address and port to the servaddr structure.
     * servaddr.sin_family is set to SOCKET_DOMAIN, which specifies the address family (e.g., AF_INET for IPv4).
     * servaddr.sin_addr.s_addr is set to S_ADR, which specifies the IP address.
     * servaddr.sin_port is set to SIN_PORT, which specifies the port number.
     */
    servaddr.sin_family = SOCKET_DOMAIN;
    servaddr.sin_addr.s_addr = LISTEN_IP; 
    servaddr.sin_port = SIN_PORT;

    return servaddr;
}

/**
 * @brief Function to set up and start the server.
 */
void start_server() {
    /**
     * @brief Create address structures
     * servaddr for the server address,
     * cliaddr for the client address
     */
    struct sockaddr_in servaddr = listen_address();
    struct sockaddr_in cliaddr;

    int sockfd = create_socket();
    printf("Socket fd: %d\n", sockfd);
   
    bind_socket(sockfd, &servaddr);

    listen_connections(sockfd);

    int connfd = accept_connection(sockfd, &cliaddr);
    printf("Connection fd: %d\n", sockfd);
    pong(connfd);

    close_socket(sockfd);
}

int main() {
    start_server();
    return 0;
}
