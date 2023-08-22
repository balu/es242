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

    // Generate all permutations with a[start] at the beginning.
    permutations(a, n, start+1);

    for (int i = start+1; i < n; ++i) {
        // Now, bring the other elements to the front.
        swap(&a[start], &a[i]);
        permutations(a, n, start+1);
        swap(&a[start], &a[i]);
    }
}

int main()
{
    permutations((int[]){0, 1, 2, 3}, 4, 0);
    return 0;
}
