CC = gcc

CFLAGS = -Wall -Werror -O2
LDFLAGS = 

all: epoll-tcp-server

tcp-server: epoll-tcp-server.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	@rm -vf epoll-tcp-server

