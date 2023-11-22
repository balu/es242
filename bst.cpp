#include <iostream>
#include <cassert>

using namespace std;

template <typename K, typename V>
struct bstnode {
    K k;
    V v;
    bstnode<K, V> *left;
    bstnode<K, V> *right;
};

template <typename K, typename V>
bstnode<K, V> *new_node(K k, V v)
{
    auto b = new bstnode<K, V>;
    b->k = k;
    b->v = v;
    b->left = b->right = NULL;
    return b;
}

template <typename K, typename V>
struct bst {
    bstnode<K, V> *root;
};

template <typename K, typename V>
bst<K, V> empty()
{
    bst<K, V> b;
    b.root = NULL;
    return b;
}

template <typename K, typename V>
struct search_result {
    bstnode<K, V> *parent;
    bstnode<K, V> *actual;
};

template <typename K, typename V>
static search_result<K, V> search(bstnode<K, V> *p, K key)
{
    bstnode<K, V> *q = p;
    while (p && p->k != key) {
        q = p;
        if (p->k < key) {
            p = p->right;
        } else {
            p = p->left;
        }
    }
    return { q, p };
}

template <typename K, typename V>
bool member(const bst<K, V> &d, K key)
{
    auto r = search(d.root, key);
    return r.actual != NULL;
}

template <typename K, typename V>
V lookup(const bst<K, V> &d, K key)
{
    auto r = search(d.root, key);
    assert(r.actual);
    return (r.actual)->v;
}

template <typename K, typename V>
void insert(bst<K, V> &d, K key, V value)
{
    /* insert into the empty tree. */
    if (!d.root) {
        d.root = new_node(key, value);
        return;
    }

    auto r = search(d.root, key);
    if (r.actual) {
        (r.actual)->v = value;
        return;
    }
    /* If we are here, r.actual == NULL. */
    auto n = new_node(key, value);
    if ((r.parent)->k < key) {
        (r.parent)->right = n;
    } else {
        (r.parent)->left = n;
    }
}

template <typename K, typename V>
bstnode<K, V> *least(bstnode<K, V>* root)
{
    while (root->left) { root = root->left; }
    return root;
}

template <typename K, typename V>
void remove(bst<K, V> &d, K key)
{
    auto r = search(d.root, key);
    auto q = r.actual;
    auto p = r.parent;
    assert(q);
    if (!q->left && !q->right) { // q does not have any child.
        if (p->left == q) {
            p->left = NULL;
        } else if (p->right == q) {
            p->right = NULL;
        }
        return;
    }

    if (!q->left || !q->right) { // q has exactly one child.
        bstnode<K, V> *zs;
        if (q->left) { zs = q->left; }
        else { zs = q->right; }
        if (p->left == q) {
            p->left = zs;
        } else if (p->right == q) {
            p->right = zs;
        }
        return;
    }

    // q has both children.
    auto t = least(q->right);
    auto new_k = t->k;
    auto new_v = t->v;

    remove(d, new_k);

    q->k = new_k;
    q->v = new_v;
}

template <typename K, typename V>
void print0(const bstnode<K, V> *p)
{
    if (!p) return;
    cout << p->k << ": " << p->v << ", ";
    print0(p->left);
    print0(p->right);
}

template <typename K, typename V>
void print(const bst<K, V>& d)
{
    cout << "{";
    print0(d.root);
    cout << "}\n";
}

int main()
{
    auto d = empty<int, int>();
    insert(d, 15, 0);
    insert(d, 10, 0);
    insert(d, 9, 0);
    insert(d, 13, 0);
    insert(d, 30, 0);
    insert(d, 17, 0);
    insert(d, 25, 0);
    insert(d, 16, 0);
    insert(d, 18, 0);
    insert(d, 21, 0);
    print(d);

    remove(d, 17);
    print(d);

    return 0;
}
