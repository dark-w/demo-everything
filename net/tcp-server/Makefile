CC = gcc

CFLAGS = -Wall -Werror -O2
LDFLAGS = -lpthread

all: tcp-server

tcp-server: tcp-server.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	@rm -vf tcp-server

