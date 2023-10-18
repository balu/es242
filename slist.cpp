#include <cstdio>

template <typename T>
struct SListNode
{
    T data;
    SListNode<T>* next;
};

template <typename T>
SListNode<T>* new_node(T val)
{
    auto p = new SListNode<T>;
    p->data = val;
    p->next = 0;
    return p;
}

template <typename T>
SListNode<T>* insert_after(SListNode<T>* pos, T val)
{
    auto q = new_node(val);
    q->next = pos->next;
    pos->next = q;
    return q;
}

void print_int_list(SListNode<int>* first)
{
    if (first == 0) return;
    auto current = first;
    while (current) {
        printf("%d, ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main()
{
    auto xs = new_node(1);
    insert_after(insert_after(insert_after(xs, 2), 4), 5);
    print_int_list(xs);
    return 0;
}
