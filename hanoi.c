#include <stdio.h>

/*
 * Print steps for moving n disks from peg 'from'
 * to peg 'to' by using the remaining peg as an
 * intermediate peg.
 *
 * Pegs are numbered 0, 1, 2.
 *
 * Note: All base cases are handled.
 *       All recursive calls are to smaller instances.
 */
void hanoi(int n, int from, int to)
{
    if (n == 1) {
        printf("Shift 1 from %d to %d\n", from, to);
        return;
    }
    int intermediate = 3 - (from + to);
    hanoi(n-1, from, intermediate);
    printf("Shift %d from %d to %d\n", n, from, to);
    hanoi(n-1, intermediate, to);
}

int main()
{
    hanoi(3, 0, 2);
    return 0;
}
