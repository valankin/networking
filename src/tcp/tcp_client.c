/**
 * @file tcp_client.c
 * @author Yuri Valankin (valankin@.com)
 * @brief 
 * @date 2024-07-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <string.h> // memset, strncmp
#include <stdio.h> // printf


#include "tcp_functions.h"
#include "tcp_settings.h"


struct sockaddr_in server_address()
{
    struct sockaddr_in servaddr;

    memset(&servaddr, BUFFER_FILL_VALUE, sizeof(servaddr));
    servaddr.sin_family = SOCKET_DOMAIN;
    servaddr.sin_addr.s_addr = SERVER_IP;
    servaddr.sin_port = SIN_PORT;

    return servaddr;
}

int main() {

    // init server address sreucture
    struct sockaddr_in servaddr = server_address();
 
    // Create socket
    int sockfd = create_socket();
    printf("Socket fd: %d\n", sockfd);

    
    // Connect to socket
    int conn_code = connect_to_socket(sockfd, &servaddr);

    printf("Connection code: %d\n", conn_code);

    // Use connection if successfull
    if (conn_code == SOCK_CONN_OK) ping(sockfd);
    
    // Close the socket
    close_socket(sockfd);

    return 0;
}
