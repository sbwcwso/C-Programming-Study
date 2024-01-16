CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall -Werror

test: test.c
	$(CC) $(CFLAGS) -o $@ $^

run-test: test
	@diff <(./test) ./answer.txt || (echo "Test Failed"; exit 1;)
	@echo "Success"
