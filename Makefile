
# Compiler configuration

## CC specifies which compiler we're using
CC = clang

## COMPILER_FLAGS specifies the additional compilation options
### -w suppresses all warnings
COMPILER_FLAGS = -w

## LINKER_FLAGS specifies the libraries we're linking against
# LINKER_FLAGS = -l...

## Language standard
STD_C=c17


# TCP communication

## Source sonfiguration
TCP_HOME = ./src/tcp
TCP_INCLUDE = $(TCP_HOME)/include

### Server Configuration
TCP_SERVER_SOURCE = main.c $(TCP_HOME)/tcp_server.c $(TCP_HOME)/tcp_functions.c 
TCP_SERVER_OBJ = tcp_server

### Client configuration
TCP_CLIENT_SOURCE = $(TCP_HOME)/tcp_client.c $(TCP_HOME)/tcp_functions.c
TCP_CLIENT_OBJ = tcp_client

## Compile entrypoints
### Server
tcp_server: $(TCP_SERVER_SOURCE)
	$(CC) -std=$(STD_C) $(COMPILER_FLAGS) \
		-I$(TCP_INCLUDE) \
		-o $(TCP_SERVER_OBJ) \
		$(TCP_SERVER_SOURCE)
### Client
tcp_client: $(TCP_CLIENT_SOURCE)
	$(CC) -std=$(STD_C) $(COMPILER_FLAGS) \
		-I$(TCP_INCLUDE) \
		-o $(TCP_CLIENT_OBJ) \
		$(TCP_CLIENT_SOURCE)