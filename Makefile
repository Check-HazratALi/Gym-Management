CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11
TARGET  = gym_management
SRC     = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) *.dat

.PHONY: all clean
