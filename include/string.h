#pragma once

#include "types.h"

char *str_n_cpy(char *, const char *, size_t);

size_t str_n_len(const char *, size_t);

size_t str_len(const char *);

int str_cmp(const char *, const char *);

int str_n_cmp(const char *, const char *, size_t);

char *str_cpy(char *, const char *);

char *str_cat(char *, const char *);

char *str_n_cat(char *, const char *, size_t);

int mem_cmp(const void *, const void *, size_t);

void *mem_cpy(void *, const void *, size_t);

void *mem_move(void *, const void *, size_t);

void *mem_set(void *, int, size_t);

char *str_str_kmp(const char *, const char *);

char *str_str(const char *, const char *);
