/**
 * @author  Aviruk Basak, CSE214047, Sem 3, Year 2
 * @topic   Stack implementation using sll in C
 * @date    12-10-2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int StackType;

typedef struct stack_node {
    StackType val;
    struct stack_node *next;
} *stack_node;

typedef struct stack {
    struct stack_node *top;
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
    st->top = NULL;
    return st;
}

bool stack_push(stack st, StackType val)
{
    if (!st) stack_error("null pointer");
    stack_node node = calloc(1, sizeof(struct stack_node));
    if (!node) stack_error("null pointer");
    node->val = val;
    node->next = NULL;
    if (st->top) node->next = st->top;
    st->top = node;
    return true;
}

StackType stack_pop(stack st)
{
    if (!st) stack_error("null pointer");
    if (!st->top) stack_warn("underflow", 0);
    StackType tmp = st->top->val;
    stack_node delnode = st->top;
    st->top = st->top->next;
    free(delnode);
    return tmp;
}

StackType stack_peek(stack st)
{
    if (!st) stack_error("null pointer");
    if (!st->top) stack_warn("underflow", 0);
    return st->top->val;
}

bool stack_isempty(stack st)
{
    return !st->top;
}

void stack_free(stack *st)
{
    if (!st || !*st) stack_error("null pointer");
    stack_node p = (*st)->top;
    while (p) {
        free(p);
        p = p->next;
    }
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

choices:
   0: exit
   1: push to top
   2: peek top
   3: pop top
   4: is empty?
enter your choice: 1

enter val = 456

choices:
   0: exit
   1: push to top
   2: peek top
   3: pop top
   4: is empty?
enter your choice: 1

enter val = 544

choices:
   0: exit
   1: push to top
   2: peek top
   3: pop top
   4: is empty?
enter your choice: 1

enter val = 876

choices:
   0: exit
   1: push to top
   2: peek top
   3: pop top
   4: is empty?
enter your choice: 2

value at top = 876

choices:
   0: exit
   1: push to top
   2: peek top
   3: pop top
   4: is empty?
enter your choice: 3

value on pop = 876

choices:
   0: exit
   1: push to top
   2: peek top
   3: pop top
   4: is empty?
enter your choice: 3

value on pop = 544

choices:
   0: exit
   1: push to top
   2: peek top
   3: pop top
   4: is empty?
enter your choice: 3

value on pop = 456

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
enter your choice: 1

enter val = 654

choices:
   0: exit
   1: push to top
   2: peek top
   3: pop top
   4: is empty?
enter your choice: 2

value at top = 654

choices:
   0: exit
   1: push to top
   2: peek top
   3: pop top
   4: is empty?
enter your choice: 3

value on pop = 654

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
