CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
test: $(OBJS)
	gcc -o $@ $(OBJS)
.PHONY: clean
clean:
	rm -rf test *.o *.c~ *.h~
