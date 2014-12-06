CC=clang
CFLAGS=-Wall -g

BINS=Client Server

all: $(BINS)

Client: Client.c Common.h
	$(CC) $(CFLAGS) -o Client Client.c

Server: Server.c Common.h
	$(CC) $(CFLAGS) -o Server Server.c

clean:
	rm $(BINS)

