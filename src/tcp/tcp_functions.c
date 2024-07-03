#include <stdio.h> // printf
#include <errno.h> // error codes
#include <stdlib.h> // exit

#include <string.h> // memset, strncmp
#include <unistd.h> // posix read, write

#include <sys/socket.h> // socket, connect, close
#include <arpa/inet.h> // for sockaddr_in and inet_pton

#include "message.h"
#include "tcp_functions.h"
#include "tcp_settings.h"

// Buffer
void clear_buff(char *buff) {
    memset(buff, BUFFER_FILL_VALUE, CHAR_BUFFER_SIZE);
}

char* heap_buff() {
    int buff_size_bytes = CHAR_BUFFER_SIZE * sizeof(char);
    char *buff = (char *)malloc(buff_size_bytes);
    if (buff == NULL) {
        printf("Failed to allocate [%d bytes] of memory for buffer: (%d) %s\n",
                buff_size_bytes, 
                errno, 
                strerror(errno));        
        exit(1);
    }
    clear_buff(buff);
    printf("Allocated heap buffer of size [%d bytes]\n", buff_size_bytes);
    return buff;
}

void exit_if_signalled(char *buff) {
    if ((strncmp(buff, "exit", 4)) == 0) {
        printf("Exiting...\n");
        exit(0);
    }
}

void load_message(char *buff) {   
    printf("Send text: ");
    int n = 0;
    while ((buff[n++] = getchar()) != '\n');
    buff[n - 1] = '\0';  // Null-terminate the string
}

// Socket
int create_socket() {   
    int sockfd = socket(SOCKET_DOMAIN, SOCKET_TYPE, SOCKET_PROTOCOL);
    if (sockfd == SOCK_CREATE_ERR) {
        printf("Error connecting to socket: (%d) %s\n", 
                errno, 
                strerror(errno));
        exit(0);
    } else {
        printf("Socket successfully created..\n");
        return sockfd;
    }
}

int bind_socket(int sockfd, struct sockaddr_in* servaddr) {
    int bind_code = bind(sockfd, (struct sockaddr*)servaddr, sizeof(*servaddr));
    if (bind_code == SOCK_BIND_ERR) {
        printf("Error binding to socket: (%d) %s\n", 
                errno, 
                strerror(errno));        
        exit(0);
    } else {
        printf("Socket successfully binded..\n");
        return SOCK_BIND_OK;
    }
}

int listen_connections(int sockfd) {
    if ((listen(sockfd, SOCK_MAX_CONNECTIONS)) == SOCK_LISTEN_ERR) {
        printf("Error listening connections: (%d) %s\n", 
                errno, 
                strerror(errno));
        exit(0);
    } else {
        printf("Server listening..\n");
        return SOCK_LISTEN_OK;
    }
}

int accept_connection(int sockfd, struct sockaddr_in* cliaddr) {
    socklen_t len = sizeof(cliaddr);
    int connfd = accept(sockfd, (struct sockaddr*)&cliaddr, &len);
    if (connfd == SOCK_ACCEPT_ERR) {
        printf("Server accept failed...\n");
        printf("Error connecting to server socket: (%d) %s\n", errno, strerror(errno));
        exit(0);
    } else {
        printf("Server accepted the client...\n");
        return connfd;
    }
}

int connect_to_socket(int sockfd, struct sockaddr_in* servaddr) {
    int connect_code = connect(sockfd, (struct sockaddr*)servaddr, sizeof(*servaddr));
    if (connect_code == SOCK_CONN_ERR) {
        printf("Error connecting to socket: (%d) %s\n", errno, strerror(errno));
        exit(0);
    } else {
        printf("Connected to socket..\n");
        return SOCK_CONN_OK;
    }
}

int close_socket(int sockfd) {
    int close_code = close(sockfd);
    if (close_code == SOCK_CLOSE_ERR) {
        printf("Error closing socket: %s\n", strerror(errno));
        exit(0);
    } else {
        printf("Successfully closed connection.");
        return SOCK_CLOSE_OK;
    }
}

// Higher level functions

// Ping pong with user input
void ping(int sockfd) {   
    char* buff = heap_buff();
    time(NULL);

    for (;;) {
        load_message(buff);
        exit_if_signalled(buff);
        send_message(sockfd, buff);
        receive_message(sockfd, buff);
    }
    free(buff);
}

void pong(int connfd) {
    char* buff = heap_buff();

    for (;;) {
        receive_message(connfd, buff);
        exit_if_signalled(buff);
        load_message(buff);
        send_message(connfd, buff);
    }
    free(buff);
}

// Send and save a file
void send_msg(int sockfd, Message *msg) {   
    send_structured_message(sockfd, msg);
    printf("Send message: Caller ID=%s, Message ID=%s, Timestamp=%ld, Data=%s\n", 
                      msg->caller_id, msg->message_id, msg->timestamp, msg->data);
}

void receive_msg(int connfd) {
    Message msg;
    receive_structured_message(connfd, &msg);
    printf("Received message: Caller ID=%s, Message ID=%s, Timestamp=%ld, Data=%s\n", 
                      msg.caller_id, msg.message_id, msg.timestamp, msg.data);
}
