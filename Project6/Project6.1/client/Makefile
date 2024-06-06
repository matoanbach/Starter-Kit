CC=g++
CFLAGS=-I
CFLAGS+=-Wall
FILES=client.cpp

server: $(FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(FILES)

clean:
	rm -f *.o client

all: client