CPP = g++-10

objs = lambda coroutine

all: $(objs)

COMMON_CFLAGS = -Wall -Werror -O2
COROUTINE_CFLAGS = -fcoroutines $(COMMON_CFLAGS)
COROUTINE_LDFLAGS = -lpthread

lambda: lambda.cc
	$(CPP) $(COMMON_CFLAGS) $^ -o $@

coroutine: coroutine.cc
	$(CPP) $(COROUTINE_CFLAGS) $^ -o $@ $(COROUTINE_LDFLAGS)

clean:
	@rm -vf $(objs)

distclean: clean

.PHONY: clean distclean
	
