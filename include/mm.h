#pragma once

#include "types.h"

int heap_init(void);

void *my_malloc(size_t size);

void my_free(void *p);

struct list_head *get_heap_head_list(void);
