/**
 * @author  Aviruk Basak, CSE214047, Sem 3, Year 2
 * @topic   Singly linked list implementation in C
 * @date    5-8-2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct sllnode {
    int val;
    struct sllnode *next;
} *sllnode;

typedef struct TupleX3 {
    sllnode prev;
    sllnode this;
    size_t index;
} TupleX3;

sllnode new_node(int val);
sllnode sll_get(sllnode head, size_t index);
bool sll_traverse(sllnode head, void(*callback)(size_t index, sllnode node));
void sll_print(sllnode head);
TupleX3 sll_search(sllnode head, int val);
TupleX3 sll_getmin(sllnode head);
TupleX3 sll_getmax(sllnode head);
bool sll_prepend(sllnode head, int val);
bool sll_append(sllnode head, int val);
bool sll_insert(sllnode head, size_t index, int val);
bool sll_insertAftVal(sllnode head, int searchVal, int val);
bool sll_delIndex(sllnode head, size_t idx);
bool sll_delValue(sllnode head, int val);
bool sll_delLeft(sllnode head);
bool sll_delRight(sllnode head);
void sll_free(sllnode *head);

// allocate a new node
sllnode new_node(int val)
{
    sllnode node = calloc(1, sizeof(struct sllnode));
    if (!node) return node;
    node->val = val;
    node->next = NULL;
    return node;
}

// get node of an index
sllnode sll_get(sllnode head, size_t index)
{
    if (!head) return NULL;
    if (index >= head->val) {
        printf ("sllist: access: index out of bounds\n");
        return NULL;
    }
    size_t i;
    sllnode p = head;
    for (i = 0; i <= index; i++) {
        if (p->next == NULL)
            break;
        p = p->next;
    }
    return p;
}

// traverse sll by using a callback method
bool sll_traverse(sllnode head, void(*callback)(size_t index, sllnode node))
{
    if (!head) return false;
    size_t i = 0;
    sllnode p = head->next;
    while (p != NULL) {
        callback(i, p);
        p = p->next;
        i++;
    }
    return true;
}

void sll_print(sllnode head)
{
    if (!head) {
        printf("NULL\n");
        return;
    } else if (!(head->val)) {
        printf("{}\n");
        return;
    }
    sllnode p = head->next;
    printf("{ ");
    while (p != NULL) {
        printf("%d%s", p->val, p->next ? ", " : " ");
        p = p->next;
    }
    printf("}\n");
}

bool sll_reverse(sllnode head)
{
    if (!head || !head->next) return false;
    size_t i;
    for (i = 0; i < head->val / 2; i++) {
        int tmp = sll_get(head, i)->val;
        sll_get(head, i)->val = sll_get(head, head->val -i -1)->val;
        sll_get(head, head->val -i -1)->val = tmp;
    }
    return true;
}

// return a tuple of index and node where target value is located
TupleX3 sll_search(sllnode head, int val)
{
    if (!head || !head->next) {
        TupleX3 rslt = { NULL, NULL, 0 };
        return rslt;
    }
    sllnode p = head;
    size_t i = 0;
    while (p->next != NULL) {
        if (p->next->val == val) {
            TupleX3 rslt = { p, p->next, i };
            return rslt;
        }
        p = p->next;
        i++;
    }
    TupleX3 rslt = { p, p->next, i };
    return rslt;
}

TupleX3 sll_getmin(sllnode head)
{
    if (!head || !head->next) {
        TupleX3 tuple = { NULL, NULL, 0 };
        return tuple;
    }
    sllnode p = head->next;
    sllnode before_min = head;
    size_t i = 0, pos = i;
    while (p->next != NULL) {
        if (p->next->val < before_min->next->val) {
            before_min = p;
            pos = i +1;
        }
        p = p->next;
        i++;
    }
    TupleX3 tuple = { before_min, before_min->next, pos };
    return tuple;
}

TupleX3 sll_getmax(sllnode head)
{
    if (!head || !head->next) {
        TupleX3 tuple = { NULL, NULL, 0 };
        return tuple;
    }
    sllnode p = head->next;
    sllnode before_max = head;
    size_t i = 0, pos = i;
    while (p->next != NULL) {
        if (p->next->val > before_max->next->val) {
            before_max = p;
            pos = i +1;
        }
        p = p->next;
        i++;
    }
    TupleX3 tuple = { before_max, before_max->next, pos };
    return tuple;
}

bool sll_prepend(sllnode head, int val)
{
    return sll_insert(head, 0, val);
}

bool sll_append(sllnode head, int val)
{
    return sll_insert(head, head->val, val);
}

// insert by index, true if successful
bool sll_insert(sllnode head, size_t index, int val)
{
    if (!head) return false;
    if (index > head->val) {
        printf ("sllist: insert: index out of bounds\n");
        return false;
    }
    size_t i;
    sllnode p = head;
    for (i = 0; i < index; i++) {
        if (p->next == NULL)
            break;
        p = p->next;
    }
    sllnode newnode = new_node(val);
    if (!newnode) return false;
    newnode->next = p->next;
    p->next = newnode;
    (head->val)++;
    return true;
}

// return true if insertion successful
bool sll_insertAftVal(sllnode head, int searchVal, int val)
{
    if (!head) return false;
    TupleX3 loc = sll_search(head, searchVal);
    if (!loc.this) return false;
    sllnode p = loc.this;
    sllnode newnode = new_node(val);
    if (!newnode) return false;
    newnode->next = p->next;
    p->next = newnode;
    (head->val)++;
    return true;
}

bool sll_delIndex(sllnode head, size_t index)
{
    if (!head || head->val <= 0) return false;
    if (index >= head->val) {
        printf("sllist: delIndex: index out of bounds\n");
        return false;
    }
    size_t i;
    sllnode p = head;
    for (i = 0; i < index; i++) {
        if (p->next == NULL)
            break;
        p = p->next;
    }
    sllnode tmp = p->next;
    p->next = p->next->next;
    free(tmp);
    (head->val)--;
    return true;
}

bool sll_delValue(sllnode head, int val)
{
    if (!head || head->val <= 0) return false;
    TupleX3 tuple = sll_search(head, val);
    sllnode p = tuple.prev;
    sllnode tmp = tuple.this;
    if (!tmp) return false;
    p->next = p->next->next;
    free(tmp);
    (head->val)--;
    return true;
}

bool sll_delLeft(sllnode head)
{
    return sll_delIndex(head, 0);
}

bool sll_delRight(sllnode head)
{
    return sll_delIndex(head, head->val -1);
}

void sll_free(sllnode *head)
{
    if (!*head) return;
    sllnode p = *head;
    while (p != NULL) {
        sllnode tmp = p->next;
        free(p);
        p = tmp;
    }
    *head = NULL;
}

int main()
{
    int ch;
    // head->val contains length of linked list
    sllnode head = new_node(0);
    do {
        printf("choices:\n"
               "   0: exit\n"
               "   1: access node at index\n"
               "   2: print sllist\n"
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
                sllnode node = sll_get(head, pos);
                if (!node)
                    printf("get failed\n");
                else
                    printf("value at index %zu = %d\n", pos, node->val);
                break;
            }
            // print
            case 2: {
                printf("sll = ");
                sll_print(head);
                printf("length = %d\n", head->val);
                break;
            }
            // search
            case 3: {
                int val;
                printf("enter value = ");
                scanf("%d", &val);
                TupleX3 loc = sll_search(head, val);
                if (!loc.this)
                    printf("not found\n");
                else
                    printf("value found at index = %zu\n", loc.index);
                break;
            }
            // find min
            case 4: {
                TupleX3 loc = sll_getmin(head);
                if (!loc.this)
                    printf("not found\n");
                else
                    printf("min = %d at index = %zu\n", loc.this->val, loc.index);
                break;
            }
            // find max
            case 5: {
                TupleX3 loc = sll_getmax(head);
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
                if (!sll_prepend(head, val))
                    printf("prepend failed, no changes made\n");
                else {
                    printf("modified sll = ");
                    sll_print(head);
                }
                break;
            }
            // append
            case 7: {
                int val;
                printf("enter value = ");
                scanf("%d", &val);
                if (!sll_append(head, val))
                    printf("append failed, no changes made\n");
                else {
                    printf("modified sll = ");
                    sll_print(head);
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
                if (!sll_insert(head, pos, val))
                    printf("insert failed, no changes made\n");
                else {
                    printf("modified sll = ");
                    sll_print(head);
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
                if (!sll_insertAftVal(head, refval, val))
                    printf("insert after value failed, no changes made\n");
                else {
                    printf("modified sll = ");
                    sll_print(head);
                }
                break;
            }
            // delete
            case 10: {
                size_t pos;
                printf("enter posn = ");
                scanf("%zu", &pos);
                if (!sll_delIndex(head, pos))
                    printf("delete failed, no changes made\n");
                else {
                    printf("modified sll = ");
                    sll_print(head);
                }
                break;
            }
            // delete value
            case 11: {
                int val;
                printf("enter value = ");
                scanf("%d", &val);
                if (!sll_delValue(head, val))
                    printf("delete failed, no changes made\n");
                else {
                    printf("modified sll = ");
                    sll_print(head);
                }
                break;
            }
            // del left
            case 12: {
                if (!sll_delLeft(head))
                    printf("delete left failed, no changes made\n");
                else {
                    printf("modified sll = ");
                    sll_print(head);
                }
                break;
            }
            // del right
            case 13: {
                if (!sll_delRight(head))
                    printf("delete right failed, no changes made\n");
                else {
                    printf("modified sll = ");
                    sll_print(head);
                }
                break;
            }
            default: {
                printf("choice invalid\n");
            }
        }
    } while(ch);
    sll_free(&head);
    return 0;
}

/* OUTPUT:

run: dsa-linked-list.c
choices:
   0: exit
   1: access node at index
   2: print sllist
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
modified sll = { 1 }

choices:
   0: exit
   1: access node at index
   2: print sllist
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
modified sll = { 1, 5 }

choices:
   0: exit
   1: access node at index
   2: print sllist
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
modified sll = { 1, 5, -4 }

choices:
   0: exit
   1: access node at index
   2: print sllist
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
modified sll = { 1, 5, -4, 3 }

choices:
   0: exit
   1: access node at index
   2: print sllist
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
modified sll = { 1, 5, -4, 3, 7 }

choices:
   0: exit
   1: access node at index
   2: print sllist
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
modified sll = { 1, 5, -4, 3, 7, 1 }

choices:
   0: exit
   1: access node at index
   2: print sllist
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
modified sll = { 1, 5, -4, 3, 7, 1, 8 }

choices:
   0: exit
   1: access node at index
   2: print sllist
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

sll = { 1, 5, -4, 3, 7, 1, 8 }
length = 7

choices:
   0: exit
   1: access node at index
   2: print sllist
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
   2: print sllist
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
   2: print sllist
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
modified sll = { 1, 5, 3, 7, 1, 8 }

choices:
   0: exit
   1: access node at index
   2: print sllist
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
modified sll = { 1, 5, 3, 7, 78, 1, 8 }

choices:
   0: exit
   1: access node at index
   2: print sllist
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
