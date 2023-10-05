#include <cstdio>
#include <vector>

#include "queue.hpp"

struct board {
    int e[3][3];
    int r, c;
};

constexpr int fact(int i)
{
    int p = 1;
    for (int j = 2; j <= i; ++j) {
        p *= j;
    }
    return p;
}

int ord(const board& board)
{
    int seen[10] = { 0 };
    int a = 0;
    int k = 8;

    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            int v = board.e[r][c];
            int o = 0;
            for (int i = 1; i < v; ++i) {
                if (!seen[i]) { ++o; }
            }
            a += o * fact(k);
            --k;
            seen[v] = 1;
        }
    }

    return a;
}

void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}

board up(const board& b)
{
    if (b.r == 0) return b;
    board c = b;
    swap(c.e[b.r-1][b.c], c.e[b.r][b.c]);
    return c;
}

board down(const board& b)
{
    if (b.r == 2) return b;
    board c = b;
    swap(c.e[b.r+1][b.c], c.e[b.r][b.c]);
    return c;
}

board left(const board& b)
{
    if (b.c == 0) return b;
    board c = b;
    swap(c.e[b.r][b.c-1], c.e[b.r][b.c]);
    return c;
}

board right(const board& b)
{
    if (b.c == 2) return b;
    board c = b;
    swap(c.e[b.r][b.c+1], c.e[b.r][b.c]);
    return c;
}

/*
 * Return a shortest path from src to dest.
 */
std::vector<board> solve(const board& src, const board& dest)
{
}

int main()
{
    return 0;
}
