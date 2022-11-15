/**
 * @author  Aviruk Basak, CSE214047, Sem 3, Year 2
 * @topic   Doubly linked list implementation in C
 * @date    5-8-2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct dllnode {
    int val;
    struct dllnode *prev;
    struct dllnode *next;
} *dllnode;

typedef struct TupleX2 {
    dllnode this;
    size_t index;
} TupleX2;

dllnode new_node(int val);
dllnode dll_get(dllnode head, size_t index);
void dll_print(dllnode head);
TupleX2 dll_search(dllnode head, int val);
TupleX2 dll_getmin(dllnode head);
TupleX2 dll_getmax(dllnode head);
bool dll_prepend(dllnode head, int val);
bool dll_append(dllnode head, int val);
bool dll_insert(dllnode head, size_t index, int val);
bool dll_insertAftVal(dllnode head, int searchVal, int val);
bool dll_delIndex(dllnode head, size_t idx);
bool dll_delValue(dllnode head, int val);
bool dll_delLeft(dllnode head);
bool dll_delRight(dllnode head);
void dll_free(dllnode *head);

// allocate a new node
dllnode new_node(int val)
{
    dllnode node = calloc(1, sizeof(struct dllnode));
    if (!node) return node;
    node->val = val;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

// get node of an index
dllnode dll_get(dllnode head, size_t index)
{
    if (!head) return NULL;
    if (index >= head->val) {
        printf ("dllist: access: index out of bounds\n");
        return NULL;
    }
    size_t i;
    dllnode p = head;
    for (i = 0; i <= index; i++) {
        if (p->next == NULL)
            break;
        p = p->next;
    }
    return p;
}

void dll_print(dllnode head)
{
    if (!head) {
        printf("NULL\n");
        return;
    } else if (!(head->val)) {
        printf("{}\n");
        return;
    }
    dllnode p = head->next;
    printf("{ ");
    while (p != NULL) {
        printf("%d%s", p->val, p->next ? ", " : " ");
        p = p->next;
    }
    printf("}\n");
}

// return a tuple of index and node where target value is located
TupleX2 dll_search(dllnode head, int val)
{
    if (!head || !head->next) {
        TupleX2 rslt = { NULL, 0 };
        return rslt;
    }
    dllnode p = head;
    size_t i = 0;
    while (p->next != NULL) {
        if (p->next->val == val) {
            TupleX2 rslt = { p->next, i };
            return rslt;
        }
        p = p->next;
        i++;
    }
    TupleX2 rslt = { p->next, i };
    return rslt;
}

TupleX2 dll_getmin(dllnode head)
{
    if (!head || !head->next) {
        TupleX2 tuple = { NULL, 0 };
        return tuple;
    }
    dllnode p = head->next;
    dllnode before_min = head;
    size_t i = 0, pos = i;
    while (p->next != NULL) {
        if (p->next->val < before_min->next->val) {
            before_min = p;
            pos = i +1;
        }
        p = p->next;
        i++;
    }
    TupleX2 tuple = { before_min->next, pos };
    return tuple;
}

TupleX2 dll_getmax(dllnode head)
{
    if (!head || !head->next) {
        TupleX2 tuple = { NULL, 0 };
        return tuple;
    }
    dllnode p = head->next;
    dllnode before_max = head;
    size_t i = 0, pos = i;
    while (p->next != NULL) {
        if (p->next->val > before_max->next->val) {
            before_max = p;
            pos = i +1;
        }
        p = p->next;
        i++;
    }
    TupleX2 tuple = { before_max->next, pos };
    return tuple;
}

bool dll_prepend(dllnode head, int val)
{
    return dll_insert(head, 0, val);
}

bool dll_append(dllnode head, int val)
{
    return dll_insert(head, head->val, val);
}

// insert by index, true if successful
bool dll_insert(dllnode head, size_t index, int val)
{
    if (!head) return false;
    if (index > head->val) {
        printf ("dllist: insert: index out of bounds\n");
        return false;
    }
    size_t i;
    dllnode p = head;
    for (i = 0; i < index; i++) {
        if (p->next == NULL)
            break;
        p = p->next;
    }
    dllnode newnode = new_node(val);
    if (!newnode) return false;
    newnode->next = p->next;
    newnode->prev = p;
    if (p->next)
        p->next->prev = newnode;
    p->next = newnode;
    (head->val)++;
    return true;
}

// return true if insertion successful
bool dll_insertAftVal(dllnode head, int searchVal, int val)
{
    if (!head) return false;
    TupleX2 loc = dll_search(head, searchVal);
    if (!loc.this) return false;
    dllnode p = loc.this;
    dllnode newnode = new_node(val);
    if (!newnode) return false;
    newnode->next = p->next;
    newnode->prev = p;
    if (p->next)
        p->next->prev = newnode;
    p->next = newnode;
    (head->val)++;
    return true;
}

bool dll_delIndex(dllnode head, size_t index)
{
    if (!head || head->val <= 0) return false;
    if (index >= head->val) {
        printf("dllist: delIndex: index out of bounds\n");
        return false;
    }
    size_t i;
    dllnode p = head;
    for (i = 0; i < index; i++) {
        if (p->next == NULL)
            break;
        p = p->next;
    }
    dllnode tmp = p->next;
    if (p->next->next)
        p->next->next->prev = p;
    p->next = p->next->next;
    free(tmp);
    (head->val)--;
    return true;
}

bool dll_delValue(dllnode head, int val)
{
    if (!head || head->val <= 0) return false;
    TupleX2 tuple = dll_search(head, val);
    dllnode p = tuple.this->prev;
    dllnode tmp = tuple.this;
    if (!tmp) return false;
    if (p->next->next)
        p->next->next->prev = p;
    p->next = p->next->next;
    free(tmp);
    (head->val)--;
    return true;
}

bool dll_delLeft(dllnode head)
{
    return dll_delIndex(head, 0);
}

bool dll_delRight(dllnode head)
{
    return dll_delIndex(head, head->val -1);
}

void dll_free(dllnode *head)
{
    if (!*head) return;
    dllnode p = *head;
    while (p != NULL) {
        dllnode tmp = p->next;
        free(p);
        p = tmp;
    }
    *head = NULL;
}

int main()
{
    int ch;
    // head->val contains length of linked list
    dllnode head = new_node(0);
    do {
        printf("\nchoices:\n"
               "   0: exit\n"
               "   1: access node at index\n"
               "   2: print dllist\n"
               "   3: search for matching value\n"
               "   4: find minimum element\n"
               "   5: find maximum element\n"
               "   6: prepend value\n"
               "   7: append value\n"
               "   8: insert a value\n"
               "   9: insert a value after another\n"
               "  10: delete at index\n"
               "  11: delete by value\n"
               "  12: delete value from left\n"
               "  13: delete value from right\n"
               "enter your choice: ");
        scanf("%d", &ch);
        printf("\n");
        switch (ch) {
            // exit
            case 0: {
                break;
            }
            // access
            case 1: {
                size_t pos;
                printf("enter posn = ");
                scanf("%zu", &pos);
                dllnode node = dll_get(head, pos);
                if (!node)
                    printf("get failed\n");
                else
                    printf("value at index %zu = %d\n", pos, node->val);
                break;
            }
            // print
            case 2: {
                printf("dll = ");
                dll_print(head);
                printf("length = %d\n", head->val);
                break;
            }
            // search
            case 3: {
                int val;
                printf("enter value = ");
                scanf("%d", &val);
                TupleX2 loc = dll_search(head, val);
                if (!loc.this)
                    printf("not found\n");
                else
                    printf("value found at index = %zu\n", loc.index);
                break;
            }
            // find min
            case 4: {
                TupleX2 loc = dll_getmin(head);
                if (!loc.this)
                    printf("not found\n");
                else
                    printf("min = %d at index = %zu\n", loc.this->val, loc.index);
                break;
            }
            // find max
            case 5: {
                TupleX2 loc = dll_getmax(head);
                if (!loc.this)
                    printf("not found\n");
                else
                    printf("max = %d at index = %zu\n", loc.this->val, loc.index);
                break;
            }
            // prepend
            case 6: {
                int val;
                printf("enter value = ");
                scanf("%d", &val);
                if (!dll_prepend(head, val))
                    printf("prepend failed, no changes made\n");
                else {
                    printf("modified dll = ");
                    dll_print(head);
                }
                break;
            }
            // append
            case 7: {
                int val;
                printf("enter value = ");
                scanf("%d", &val);
                if (!dll_append(head, val))
                    printf("append failed, no changes made\n");
                else {
                    printf("modified dll = ");
                    dll_print(head);
                }
                break;
            }
            // insert
            case 8: {
                int val;
                size_t pos;
                printf("enter value = ");
                scanf("%d", &val);
                printf("enter posn = ");
                scanf("%zu", &pos);
                if (!dll_insert(head, pos, val))
                    printf("insert failed, no changes made\n");
                else {
                    printf("modified dll = ");
                    dll_print(head);
                }
                break;
            }
            // insert after
            case 9: {
                int val, refval;
                printf("enter value = ");
                scanf("%d", &val);
                printf("enter reference value = ");
                scanf("%d", &refval);
                if (!dll_insertAftVal(head, refval, val))
                    printf("insert after value failed, no changes made\n");
                else {
                    printf("modified dll = ");
                    dll_print(head);
                }
                break;
            }
            // delete
            case 10: {
                size_t pos;
                printf("enter posn = ");
                scanf("%zu", &pos);
                if (!dll_delIndex(head, pos))
                    printf("delete failed, no changes made\n");
                else {
                    printf("modified dll = ");
                    dll_print(head);
                }
                break;
            }
            // delete value
            case 11: {
                int val;
                printf("enter value = ");
                scanf("%d", &val);
                if (!dll_delValue(head, val))
                    printf("delete failed, no changes made\n");
                else {
                    printf("modified dll = ");
                    dll_print(head);
                }
                break;
            }
            // del left
            case 12: {
                if (!dll_delLeft(head))
                    printf("delete left failed, no changes made\n");
                else {
                    printf("modified dll = ");
                    dll_print(head);
                }
                break;
            }
            // del right
            case 13: {
                if (!dll_delRight(head))
                    printf("delete right failed, no changes made\n");
                else {
                    printf("modified dll = ");
                    dll_print(head);
                }
                break;
            }
            default: {
                printf("choice invalid\n");
            }
        }
    } while(ch);
    dll_free(&head);
    return 0;
}

/* OUTPUT:

run: dsa-linked-list.c
choices:
   0: exit
   1: access node at index
   2: print dllist
   3: search for matching value
   4: find minimum element
   5: find maximum element
   6: prepend value
   7: append value
   8: insert a value
   9: insert a value after another
  10: delete at index
  11: delete by value
  12: delete value from left
  13: delete value from right
enter your choice: 7

enter value = 1
modified dll = { 1 }

choices:
   0: exit
   1: access node at index
   2: print dllist
   3: search for matching value
   4: find minimum element
   5: find maximum element
   6: prepend value
   7: append value
   8: insert a value
   9: insert a value after another
  10: delete at index
  11: delete by value
  12: delete value from left
  13: delete value from right
enter your choice: 7

enter value = 5
modified dll = { 1, 5 }

choices:
   0: exit
   1: access node at index
   2: print dllist
   3: search for matching value
   4: find minimum element
   5: find maximum element
   6: prepend value
   7: append value
   8: insert a value
   9: insert a value after another
  10: delete at index
  11: delete by value
  12: delete value from left
  13: delete value from right
enter your choice: 7

enter value = -4
modified dll = { 1, 5, -4 }

choices:
   0: exit
   1: access node at index
   2: print dllist
   3: search for matching value
   4: find minimum element
   5: find maximum element
   6: prepend value
   7: append value
   8: insert a value
   9: insert a value after another
  10: delete at index
  11: delete by value
  12: delete value from left
  13: delete value from right
enter your choice: 7

enter value = 3
modified dll = { 1, 5, -4, 3 }

choices:
   0: exit
   1: access node at index
   2: print dllist
   3: search for matching value
   4: find minimum element
   5: find maximum element
   6: prepend value
   7: append value
   8: insert a value
   9: insert a value after another
  10: delete at index
  11: delete by value
  12: delete value from left
  13: delete value from right
enter your choice: 7

enter value = 7
modified dll = { 1, 5, -4, 3, 7 }

choices:
   0: exit
   1: access node at index
   2: print dllist
   3: search for matching value
   4: find minimum element
   5: find maximum element
   6: prepend value
   7: append value
   8: insert a value
   9: insert a value after another
  10: delete at index
  11: delete by value
  12: delete value from left
  13: delete value from right
enter your choice: 7

enter value = 1
modified dll = { 1, 5, -4, 3, 7, 1 }

choices:
   0: exit
   1: access node at index
   2: print dllist
   3: search for matching value
   4: find minimum element
   5: find maximum element
   6: prepend value
   7: append value
   8: insert a value
   9: insert a value after another
  10: delete at index
  11: delete by value
  12: delete value from left
  13: delete value from right
enter your choice: 7

enter value = 8
modified dll = { 1, 5, -4, 3, 7, 1, 8 }

choices:
   0: exit
   1: access node at index
   2: print dllist
   3: search for matching value
   4: find minimum element
   5: find maximum element
   6: prepend value
   7: append value
   8: insert a value
   9: insert a value after another
  10: delete at index
  11: delete by value
  12: delete value from left
  13: delete value from right
enter your choice: 2

dll = { 1, 5, -4, 3, 7, 1, 8 }
length = 7

choices:
   0: exit
   1: access node at index
   2: print dllist
   3: search for matching value
   4: find minimum element
   5: find maximum element
   6: prepend value
   7: append value
   8: insert a value
   9: insert a value after another
  10: delete at index
  11: delete by value
  12: delete value from left
  13: delete value from right
enter your choice: 4

min = -4 at index = 2

choices:
   0: exit
   1: access node at index
   2: print dllist
   3: search for matching value
   4: find minimum element
   5: find maximum element
   6: prepend value
   7: append value
   8: insert a value
   9: insert a value after another
  10: delete at index
  11: delete by value
  12: delete value from left
  13: delete value from right
enter your choice: 5

max = 8 at index = 6

choices:
   0: exit
   1: access node at index
   2: print dllist
   3: search for matching value
   4: find minimum element
   5: find maximum element
   6: prepend value
   7: append value
   8: insert a value
   9: insert a value after another
  10: delete at index
  11: delete by value
  12: delete value from left
  13: delete value from right
enter your choice: 11

enter value = -4
modified dll = { 1, 5, 3, 7, 1, 8 }

choices:
   0: exit
   1: access node at index
   2: print dllist
   3: search for matching value
   4: find minimum element
   5: find maximum element
   6: prepend value
   7: append value
   8: insert a value
   9: insert a value after another
  10: delete at index
  11: delete by value
  12: delete value from left
  13: delete value from right
enter your choice: 9

enter value = 78
enter reference value = 7
modified dll = { 1, 5, 3, 7, 78, 1, 8 }

choices:
   0: exit
   1: access node at index
   2: print dllist
   3: search for matching value
   4: find minimum element
   5: find maximum element
   6: prepend value
   7: append value
   8: insert a value
   9: insert a value after another
  10: delete at index
  11: delete by value
  12: delete value from left
  13: delete value from right
enter your choice: 0

*/
