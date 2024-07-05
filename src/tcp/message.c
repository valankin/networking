#include "message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// Function to generate a random hexadecimal character
char random_hex_char() {
    const char hex_digits[] = "0123456789abcdef";
    return hex_digits[rand() % 16];
}

// Function to generate a UUID (version 4 UUID)
void generate_uuid(char *uuid) {
    // Seed the random number generator
    srand((unsigned int)time(NULL));

    // Fill the UUID string with random hexadecimal characters
    for (int i = 0; i < 36; i++) {
        switch (i) {
            case 8:
            case 13:
            case 18:
            case 23:
                uuid[i] = '-';
                break;
            case 14:
                uuid[i] = '4'; // Version 4 UUID
                break;
            case 19:
                uuid[i] = "89ab"[rand() % 4]; // The variant specified in RFC 4122
                break;
            default:
                uuid[i] = random_hex_char();
                break;
        }
    }

    uuid[36] = '\0'; // Null-terminate the UUID string
}

// Function to get the current timestamp
time_t get_current_timestamp() {
    return time(NULL);
}

// Function to create a default client message
Message create_default_client_message() {
    Message msg;
    strncpy(msg.caller_id, "Client", CALLER_ID_SIZE);
    generate_uuid(msg.message_id);
    msg.timestamp = get_current_timestamp();
    strncpy(msg.data, "Default client message", MESSAGE_SIZE);
    strncpy(msg.function_name, "send_structured_message", FUNCTION_NAME_SIZE);

    return msg;
}

// Function to create a default server message
Message create_default_server_message() {
    Message msg;
    strncpy(msg.caller_id, "Server", CALLER_ID_SIZE);
    generate_uuid(msg.message_id);
    msg.timestamp = get_current_timestamp();
    strncpy(msg.data, "Default server message", MESSAGE_SIZE);
    return msg;
}


void send_message(int sockfd, const void *buff) {
    const char *buffer = (const char *)buff;
    if (write(sockfd, buffer, strlen(buffer) + 1) < 0) {
        perror("Error sending message");
        exit(EXIT_FAILURE);
    }
}


// Function to receive a simple message into a char buffer
void receive_message(int sockfd, char *buff) {
    if (read(sockfd, buff, MESSAGE_SIZE) < 0) {
        perror("Error receiving message");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Function to receive a structured message
 * 
 * @param sockfd - socket file descriptor returned by unistd::socket(...)
 * @param msg - Pointer to a void message buffer
 */
void receive_structured_message(int sockfd, const void *msg) {
    if (read(sockfd, msg, sizeof(Message)) < 0) {
        perror("Error receiving message");
        exit(EXIT_FAILURE);
    }
}

void send_structured_message(int sockfd, const void *msg) {
    const Message *message = (const Message *)msg;
    if (write(sockfd, message, sizeof(Message)) < 0) {
        perror("Error sending message");
        exit(EXIT_FAILURE);
    }
}

// Forward declarations of message sending functions
void send_message(int sockfd, const void *buff);

void send_structured_message(int sockfd, const void *msg);






// /**
//  * @brief Defines function_map_t type
//  * @param name - function name
//  * @param func - function pointer
//  */
// typedef struct {
//     const char *name;
//     message_function_t func;
// } function_map_t;



// typedef void (*message_function_t)(int, const void *);

/**
 * @brief Get the function by name object
 * 
 * @param name - function name passed in a message
 * @return message_function_t - socketfd and message
 */
message_function_t get_function_by_name(const char *name) {
    static struct {
        const char *name;
        message_function_t func;
    } function_map[] = {
        {"send_message", send_message},
        {"send_structured_message", send_structured_message}
    };

    for (int i = 0; i < sizeof(function_map) / sizeof(function_map[0]); i++) {
        if (strcmp(function_map[i].name, name) == 0) {
            return function_map[i].func;
        }
    }
    return NULL;
}
