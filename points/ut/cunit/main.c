#include "foo.h"

int printf(const char *fmt, ...);

int main(int argc, char **argv)
{
    int a = 11;
    int b = 22;
    int r = add(a, b);

    printf("%d + %d = %d\n", a, b, r);

    return 0;
}
