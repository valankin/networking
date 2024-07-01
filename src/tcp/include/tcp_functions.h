/**
 * @file tcp_functions.h
 * @author Yuri Valankin (valankin@.com)
 * @brief Functions that are applied to connection file descriptors
 * @date 2024-07-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// Function designed for chat between client and server.

#ifndef TCP_FUNCTIONS_H
#define TCP_FUNCTIONS_H


// Buffer
void exit_if_signalled(char *buff);
void load_message(char *buff);

// Socket

// Common
int create_socket();

int bind_socket(int sockfd, struct sockaddr_in* servaddr);
int listen_connections(int sockfd);
int accept_connection(int sockfd, struct sockaddr_in* cliaddr);
int connect_to_socket(int sockfd, struct sockaddr_in* servaddr);
int close_socket(int sockfd);

// Messages
void send_message(char *buff, int sockfd);
void read_message(int sockfd, char *buff);

// Higher level functions
void ping(int sockfd); // client
void pong(int connfd); // server

#endif // TCP_FUNCTIONS_H