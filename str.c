#include <stdio.h>

void foo(const char *src)
{
    printf("%p\n", src);
    printf("%d\n", sizeof(src));
    printf("%s\n", src);
    printf("%d\n", src[5]);
    printf("%d\n", *(src+5));
}

int main()
{
    const char *src = "Hello";
    printf("%p\n", &src[0]);
    foo(src);
    return 0;
}
