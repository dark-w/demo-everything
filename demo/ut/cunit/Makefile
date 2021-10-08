include config.mk

CC = gcc

CFLAGS = -Wall -Werror -O2 
LDFLAGS = 

all: main test

main: main.c foo.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

test: test.c foo.c
	$(CC) $(CFLAGS) $(CUNIT_CFLAGS) $^ -o $@ $(CUNIT_LDFLAGS)
	
check:
	@./test
	@echo check done

clean:
	@rm -vf main test

distclean: clean
	@rm -vf config.mk

