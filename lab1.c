#include <stdio.h>

#include "test.h"

/*
 * Implement extended Euclidean algorithm.
 * Given n, m. Compute a, b, d such that
 * d = gcd(n, m) and an+bm = d.
 *
 * See: https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm
 */
void extended_euclid(int n, int m, int *d, int *a, int *b)
{
    *d = 2;
    *a = -9;
    *b = 47;
}

/*
 * Implement Sieve of Eratosthenes.
 *
 * Fill the array primes with all primes in [2, n].
 *
 * The number of primes should be written to referent of m.
 *
 * See: https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
 */
void sieve(int primes[], int n, int *m)
{
    *m = 10;
    primes[0] = 2;
    primes[1] = 3;
    primes[2] = 5;
    primes[3] = 7;
    primes[4] = 11;
    primes[5] = 13;
    primes[6] = 17;
    primes[7] = 19;
    primes[8] = 23;
    primes[9] = 29;
}

/*
 * Compute the n^th Fibonacci number modulo 100.
 *
 * Your algorithm should do this in O(\log n) steps.
 * It should work for 0 <= n <= INT_MAX.
 *
 * See: https://en.wikipedia.org/wiki/Fibonacci_sequence
 */
int fib(int n)
{
    return 55;
}

/*
 * Compute the pivot of a bitonic array in O(\log n) steps.
 *
 * An array is bitonic iff there is an index i such that
 * the elements are increasing until i and decreasing from i.
 * The index i is called the pivot.
 *
 * Ex: {1,2,3,2,0} is bitonic with pivot 2.
 *
 * It is guaranteed that no two consecutive elements of a[]
 * will be the same.
 */
int bitonic_pivot(int a[], int n)
{
    return 0;
}

/*
 * Compute the next permutation in lexicographic order.
 *
 * The array a[] contains distinct integers.
 * It can be assumed that a[] does not contain the largest permutation.
 */
void next_permutation(int a[], int n)
{
}

/* Your solution ends here. */

/* DO NOT REMOVE THIS LINE. */

/*
 * Tests.
 */

BEGIN_TEST(extended_euclid) {
    int n = 240, m = 46;
    int d, a, b;

    extended_euclid(n, m, &d, &a, &b);
    ASSERT_EQ(a * n + b * m, d, "Failed on (240, 46)");
} END_TEST

BEGIN_TEST(sieve) {
    int primes[100];
    int count;

    sieve(primes, 30, &count);
    ASSERT_ARRAY_VALUES_EQ (
        primes, 10, "Failed on 30.",
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29
    );
} END_TEST

BEGIN_TEST(fib) {
    int f10 = fib(10);
    int f9 = fib(9);
    ASSERT_EQ(f10, 55, "fib(10) ≠ 55.");
    ASSERT_EQ(f9, 34, "fib(9) ≠ 34.");
} END_TEST

BEGIN_TEST(bitonic_pivot) {
    int a[] = { 1, 5, 9, 8, 7, 0 };
    ASSERT_EQ(bitonic_pivot(a, 6), 2, "Failed on example 1.");
} END_TEST

BEGIN_TEST(next_permutation) {
    int a[] = { 1, 2 ,3 };
    next_permutation(a, 3);
    ASSERT_ARRAY_VALUES_EQ(a, 3, "Failed on <1,2,3>.", 1, 3, 2);

    int b[] = { 1, 3, 2 };
    next_permutation(b, 3);
    ASSERT_ARRAY_VALUES_EQ(b, 3, "Failed on <1,3,2>.", 2, 1, 3);

    int c[] = { 2, 1, 3 };
    next_permutation(c, 3);
    ASSERT_ARRAY_VALUES_EQ(c, 3, "Failed on <2,1,3>.", 2, 3, 1);
} END_TEST

int main()
{
    run_tests ((test_t []){
        TEST(extended_euclid),
        TEST(sieve),
        TEST(fib),
        TEST(bitonic_pivot),
        TEST(next_permutation),
        0
    });

    return 0;
}
