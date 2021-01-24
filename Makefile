CC = gcc
LD = ld

CFLAGS = -Wall -Werror -O2 -Iinclude -Iinclude/sokoban
# LDFLAGD

MAKEFLAGS = --no-print-directory

builtin-obj = built-in.o

export CC LD CFLAGS MAKEFLAGS
export builtin-obj

dir-y = src lib sokoban
subdir-objs = $(foreach n, $(dir-y), $(n)/$(builtin-obj))

include build/rules/common.mk

all: push-the-box 

push-the-box: $(subdir-objs)
	$(CC) $(CFLAGS) $^ -o $@

$(subdir-objs): $(dir-y)

$(dir-y):
	make $(obj_build)$@

clean:
	@for dir in $(dir-y); do \
		 make $(obj_build)$$dir clean; \
	 done
	@rm -vf push-the-box

.PHONY: $(dir-y) push-the-box 
