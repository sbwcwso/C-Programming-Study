CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
test: $(OBJS)
	gcc -o $@ $(OBJS)
run_test: test
	diff <(./test) answer.txt
.PHONY: clean
clean:
	rm -rf test *.o *.c~ *.h~
