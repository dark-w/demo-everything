CC = gcc

CFLAGS = -Wall -Werror -O2
LDFLAGS = -lpthread

all: thpool

thpool: thpool.c example.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	@rm -vf thpool

