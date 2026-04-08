# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -I./include

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
DATA_DIR = data

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Executable name
TARGET = gym_management

# Default target
all: $(TARGET)

# Create directories
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(DATA_DIR):
	mkdir -p $(DATA_DIR)

# Link object files to create executable
$(TARGET): $(BUILD_DIR) $(DATA_DIR) $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Clean all including data
cleanall: clean
	rm -rf $(DATA_DIR)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean cleanall run