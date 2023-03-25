# CROSS_COMPILE = aarch64-none-linux-gnu-
CC = gcc
CFLAGS = -Wall
writer: writer.c
	$(CROSS_COMPILE)$(CC) -c $^ -o writer.o
	$(CROSS_COMPILE)$(CC) -o $@ writer.o
clean: 
	find . -type f \( -name *.o -o -name writer \) -delete