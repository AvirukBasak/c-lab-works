/**
 * @author  Aviruk Basak, CSE214047, Sem 3, Year 2
 * @topic   Stack implementation using array in C
 * @date    5-8-2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int StackType;

typedef struct stack {
    int top;
    StackType *arr;
} *stack;

stack new_stack();
bool stack_push(stack st, StackType val);
StackType stack_pop(stack st);
StackType stack_peek(stack st);
bool stack_isempty(stack st);
void stack_free(stack *head);

#define stack_error(e) {                     \
    fprintf(stderr, "stack error: %s\n", e); \
    abort();                                 \
}

#define stack_warn(e, retval) {              \
    fprintf(stderr, "stack warn: %s\n", e);  \
    return retval;                           \
}

// allocate a new stack
stack new_stack()
{
    stack st = calloc(1, sizeof(struct stack));
    if (!st) stack_error("null pointer");
    st->top = -1;
    st->arr = NULL;
    return st;
}

bool stack_push(stack st, StackType val)
{
    if (!st) stack_error("null pointer");
    st->arr = realloc(st->arr, (++(st->top) + 1) * sizeof(StackType));
    if (!st->arr) stack_error("null pointer");
    st->arr[st->top] = val;
    return true;
}

StackType stack_pop(stack st)
{
    if (!st) stack_error("null pointer");
    if (st->top < 0) stack_warn("underflow", 0);
    StackType tmp = st->arr[st->top];
    st->arr = realloc(st->arr, ((st->top)--) * sizeof(StackType));
    return tmp;
}

StackType stack_peek(stack st)
{
    if (!st) stack_error("null pointer");
    if (st->top < 0) stack_warn("underflow", 0);
    return st->arr[st->top];
}

bool stack_isempty(stack st)
{
    return st->top < 0;
}

void stack_free(stack *st)
{
    if (!st || !*st) stack_error("null pointer");
    free((*st)->arr);
    free(*st);
    *st = NULL;
}

int main()
{
    stack st = new_stack();
    int ch = 0;
    do {
        printf("\nchoices:\n"
               "   0: exit\n"
               "   1: push to top\n"
               "   2: peek top\n"
               "   3: pop top\n"
               "   4: is empty?\n"
               "enter your choice: ");
        scanf("%d", &ch);
        printf("\n");
        switch (ch) {
            // exit
            case 0: {
                break;
            }
            // push
            case 1: {
                int val;
                printf("enter val = ");
                scanf("%d", &val);
                stack_push(st, val);
                break;
            }
            // peek
            case 2: {
                printf("value at top = %d\n", stack_peek(st));
                break;
            }
            // pop
            case 3: {
                printf("value on pop = %d\n", stack_pop(st));
                break;
            }
            // is empty
            case 4: {
                if (stack_isempty(st))
                    printf("stack is empty\n");
                else
                    printf("stack is not empty\n");
            }
            default: {
                printf("choice invalid\n");
            }
        }
    } while(ch);
    stack_free(&st);
    return 0;
}

/* OUTPUT:

run: dsa-array-stack.c

choices:
   0: exit
   1: push to top
   2: peek top
   3: pop top
   4: is empty?
enter your choice: 3

stack warn: underflow
value on pop = 0

choices:
   0: exit
   1: push to top
   2: peek top
   3: pop top
   4: is empty?
enter your choice: 3

stack warn: underflow
value on pop = 0

choices:
   0: exit
   1: push to top
   2: peek top
   3: pop top
   4: is empty?
enter your choice: 2

stack warn: underflow
value at top = 0

choices:
   0: exit
   1: push to top
   2: peek top
   3: pop top
   4: is empty?
enter your choice: 1

enter val = 78

choices:
   0: exit
   1: push to top
   2: peek top
   3: pop top
   4: is empty?
enter your choice: 1

enter val = 653

choices:
   0: exit
   1: push to top
   2: peek top
   3: pop top
   4: is empty?
enter your choice: 2

value at top = 653

choices:
   0: exit
   1: push to top
   2: peek top
   3: pop top
   4: is empty?
enter your choice: 3

value on pop = 653

choices:
   0: exit
   1: push to top
   2: peek top
   3: pop top
   4: is empty?
enter your choice: 3

value on pop = 78

choices:
   0: exit
   1: push to top
   2: peek top
   3: pop top
   4: is empty?
enter your choice: 3

stack warn: underflow
value on pop = 0

choices:
   0: exit
   1: push to top
   2: peek top
   3: pop top
   4: is empty?
enter your choice: 0

*/
