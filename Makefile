
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
	$(CC) -std=$(STD_C) -o $(SERVER_OBJ) $(SERVER_SOURCE)
