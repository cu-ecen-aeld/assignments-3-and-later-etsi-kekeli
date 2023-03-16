# CROSS_COMPILE = aarch64-none-linux-gnu-
CC = gcc
CFLAGS = -Wall
default: finder-app/writer.c
	$(CROSS_COMPILE)$(CC) -c $^ -o finder-app/writer.o
	$(CROSS_COMPILE)$(CC) -o finder-app/writer finder-app/writer.o
clean: 
	find ./finder-app -type f \( -name *.o -o -name writer \) -delete