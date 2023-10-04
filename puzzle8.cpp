#include <cstdio>

#include "queue.hpp"

int main()
{
    queue<int, 5> q;
    enqueue(q, 3);
    enqueue(q, 1);
    enqueue(q, 5);
    printf("%d\n", dequeue(q));
    enqueue(q, 4);
    printf("%d\n", dequeue(q));
    printf("%d\n", dequeue(q));
    printf("%d\n", dequeue(q));
    assert(is_empty(q));
    return 0;
}
