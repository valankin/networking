/**
 * @file tcp_functions.c
 * @author Yuri Valankin (valankin@.com)
 * @brief Functions that are applied to connection file descriptors
 * @date 2024-07-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h> // printf
#include <errno.h> // error codes
#include <stdlib.h> // exit

#include <string.h> // memset, strncmp
#include <unistd.h> // posix read, write

#include <sys/socket.h> // socket, connect, close
#include <arpa/inet.h> // for sockaddr_in and inet_pton

#include "tcp_functions.h"
#include "tcp_settings.h"


// Socket and connection



// Buffer
void exit_if_signalled(char *buff)
{
    if ((strncmp(buff, "exit", 4)) == 0) {
			printf("Exiting...\n");
            exit(0);
    }
}

void load_message(char *buff)
{   
    printf("Send text: ");
    int n = 0;
	while ((buff[n++] = getchar()) != '\n');
    buff[n - 1] = '\0';  // Null-terminate the string
}


// Socket
int create_socket()
{   
    int sockfd = socket(SOCKET_DOMAIN, SOCKET_TYPE, SOCKET_PROTOCOL);

    if (sockfd == SOCK_CREATE_ERR) {
        printf("Error connecting to socket: (%d) %s\n", 
                errno, 
                strerror(errno));
        exit(0);
    } else
        printf("Socket successfully created..\n");
        return sockfd;
}


 /**
     * @brief Binds the socket to the IP address and port specified in servaddr using the bind function.
     * If bind_code is not 0, it indicates a failure, so it prints an error message and exits the program. Otherwise, it prints a success message.
     */
int bind_socket(int sockfd, struct sockaddr_in* servaddr)
{
    int bind_code = bind(sockfd, (struct sockaddr*)servaddr, sizeof(*servaddr));
    if (bind_code == SOCK_BIND_ERR) {
        printf("Error binding to socket: (%d) %s\n", 
                errno, 
                strerror(errno));        
        exit(0);
    } else
        printf("Socket successfully binded..\n");
        return SOCK_BIND_OK;
}


int listen_connections(int sockfd)
{
    /**
     * @brief Now server is ready to listen and verification
     * Puts the server socket in a listening state using the listen function 
     * with a backlog of 5 (the maximum length to which the queue of pending connections may grow).
     * If the listen function returns a non-zero value, it indicates a failure, 
     * so it prints an error message and exits the program. 
     * Otherwise, it prints a success message.
     * 
     */
    if ((listen(sockfd, SOCK_MAX_CONNECTIONS)) == SOCK_LISTEN_ERR) {
        printf("Error listening connections: (%d) %s\n", 
                errno, 
                strerror(errno));
        exit(0);
    } else
        printf("Server listening..\n");
        return SOCK_LISTEN_OK;
}


int accept_connection(int sockfd, struct sockaddr_in* cliaddr)
{
     // Accept the data packet from client and verification
    socklen_t len = sizeof(cliaddr);
    int connfd = accept(sockfd, (struct sockaddr*)&cliaddr, &len);
    if (connfd == SOCK_ACCEPT_ERR) {
        printf("Server accept failed...\n");
        printf("Error connecting to server socket: (%d) %s\n", errno, strerror(errno));
        exit(0);
    } else
        printf("Server accepted the client...\n");
        return connfd;
}


int connect_to_socket(int sockfd, struct sockaddr_in* servaddr)
{
    // connect the client socket to server socket
    int connect_code = connect(sockfd, (struct sockaddr*)servaddr, sizeof(*servaddr));
    if (connect_code == SOCK_CONN_ERR) {
        printf("Error connecting to socket: (%d) %s\n", errno, strerror(errno));
        exit(0);
    } else
        printf("Connected to socket..\n");
        return SOCK_CONN_OK;
}

int close_socket(int sockfd)
{
    int close_code = close(sockfd);
    if (close_code == SOCK_CLOSE_ERR) {
        printf("Error closing socket: %s\n", strerror(errno));
        exit(0);
    } else {
        printf("Successfully closed connection.");
        return SOCK_CLOSE_OK;
    }
}

// Messages
void send_message(char *buff, int sockfd)
{
    write(sockfd, buff, CHAR_BUFFER_SIZE);
}

/**
 * @brief Reads from file descriptor
 * 
 * @param fd - connection or docker fd
 * @param buff - char buffer
 */
void read_message(int fd, char *buff)
{
    memset(buff, BUFFER_FILL_VALUE, CHAR_BUFFER_SIZE);
    read(fd, buff, CHAR_BUFFER_SIZE);

    // Clear buffer
    printf("Received: %s\n", buff);
	
}


// Higher level functions
void pong(int connfd) {
    char buff[CHAR_BUFFER_SIZE]; // Message buffer in chars
    memset(buff, BUFFER_FILL_VALUE, CHAR_BUFFER_SIZE);
   
    // Infinite loop for chat
    for (;;) {
        // Read from fd into buff
        read_message(connfd, buff);

        // Checks if input equals "exit"
        exit_if_signalled(buff);

        // Load message into the buffer
        load_message(buff);

        // Write buffer into connection fd
        send_message(buff, connfd);

    }
}


void ping(int sockfd)
{   
    // Create buffer for message
	char buff[CHAR_BUFFER_SIZE];
    memset(buff, BUFFER_FILL_VALUE, CHAR_BUFFER_SIZE);

    // Chat with server until exit
	for (;;) {
        // Load message into the buffer
        load_message(buff);

        // Checks if input equals "exit"
        exit_if_signalled(buff);

        // Write buffer into socket
        send_message(buff, sockfd);

        // Read from socket into the buffer
        read_message(sockfd, buff);
	}
}