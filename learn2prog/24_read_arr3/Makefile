CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall -Werror

test: test.c
	gcc $(CFLAGS) -o $@ $^

compare: test
	@diff <(./test) answer.txt || (echo "Compare Failed"; exit 1;)
	@echo "Compare success"
