# Example Makefile

# Compilation: Each .cpp file is compiled into an object file (.o).
# Linking: All object files are linked together to create the final executable.

# Variables
CXX = clang++
CXXFLAGS = -g -Wall

TARGET = debug

SRC_DIR = src
BUILD_DIR = build

# Find every cpp file in ./src.
SRCS = $(shell find $(SRC_DIR) -name '*.cpp')
# Rename every .cpp into .o file.
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)


# Default target
all: $(BUILD_DIR)/$(TARGET)

# Ensure the build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Linking
#
# Purpose: Combines object files into a single executable. 
# It resolves references between object files, 
# ensuring that all functions and variables have definitions.
#
# Process: The linker takes all the object files and libraries specified, 
# resolves all the symbol references, and produces the final executable.
# 
# Output: The final executable file (e.g., debug).
#
# This line links all the object files (specified by $(OBJS)) 
# to produce the final executable (specified by $@).
# 
# '-o $@' This tells the compiler to output the result to the file specified by $@.
# $@ is an automatic variable in Makefiles that represents the target name. 
# In this case, it will be the path to the final executable, e.g., build/debug.
$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)


# Compilation - Create object files
#
# Purpose: Converts source code files (.cpp files) into object files (.o files).
#
#
# Process: Each source file is compiled independently into an object file. 
# This involves translating the human-readable code into machine code and 
# performing syntax and semantic checks.
#
#
# Output: Object files (.o), which contain machine code and 
# information about unresolved symbols (such as functions or 
# variables declared but not defined in the same file).
#
#
# Scripting: This line compiles the source file (specified by $<) 
# into an object file (specified by $@).
# 
# -c: 
# This flag tells the compiler to compile the source file to an object file, 
# but not to link it.
#
# -o $@: 
# This tells the compiler to output the result to the file specified by $@.
# 
# $@: 
# Is an automatic variable in Makefiles that represents the target name. 
# In this case, it will be the path to the object file, e.g., build/debug.o.
# 
# $<: 
# This is an automatic variable that represents 
# the first prerequisite (the source file being compiled).
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Clean up
clean:
	rm -rf $(BUILD_DIR)

# Phony targets
.PHONY: all clean


