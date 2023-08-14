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

int euclid_gcd(int n, int m)
{
    if (n < m) {
        int t = n;
        n = m;
        m = t;
    }

    while (m) {
        int r = n % m;
        n = m;
        m = r;
    }

    return n;
}

int lcm(int n, int m)
{
    return (n/euclid_gcd(n, m))*m;
}

struct gcdlcm_result {
    int lcm;
    int gcd;
};

struct gcdlcm_result euclid_gcdlcm(int n, int m)
{
    struct gcdlcm_result r;
    r.gcd = euclid_gcd(n, m);
    r.lcm = (n/r.gcd)*m;
    return r;
}

int main()
{
    printf("gcd(%d, %d) = %d\n", 24, 54, gcd(24, 54));

    printf("INT_MAX = %d\n", INT_MAX);

    /*
      The following code is invalid since INT_MAX*INT_MAX is not
      representable in an int.
     */
#if 0
    printf ("gcd(INT_MAX, INT_MAX*INT_MAX) = %d\n",
            gcd(INT_MAX, INT_MAX*INT_MAX)
    );
#endif

    /* The following is OK. */
    printf("%d, %d\n", average(10, 4), average(5, 4));

    /* The following is invalid due to overflow. */
#if 0
    printf("%d\n", average(INT_MAX, INT_MAX));
#endif

    /* Inefficient. Runs Euclid's algorithm twice. */
    printf("%d %d\n", euclid_gcd(24, 54), lcm(24, 54));

    /* Efficient. Runs Euclid's algorithm only once. */
    struct gcdlcm_result r = euclid_gcdlcm(24, 54);
    printf("%d %d\n", r.gcd, r.lcm);

    /*
      Error. Unnecessary overflow.
      The function will compute lcm even though we don't
      use it.
    */
#if 0
    printf("%d\n", euclid_gcdlcm(INT_MAX, INT_MAX-1).gcd);
#endif

    /* The following is invalid. We print an undefined value. */
#if 0
    int a;
    printf("%d\n", a);
#endif

    return 0;
}
