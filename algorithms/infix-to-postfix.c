/**
 * @author  Aviruk Basak, CSE214047, Sem 3, Year 2
 * @topic   Infix to postfix converter in C
 * @date    2-11-2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#undef EOF
#define EOF (255)
typedef char StackType;

/* ------------ START STACK IMPLEMENTATION -------------- */

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

/* -------------- END STACK IMPLEMENTATION -------------- */

typedef enum {
    IN_STACK,
    INCOMING
} Loc;

int priority(Loc location, char sym);
char *inputStr(const char *prompt);
char *toPostFix(const char *infix);

/** priority table equivalent */
int priority(Loc location, char sym)
{
    if (sym == '+' || sym == '-')
        if (location == IN_STACK) return 2;
        else return 1;
    else if (sym == '*' || sym == '/')
        if (location == IN_STACK) return 4;
        else return 3;
    else if (sym == '^')
        if (location == IN_STACK) return 5;
        else return 6;
    else if (sym == '(')
        if (location == IN_STACK) return 0;
        else return 9;
    else if (sym == ')')
        if (location == IN_STACK) return -1;
        else return 0;
    else
        if (location == IN_STACK) return 8;
        else return 7;
}

/** Remember to free the returned pointer */
char *toPostFix(const char *infix)
{
    stack symst = new_stack();
    stack_push(symst, infix[0]);
    int i = 1, j = 0;
    char *postfix = malloc((j+1) * sizeof(char));
    while (!stack_isempty(symst)) {
        char sym = infix[i];
        char t = stack_pop(symst);
        if (isalpha(sym) || (sym >= '0' && sym <= '9')) {
            postfix[j++] = sym;
            postfix = realloc(postfix, (j+1) * sizeof(char));
            stack_push(symst, t);
        } else if (sym == ')') {
            while (t != '(') {
                postfix[j++] = sym;
                postfix = realloc(postfix, (j+1) * sizeof(char));
                t = stack_pop(symst);
            }
            if (t == '(') stack_pop(symst);
        } else if (sym == '(') {
            stack_push(symst, '(');
        } else if (priority(INCOMING, sym) > priority(IN_STACK, t)) {
            stack_push(symst, t);
            stack_push(symst, sym);
        } else {
            stack_push(symst, t);
            while (priority(IN_STACK, stack_peek(symst)) <= priority(INCOMING, sym)) {
                postfix[j++] = stack_pop(symst);
                postfix = realloc(postfix, (j+1) * sizeof(char));
            }
            stack_push(symst, sym);
        }
        i++;
    }
    postfix[j] = 0;
    stack_free(&symst);
    return postfix;
}

/** Remember to free the returned pointer */
char *inputStr(const char *prompt)
{
    printf("%s", prompt);
    int i = 0;
    char c = getchar();
    char *in = malloc(1 * sizeof(char));
    while (c != EOF && c != 0 && c != '\n') {
        in[i++] = c;
        in = realloc(in, (i+1) * sizeof(char));
        c = getchar();
    }
    in[i] = 0;
    return in;
}

int main()
{
    do {
        char *infix = inputStr("enter infix exp, leave empty to exit: ");
        if (strlen(infix) == 0) exit(0);
        char *postfix = toPostFix(infix);
        free(infix);
        printf("postfix: %s\n", postfix); 
        free(postfix);
    } while (true);
    return 0;
}
