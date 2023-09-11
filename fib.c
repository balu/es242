#include <stdio.h>

int computed[1000] = { 0 };

int fib(int n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (computed[n] > 0) {
        return computed[n];
    }
    computed[n] = ((fib(n-1)%97) + (fib(n-2)%97))%97;
    return computed[n];
}

int main()
{
    for (int i = 0; i < 1000; ++i) {
        computed[i] = -1;
    }
    printf("%d\n", fib(50));
    return 0;
}
