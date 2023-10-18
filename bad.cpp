/* Function local vs dynamic. */

#include <cstdio>

int *foo()
{
    int a { 42 };
    return &a;
}

int *bar()
{
    int *p = new int;
    *p = 42;
    return p;
}

int main()
{
    // int *p = foo();
    // printf("%d\n", *p);
    int *q = bar();
    printf("%d\n", *q);
    delete q;
    return 0;
}
