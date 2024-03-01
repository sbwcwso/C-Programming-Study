CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall -Werror

rotateMatrix: rotateMatrix.c
	$(CC) $(CFLAGS) -o $@ $^

test: rotateMatrix
	@diff <(./rotateMatrix sample.txt) sample.out || (echo "TEST Failed!"; exit 1;)
	@echo "Success"

