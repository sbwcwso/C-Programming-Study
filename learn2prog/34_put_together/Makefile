CFLAGS=-Wall -Werror -std=gnu99 -pedantic -ggdb3
SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(SRCS))
PROGRAM=count_values

$(PROGRAM): $(OBJS)
	gcc $(CFLAGS) -o $@ $(OBJS)

%.o: %.c 
	gcc -c $(CFLAGS) $<

clean:
	rm -f $(OBJS) $(PROGRAM) *~ *.counts

test: $(PROGRAM)
	@(./count_values kvs1.txt list1a.txt list1b.txt \
	&& diff list1a.txt.counts list1a.txt.ans \
	&& diff list1b.txt.counts list1b.txt.ans \
	&& echo "first test case success.") \
	|| (echo "first test case failed."; exit 1)
	@(./count_values kvs2.txt list2a.txt list2b.txt list2c.txt \
	&& diff list2a.txt.counts list2a.txt.ans \
	&& diff list2b.txt.counts list2b.txt.ans \
	&& diff list2c.txt.counts list2c.txt.ans\
	&& echo "second test case success.") \
	|| (echo "second test case failed."; exit 1)

counts.o: counts.h
outname.o: outname.h
kv.o: kv.h
main.o: kv.h
main.o: outname.h
main.o: counts.h
