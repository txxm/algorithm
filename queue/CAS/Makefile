CC = gcc
CFLAGS = -fPIC -shared
TARGET = libcas.so.1

$(TARGET):*.o
	$(CC) $(CFLAGS) -o $(TARGET) $<

%.o:%.c
	$(CC) $(CFLAGS) -c $^

.PHONY:clean
clean:
	rm *.o
