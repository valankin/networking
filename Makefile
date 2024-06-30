
# Configuration
## CC specifies which compiler we're using
CC = gcc

## COMPILER_FLAGS specifies the additional compilation options
### -w suppresses all warnings
COMPILER_FLAGS = -w

## LINKER_FLAGS specifies the libraries we're linking against
# LINKER_FLAGS = -l...

## Language standard
STD_C=c17




# Socket communication

## Server
SERVER_OBJ = server
SERVER_SOURCE = server.c

server: $(SERVER_SOURCE)
	$(CC) -std=$(STD_C) -o $(SERVER_OBJ) $(SERVER_SOURCE)


## Client
CLIENT_OBJ = client
CLIENT_SOURCE = client.c

client: $(CLIENT_SOURCE)
	$(CC) -std=$(STD_C) -o $(CLIENT_OBJ) $(CLIENT_SOURCE)



# TCP Server - Client

## TCP Server
TCP_SERVER_OBJ = tcp_server
TCP_SERVER_SOURCE = tcp_server.c

tcp_server: $(TCP_SERVER_SOURCE)
	$(CC) -std=$(STD_C) -o $(TCP_SERVER_OBJ) $(TCP_SERVER_SOURCE)


## TCP Client
TCP_CLIENT_OBJ = tcp_client
TCP_CLIENT_SOURCE = tcp_client.c

client: $(TCP_CLIENT_SOURCE)
	$(CC) -std=$(STD_C) -o $(TCP_CLIENT_OBJ) $(TCP_CLIENT_SOURCE)