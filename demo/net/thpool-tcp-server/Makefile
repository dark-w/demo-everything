CC = gcc

CFLAGS = -Wall -Werror -O2 -Iinclude
LDFLAGS = -lpthread

all: thpool-tcp-server

thpool-tcp-server: thpool-tcp-server.c lib/thpool.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	@rm -vf thpool-tcp-server

