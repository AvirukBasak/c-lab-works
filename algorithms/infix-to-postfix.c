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
#define EOF ((char) -1)
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
char *str_appendchar(char *s, char c)
{
    if (!s) {
        s = malloc(2 * sizeof(char));
        if (!s) abort();
        s[0] = c;
        s[1] = 0;
        return s;
    }
    int size = strlen(s) + 1;
    s = realloc(s, (size+1) * sizeof(char));
    if (!s) abort();
    s[size-1] = c;
    s[size] = 0;
    return s;
}

/** Remember to free the returned pointer */
char *toPostFix(const char *s)
{
    stack symst = new_stack();
    int len = strlen(s);
    char *result = NULL;
    for (int i = 0; i < len; i++) {
        char c = s[i];
        // symbol = operand goes to output
        if (isalpha(c) || isdigit(c))
            result = str_appendchar(result, c);
        // symbol = '(' gets pushed
        else if (c == '(')
            stack_push(symst, '(');
        // symbol = ')' pop and output until symbol = '('
        else if (c == ')') {
            while (stack_peek(symst) != '(') {
                result = str_appendchar(result, stack_peek(symst));
                stack_pop(symst);
            }
            stack_pop(symst);
        }
        // symbol = operator
        else {
            while (!stack_isempty(symst)
                   && priority(INCOMING, s[i]) <= priority(IN_STACK, stack_peek(symst))) {
                result = str_appendchar(result, stack_peek(symst));
                stack_pop(symst);
            }
            stack_push(symst, c);
        }
    }
    // pop remaining symbols to output
    while (!stack_isempty(symst)) {
        result = str_appendchar(result, stack_peek(symst));
        stack_pop(symst);
    }
    stack_free(&symst);
    return result;
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

/* OUTPUT:

enter infix exp, leave empty to exit: ((A+B)^C-(D*E)/F)
postfix: AB+C^DE*F/-

*/
