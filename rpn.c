/*
 * RPN Calculator.
 */

#include <stdio.h>
#include <assert.h>

#define MAX (256)

typedef struct {
    double elements[MAX];
    int top;
} stack_t;

void empty(stack_t *s)
{
    s->top = 0;
}

int is_empty(stack_t *s)
{
    return (s->top == 0);
}

void push(stack_t *s, double data)
{
    s->elements[s->top] = data;
    ++(s->top);
}

double pop(stack_t *s)
{
    assert(!is_empty(s));
    --(s->top);
    return s->elements[s->top];
}

double top(stack_t *s)
{
    double d = pop(s);
    push(s, d);
    return d;
}

int main()
{
    char buf[128];
    double left, right, data;

    stack_t operands;
    empty(&operands);

    while (1) {
        printf("$ "); scanf("%s", buf);
        switch (buf[0]) {
        case '+':
            right = pop(&operands);
            left = pop(&operands);
            push(&operands, left + right);
            break;
        case '-':
            right = pop(&operands);
            left = pop(&operands);
            push(&operands, left - right);
            break;
        case '*':
            right = pop(&operands);
            left = pop(&operands);
            push(&operands, left * right);
            break;
        case '/':
            right = pop(&operands);
            left = pop(&operands);
            push(&operands, left / right);
            break;
        case '<':
            switch(buf[1]) {
            case '+':
                double sum = 0.0;
                while (!is_empty(&operands)) {
                    sum += pop(&operands);
                }
                push(&operands, sum);
                break;
            case '*':
                double prod = 1.0;
                while (!is_empty(&operands)) {
                    prod *= pop(&operands);
                }
                push(&operands, prod);
                break;
            }
            break;
        case 'p':
            printf("> %.2lf\n", top(&operands));
            break;
        case 'q':
            goto end;
        default:
            sscanf(buf, "%lf", &data);
            push(&operands, data);
        }
    }
end:
    return 0;
}
