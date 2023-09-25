#ifndef STACK_HPP
#define STACK_HPP

template<typename T>
typedef struct {
    T elements[MAX];
    int top;

    stack() {
        s.top = 0;
    }
} stack;

template<typename T>
bool is_empty(stack<T>& s)
{
    return (s.top == 0);
}

template<typename T>
T pop(stack<T>& s)
{
    --(s.top);
    return s.elements[s.top];
}

template<typename T>
void push(stack& s, T e)
{
    s.elements[s.top++] = e;
}

template<typename T>
T top(stack<T>& s)
{
    T e = pop(s);
    push(s, e);
    return e;
}
#endif
