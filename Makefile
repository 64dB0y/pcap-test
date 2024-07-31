# Makefile for building the pcap-test project

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra

# Include paths
INCLUDES =

# Libraries to link
LIBS = -lpcap

# Source files
SRCS = pcap-test.c

# Output executable
TARGET = pcap-test

# Build target
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LIBS)

# Clean up build files
clean:
	rm -f $(TARGET)
