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

void process_permutations(int a[], int n, int start, void (*process_perm)(int a[], int n))
{
    if (start == n-1) {
        (*process_perm)(a, n);
        return;
    }

    // Generate all permutations with a[start] at the beginning.
    process_permutations(a, n, start+1, process_perm);

    for (int i = start+1; i < n; ++i) {
        // Now, bring the other elements to the front.
        swap(&a[start], &a[i]);
        process_permutations(a, n, start+1, process_perm);
        swap(&a[start], &a[i]);
    }
}

int is_derangement(int a[], int n)
{
    for (int i = 0; i < n; ++i) {
        if (a[i] == i) { return 0; }
    }
    return 1;
}

void print_if_derangement(int a[], int n)
{
    if (is_derangement(a, n)) { print_array(a, n); }
}

int main()
{
    process_permutations((int[]){0, 1, 2, 3}, 4, 0, print_if_derangement);
    return 0;
}
