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
#include "message.h"


/**
 * @brief Connection address
 * 
 * @return struct sockaddr_in 
 */
struct sockaddr_in server_address()
{
    struct sockaddr_in servaddr;

    memset(&servaddr, BUFFER_FILL_VALUE, sizeof(servaddr));
    servaddr.sin_family = SOCKET_DOMAIN;
    servaddr.sin_addr.s_addr = SERVER_IP;
    servaddr.sin_port = SIN_PORT;

    return servaddr;
}



int start_client(Message *msg) {
    // init server address sreucture
    struct sockaddr_in servaddr = server_address();
 
    // Create socket
    int sockfd = create_socket();
    printf("Socket fd: %d\n", sockfd);

    // Connect to socket
    int conn_code = connect_to_socket(sockfd, &servaddr);

    printf("Connection code: %d\n", conn_code);

    // Use connection if successfull
    // if (conn_code == SOCK_CONN_OK) {
    //     message_function_t func = get_function_by_name(msg->function_name);
    //     printf("Called function: %s", func);
    //     if (func) {
    //         func(msg);
    //     } else {
    //         printf("Function '%s' not found.\n", msg->function_name);
    //     }
    // }
    if (conn_code == SOCK_CONN_OK) {
        message_function_t func = get_function_by_name(msg->function_name);
        printf("Called function: %p\n", func);
        if (func) {
            printf("Using socket fd %d to send message...\n", sockfd);
            func(sockfd, msg);
        } else {
            printf("Function '%s' not found.\n", msg->function_name);
        }
    }
    
    // Close the socket
    close_socket(sockfd);

    return 0;
}

int main() {
    Message msg = create_default_client_message();
    start_client(&msg);
    return 0;
}
