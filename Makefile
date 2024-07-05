# Root Makefile



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

# Load environment variables
export_env:
	@. ./load_env.sh && echo "DB_HOST is $$DB_HOST"


# TCP communication

## Source sonfiguration
TCP_HOME = ./src/tcp
TCP_INCLUDE = $(TCP_HOME)/include

# Ensure the build directory exists
BUILD_DIR = build

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# When compiling and linking separately, use these targets:
# SRCS = $(shell find $(SRC_DIR) -name '*.cpp')
# OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
# TCP_SERVER_OBJECTS = $(TCP_SERVER_SOURCES:%.c=build/%.o)
# TCP_CLIENT_OBJECTS = $(TCP_CLIENT_SOURCES:%.c=build/%.o)

### Server Configuration
TCP_SERVER_SOURCE = $(TCP_HOME)/tcp_server.c $(TCP_HOME)/tcp_functions.c $(TCP_HOME)/message.c
TCP_SERVER_TARGET = $(BUILD_DIR)/tcp_server

### Client configuration
TCP_CLIENT_SOURCE = $(TCP_HOME)/tcp_client.c $(TCP_HOME)/tcp_functions.c $(TCP_HOME)/message.c
TCP_CLIENT_TARGET = $(BUILD_DIR)/tcp_client

## Compile targets
### Server
tcp_server: export_env $(BUILD_DIR) $(TCP_SERVER_SOURCE)
	@. ./load_env.sh && $(CC) -std=$(STD_C) $(COMPILER_FLAGS) \
		-I$(TCP_INCLUDE) \
		-o $(TCP_SERVER_TARGET) \
		$(TCP_SERVER_SOURCE)

### Client
tcp_client: export_env $(BUILD_DIR) $(TCP_CLIENT_SOURCE)
	@. ./load_env.sh && $(CC) -std=$(STD_C) $(COMPILER_FLAGS) \
		-I$(TCP_INCLUDE) \
		-o $(TCP_CLIENT_TARGET) \
		$(TCP_CLIENT_SOURCE)

### Combined target
tcp: tcp_server tcp_client

# Clean up build artifacts
clean:
	rm -rf $(BUILD_DIR)



.PHONY: tcp tcp_server tcp_client clean export_env