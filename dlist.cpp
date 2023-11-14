template <typename T>
struct dlistnode {
    T data;
    dlistnode<T> *prev, *next;
};

template <typename T>
dlistnode<T> *unlink(dlistnode<T> *p)
{
    assert(p);
    auto q = p->prev;
    auto r = p->next;
    q->next = r;
    r->prev = q;
    return p;
}

template <typename T>
dlistnode<T> *insert_before(dlistnode<T> *current, dlistnode<T> *new_node)
{
    auto q = current->prev;
    q->next = new_node;
    current->prev = new_node;
    new_node->prev = q;
    new_node->next = current;
    return new_node;
}
