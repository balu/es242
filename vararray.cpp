#include <cstdio>

int *read_array(int n)
{
    int *p = new int[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &p[i]);
    }
    return p;
}

void print_array(int *p, int n)
{
    for (int i = 0; i < n; ++i) {
        printf("%d ", p[i]);
    }
    printf("\n");
}

int main()
{
    int n;

    scanf("%d", &n);

    int *a = read_array(n);

    print_array(a, n);

    delete[] a;

    return 0;
}
