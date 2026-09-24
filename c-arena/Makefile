CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = main

SRCS = $(wildcard *.c)

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET) *.out main *.o