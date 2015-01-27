
CC ?= gcc
CFLAGS += -Wall
#LDFLAGS +=

all: test

overflow.o: overflow.c
	$(CC) $(CFLAGS) $(LDFLAGS) overflow.c -c -o overflow.o

test.o: test.c
	$(CC) $(CFLAGS) $(LDFLAGS) test.c -c -o test.o

test: test.o overflow.o
	$(CC) $(CFLAGS) $(LDFLAGS) test.o overflow.o -lutil -o test

clean:
	@git clean -xdf
