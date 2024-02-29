CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall -Werror

breaker: breaker.c
	$(CC) $(CFLAGS) -o $@ $^

test: breaker
	@./breaker input.txt || (echo "Test Filed!"; exit 1;)
	@echo "Success"

