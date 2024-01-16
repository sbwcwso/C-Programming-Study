CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall -Werror

rotate-matrix: rotate.o read-matrix.o
	$(CC) $(CFLAGS) -o $@ $^

rotate: rotate.c
	$(CC) $(CFLAGS) -c $^

test: rotate-matrix 
	@diff <(./rotate-matrix sample.txt) ./sample.out || (echo "Test Failed"; exit 1)
	@echo "Success"
