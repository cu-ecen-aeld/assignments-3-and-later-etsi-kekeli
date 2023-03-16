# CROSS_COMPILE = aarch64-none-linux-gnu-
CC = gcc
CFLAGS = -Wall
default: writer.c
	$(CROSS_COMPILE)$(CC) -c $^ -o writer.o
	$(CROSS_COMPILE)$(CC) -o writer writer.o
clean: 
	find . -type f \( -name *.o -o -name writer \) -delete