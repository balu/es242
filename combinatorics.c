#include <stdio.h>

void print_array(int a[], int n)
{
    for (int i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

/*
 * Print all permutations of a[] of n elements.
 */
void permutations(int a[], int n, int start)
{
    if (start == n-1) {
        print_array(a, n);
        return;
    }
    for (int i = start; i < n; ++i) {
        swap(&a[start], &a[i]);
        permutations(a, n, start+1);
        swap(&a[start], &a[i]);
    }
}

int main()
{
    permutations((int[]){0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}, 14, 0);
    return 0;
}
