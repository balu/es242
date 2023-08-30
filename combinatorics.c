#include <stdio.h>
#include <assert.h>

void print_array(int a[], int n)
{
    for (int i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void print_array_1(int a[], int n, void *__data)
{
    print_array(a, n);
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

void generate_permutations(int a[], int n, int start, void *data, void (*process_perm)(int a[], int n, void *data))
{
    if (start == n-1) {
        (*process_perm)(a, n, data);
        return;
    }

    // Generate all permutations with a[start] at the beginning.
    generate_permutations(a, n, start+1, data, process_perm);

    for (int i = start+1; i < n; ++i) {
        // Now, bring the other elements to the front.
        swap(&a[start], &a[i]);
        generate_permutations(a, n, start+1, data, process_perm);
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

void count_if_derangement(int a[], int n, void *data)
{
    int *nderangements = (int *)data; // cast void * to int *
    if (is_derangement(a, n)) { ++(*nderangements); }
}

typedef struct {
    int m;
    int *a; // read about array-to-pointer decay in C/C++.
} perm_t;

void store_if_0(int a[], int n, void *data)
{
    perm_t *p = (perm_t *)data;
    if (p->m < 0) return;
    if (p->m > 0) {
        --(p->m);
        return;
    }
    assert(p->m == 0);
    --(p->m);
    for (int i = 0; i < n; ++i) {
        p->a[i] = a[i];
    }
}

int main()
{
    int nderangements4 = 0;
    int nderangements5 = 0;

    generate_permutations((int[]){0, 1, 2, 3}, 4, 0, &nderangements4, count_if_derangement);
    printf("d(4) = %d\n", nderangements4);
    generate_permutations((int[]){0, 1, 2, 3, 4}, 5, 0, &nderangements5, count_if_derangement);
    printf("d(5) = %d\n", nderangements5);

    generate_permutations((int[]){0, 1, 2}, 3, 0, NULL, print_array_1);

    printf("===\n");
    int b[3];
    perm_t p = { .m = 3, .a = b };
    generate_permutations((int[]){0, 1, 2}, 3, 0, &p, store_if_0);
    print_array(p.a, 3);

    return 0;
}
