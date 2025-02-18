/**
 * @file tcp_server.c
 * @author Yuri Valankin (valankin@.com)
 * @brief A TCP Server
 * @date 2024-07-01
 *  
 */

#include <stdlib.h> // getenv
#include <stdio.h> // printf and getchar
#include <string.h> // bzero and strncmp
#include <unistd.h> // POSIX read and write
#include <errno.h> // error codes

#include <sys/socket.h>

#include "tcp_server.h"
#include "tcp_settings.h"
#include "tcp_functions.h"
#include "message.h"

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

    Message msg;
    receive_structured_message(connfd, &msg);
    // apply_function_to_message(&msg);

    printf("Processed message: Caller ID=%s, Message ID=%s, Timestamp=%ld, Data=%s\n", 
           msg.caller_id, 
           msg.message_id, 
           msg.timestamp, 
           msg.data);

    // Optionally send the processed message back to the client
    // send_structured_message(connfd, &msg);
    // pong(connfd);

    close_socket(sockfd);
}

int main() {

    
    char *db_host = getenv("DB_HOST");
    char *db_user = getenv("DB_USER");
    char *db_pass = getenv("DB_PASS");

    if (db_host && db_user && db_pass) {
        printf("DB Host: %s\n", db_host);
        printf("DB User: %s\n", db_user);
        printf("DB Pass: %s\n", db_pass);
    } else {
        printf("Environment variables not set.\n");
    }

    start_server();
    return 0;
}
