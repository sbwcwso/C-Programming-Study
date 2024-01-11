CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall -Werror
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
test: $(OBJS)
	gcc -o $@ $(OBJS) $(CFLAGS)
run_test: test
	@diff <(./test) answer.txt || (echo "Test filed"; exit 1;)
	@echo "Success"
.PHONY: clean
clean:
	rm -rf test *.o *.c~ *.h~
