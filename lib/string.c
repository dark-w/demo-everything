#include "string.h"

#include <stdlib.h>

#ifdef LIB_STRING_DEBUG
#include  <stdio.h>
#define SPRINTF(fmt, args...) printf(fmt, ##args)
#else
#define SPRINTF(fmt, args...)
#endif

size_t str_len(const char *src)
{
    const char *iter;

    for (iter = src; *iter; iter++);

    return iter - src;
}

size_t str_n_len(const char *src, size_t count)
{
    const char *iter;

    for (iter = src; *iter && count; iter++, count--);

    return iter - src;
}

char *str_cpy(char *dst, const char *src)
{
    char *iter = dst;

    while ((*iter = *src) != '\0') {
        iter++;
        src++;
    }

    return dst;
}

char *str_n_cpy(char *dst, const char *src, size_t count)
{
    char *iter = dst;
    size_t n = 0;

    while ((n < count) && (*iter = *src)) {
        iter++;
        src++;
        n++;
    }

    while (n < count) {
        *iter++ = '\0';
        n++;
    }

    return dst;
}

int str_cmp(const char *pstr1, const char *pstr2)
{
    while (*pstr1 == *pstr2) {
        if ('\0' == *pstr1)
            return 0;

        pstr1++;
        pstr2++;
    }

    return *pstr1 - *pstr2;
}

int str_n_cmp(const char *pstr1, const char *pstr2, size_t count)
{
    size_t n = 1;

    while (*pstr1 == *pstr2) {
        if (('\0' == *pstr1) || (n == count))
            return 0;

        pstr1++;
        pstr2++;
        n++;
    }

    return *pstr1 - *pstr2;
}

char *str_cat(char *dst, const char *src)
{
    char *iter;

    for (iter = dst; *iter; iter++);

    while ((*iter = *src) != '\0') {
        iter++;
        src++;
    }

    return dst;
}

char *str_n_cat(char *dst, const char *src, size_t count)
{
    char *iter;
    size_t n = 0;

    for (iter = dst; *iter; iter++);

    while (n < count && (*iter = *src)) {
        iter++;
        src++;
        n++;
    }

    while (n < count) {
        *iter = '\0';
        iter++;
        n++;
    }

    return dst;
}

/* kmp solution, the time complexity of the algorithm is the O(N + M) */
char *str_str_kmp(const char *haystack, const char *needle)
{
    char *result = NULL;

    // get the next array
    const int needle_len = str_len(needle);
    int *next = (int *)calloc(needle_len, sizeof(*next));

    SPRINTF("next[0]: %d\n", next[0]);
    for (int i = 1, j = 0; i < needle_len; i++) {
       while (j > 0 && needle[i] != needle[j]) {
           j = next[j - 1];
       }

       if (needle[i] == needle[j]) {
           next[i] = j + 1;
           j++;
       }

       SPRINTF("next[%d]: %d\n", i, next[i]);
    }

    // find
    int i = 0, j = 0;
    const int haystack_len = str_len(haystack);
    while (i < haystack_len) {
        if (needle[j] == haystack[i]) {
            i++;
            j++;     
        } else {
            if (!j) i++;
            else j = next[j - 1];
        }
    
        if ('\0' == needle[j]) {
            result = (char *)&haystack[i - needle_len];

            break;
        }
    }

    SPRINTF("result: %s\n", result);

    free(next);
    return result;
}

/* violent solution, the time complexity of the algorithm is the O(N * M) */
char *str_str(const char *haystack, const char *needle)
{
    const char *p, *q;

    p = haystack;
    q = needle;
    while (*p) {
        int i = 0;
        while (q[i] && q[i] == p[i]) i++;
        if (q[i] == '\0')
            return (char *)p;
        p++;
    }

    return NULL;
}

void *mem_cpy(void *dst, const void *src, size_t count)
{
    uint8_t *d;
    const uint8_t *s;

    d = dst;
    s = src;

    while (count > 0) {
        *d++ = *s++;
        count--;
    }

    return dst;
}

void *mem_move(void *dst, const void *src, size_t count)
{
    uint8_t *d;
    const uint8_t *s;

    if (dst < src) {
        d = dst;
        s = src;

        while (count > 0) {
            *d++ = *s++;
            count--;
        }
    } else {
        d = dst + count;
        s = src + count;

        while (count > 0) {
            *--d = *--s;
            count--;
        }
    }

    return dst;
}

void *mem_set(void *src, int c, size_t count)
{
    char *s = src;

    while (count) {
        *s = c;

        s++;
        count--;
    }

    return src;
}

int mem_cmp(const void* dst, const void* src, size_t count)
{
    const uint8_t *s, *d;

    d = dst;
    s = src;

    while (count > 0) {
        if (*d != *s)
            return *d - *s;

        s++;
        d++;

        count--;
    }

    return 0;
}
