#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdint.h>
#include <time.h>

#define MESSAGE_SIZE 256
#define UUID_SIZE 36
#define CALLER_ID_SIZE 32
#define FUNCTION_NAME_SIZE 32


typedef struct {
    char caller_id[CALLER_ID_SIZE];
    char message_id[UUID_SIZE];
    time_t timestamp;
    char data[MESSAGE_SIZE];
    char function_name[FUNCTION_NAME_SIZE];
} Message;

// Function prototypes
void send_message(int sockfd, const void *buff);
void receive_message(int sockfd, char *buffer);
void send_structured_message(int sockfd, const void *msg);
void receive_structured_message(int sockfd, const void *msg);
void generate_uuid(char *uuid);
time_t get_current_timestamp();
Message create_default_client_message();
Message create_default_server_message();

// typedef void (*send_function_t)(int, const void *);
// typedef void (*message_function_t)(Message *);

// Use int socketfd to send a message
typedef void (*message_function_t)(int, const void *);

// Function to find a function by name
message_function_t get_function_by_name(const char *name);

#endif // MESSAGE_H
