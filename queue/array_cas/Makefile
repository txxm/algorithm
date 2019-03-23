CC = gcc
CFLAGS = -g -Wall -fPIC -shared
INCLUDE = -I ./
TARGET = libcasarray.so.1
SRC = $(wildcard *.c)
OBJ = $(patsubst *.c, *.o, $(SRC))
HEAD = casarray.h
HEADPATH = /usr/include
LIBPATH = /usr/lib64

RM = rm
COPY = cp

$(TARGET):$(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $<

.PHONY:clean
clean:
	$(RM) -rf *.o $(TARGET)

install:
	$(COPY) $(HEAD) $(HEADPATH) -f
	$(COPY) $(TARGET) $(LIBPATH) -f

uninstall:
	$(RM) $(HEADPATH)/$(HEAD) -f
	$(RM) $(LIBPATH)/$(TARGET) -f
