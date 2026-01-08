CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c23
TARGET = fatalspin
SOURCE = main.c

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET)

.PHONY: clean
