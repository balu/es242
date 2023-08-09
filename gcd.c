#include <stdio.h>
#include <limits.h>

int gcd(int n, int m)
{
    if (n < m) return gcd(m, n);

    for (int d = m; d > 0; --d) {
        if (n % d == 0 && m % d == 0) return d;
    }
    return n;
}

int average(int a, int b)
{
    return (a+b)/2;
}

int main()
{
    printf("gcd(%d, %d) = %d\n", 24, 54, gcd(24, 54));

    printf("INT_MAX = %d\n", INT_MAX);
    /*  printf("gcd(INT_MAX, INT_MAX*INT_MAX) = %d\n", gcd(INT_MAX, INT_MAX*INT_MAX)); */
    printf("%d, %d, %d\n", average(10, 4), average(5, 4), average(INT_MAX, INT_MAX));

    int a;
    printf("%d\n", a);
    return 0;
}
