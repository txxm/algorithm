CC = gcc
CFLAGS = -Wall -g -std=gnu99 -lpthread

all = main.o ringbuf.o

main:$(all)
	$(CC) $(CFLAGS) -o $@ $^

%.o:%.c
	$(CC) $(CFLAGS) -c $<

.PHONY:clean
clean:
	rm -f *.o
