/**
 * @author  Aviruk Basak, CSE214047, Sem 3, Year 2
 * @topic   Circular linked list implementation in C
 * @date    7-9-2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct csllnode {
    int val;
    struct csllnode *next;
} *csllnode;

typedef struct TupleX3 {
    csllnode prev;
    csllnode this;
    size_t index;
} TupleX3;

csllnode new_node(int val);
csllnode csll_get(csllnode head, size_t index);
bool csll_traverse(csllnode head, void(*callback)(size_t index, csllnode node));
void csll_print(csllnode head);
TupleX3 csll_search(csllnode head, int val);
TupleX3 csll_getmin(csllnode head);
TupleX3 csll_getmax(csllnode head);
bool csll_prepend(csllnode head, int val);
bool csll_append(csllnode head, int val);
bool csll_insert(csllnode head, size_t index, int val);
bool csll_insertAftVal(csllnode head, int searchVal, int val);
bool csll_delIndex(csllnode head, size_t idx);
bool csll_delValue(csllnode head, int val);
bool csll_delLeft(csllnode head);
bool csll_delRight(csllnode head);
void csll_free(csllnode *head);

// allocate a new node
csllnode new_node(int val)
{
    csllnode node = calloc(1, sizeof(struct csllnode));
    if (!node) return node;
    node->val = val;
    node->next = NULL;
    return node;
}

// get node of an index
csllnode csll_get(csllnode head, size_t index)
{
    if (!head) return NULL;
    if (index >= head->val) {
        printf ("csllist: access: index out of bounds\n");
        return NULL;
    }
    size_t i;
    csllnode p = head;
    for (i = 0; i <= index; i++) {
        if (p->next == head)
            break;
        p = p->next;
    }
    return p;
}

// traverse csll by using a callback method
bool csll_traverse(csllnode head, void(*callback)(size_t index, csllnode node))
{
    if (!head) return false;
    size_t i = 0;
    csllnode p = head->next;
    while (p != head) {
        callback(i, p);
        p = p->next;
        i++;
    }
    return true;
}

void csll_print(csllnode head)
{
    if (!head) {
        printf("NULL\n");
        return;
    } else if (!(head->val)) {
        printf("{}\n");
        return;
    }
    csllnode p = head->next;
    printf("{ ");
    while (p != head) {
        printf("%d%s", p->val, p->next != head ? ", " : " ");
        p = p->next;
    }
    printf("}\n");
}

// return a tuple of index and node where target value is located
TupleX3 csll_search(csllnode head, int val)
{
    if (!head || !head->next) {
        TupleX3 rslt = { NULL, NULL, 0 };
        return rslt;
    }
    csllnode p = head;
    size_t i = 0;
    while (p->next != head) {
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

TupleX3 csll_getmin(csllnode head)
{
    if (!head || !head->next) {
        TupleX3 tuple = { NULL, NULL, 0 };
        return tuple;
    }
    csllnode p = head->next;
    csllnode before_min = head;
    size_t i = 0, pos = i;
    while (p->next != head) {
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

TupleX3 csll_getmax(csllnode head)
{
    if (!head || !head->next) {
        TupleX3 tuple = { NULL, NULL, 0 };
        return tuple;
    }
    csllnode p = head->next;
    csllnode before_max = head;
    size_t i = 0, pos = i;
    while (p->next != head) {
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

bool csll_prepend(csllnode head, int val)
{
    return csll_insert(head, 0, val);
}

bool csll_append(csllnode head, int val)
{
    return csll_insert(head, head->val, val);
}

// insert by index, true if successful
bool csll_insert(csllnode head, size_t index, int val)
{
    if (!head) return false;
    if (index > head->val) {
        printf ("csllist: insert: index out of bounds\n");
        return false;
    }
    size_t i;
    csllnode p = head;
    for (i = 0; i < index; i++) {
        if (p->next == head)
            break;
        p = p->next;
    }
    csllnode newnode = new_node(val);
    if (!newnode) return false;
    newnode->next = p->next;
    p->next = newnode;
    (head->val)++;
    return true;
}

// return true if insertion successful
bool csll_insertAftVal(csllnode head, int searchVal, int val)
{
    if (!head) return false;
    TupleX3 loc = csll_search(head, searchVal);
    if (!loc.this) return false;
    csllnode p = loc.this;
    csllnode newnode = new_node(val);
    if (!newnode) return false;
    newnode->next = p->next;
    p->next = newnode;
    (head->val)++;
    return true;
}

bool csll_delIndex(csllnode head, size_t index)
{
    if (!head || head->val <= 0) return false;
    if (index >= head->val) {
        printf("csllist: delIndex: index out of bounds\n");
        return false;
    }
    size_t i;
    csllnode p = head;
    for (i = 0; i < index; i++) {
        if (p->next == head)
            break;
        p = p->next;
    }
    csllnode tmp = p->next;
    p->next = p->next->next;
    free(tmp);
    (head->val)--;
    return true;
}

bool csll_delValue(csllnode head, int val)
{
    if (!head || head->val <= 0) return false;
    TupleX3 tuple = csll_search(head, val);
    csllnode p = tuple.prev;
    csllnode tmp = tuple.this;
    if (!tmp) return false;
    p->next = p->next->next;
    free(tmp);
    (head->val)--;
    return true;
}

bool csll_delLeft(csllnode head)
{
    return csll_delIndex(head, 0);
}

bool csll_delRight(csllnode head)
{
    return csll_delIndex(head, head->val -1);
}

void csll_free(csllnode *head)
{
    if (!*head) return;
    csllnode p = *head;
    while (p != *head) {
        csllnode tmp = p->next;
        free(p);
        p = tmp;
    }
    *head = NULL;
}

int main()
{
    int ch;
    // head->val contains length of linked list
    csllnode head = new_node(0);
    // creating circular reference
    head->next = head;
    do {
        printf("\nchoices:\n"
               "   0: exit\n"
               "   1: access node at index\n"
               "   2: print csllist\n"
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
                csllnode node = csll_get(head, pos);
                if (!node)
                    printf("get failed\n");
                else
                    printf("value at index %zu = %d\n", pos, node->val);
                break;
            }
            // print
            case 2: {
                printf("csll = ");
                csll_print(head);
                printf("length = %d\n", head->val);
                break;
            }
            // search
            case 3: {
                int val;
                printf("enter value = ");
                scanf("%d", &val);
                TupleX3 loc = csll_search(head, val);
                if (!loc.this)
                    printf("not found\n");
                else
                    printf("value found at index = %zu\n", loc.index);
                break;
            }
            // find min
            case 4: {
                TupleX3 loc = csll_getmin(head);
                if (!loc.this)
                    printf("not found\n");
                else
                    printf("min = %d at index = %zu\n", loc.this->val, loc.index);
                break;
            }
            // find max
            case 5: {
                TupleX3 loc = csll_getmax(head);
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
                if (!csll_prepend(head, val))
                    printf("prepend failed, no changes made\n");
                else {
                    printf("modified csll = ");
                    csll_print(head);
                }
                break;
            }
            // append
            case 7: {
                int val;
                printf("enter value = ");
                scanf("%d", &val);
                if (!csll_append(head, val))
                    printf("append failed, no changes made\n");
                else {
                    printf("modified csll = ");
                    csll_print(head);
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
                if (!csll_insert(head, pos, val))
                    printf("insert failed, no changes made\n");
                else {
                    printf("modified csll = ");
                    csll_print(head);
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
                if (!csll_insertAftVal(head, refval, val))
                    printf("insert after value failed, no changes made\n");
                else {
                    printf("modified csll = ");
                    csll_print(head);
                }
                break;
            }
            // delete
            case 10: {
                size_t pos;
                printf("enter posn = ");
                scanf("%zu", &pos);
                if (!csll_delIndex(head, pos))
                    printf("delete failed, no changes made\n");
                else {
                    printf("modified csll = ");
                    csll_print(head);
                }
                break;
            }
            // delete value
            case 11: {
                int val;
                printf("enter value = ");
                scanf("%d", &val);
                if (!csll_delValue(head, val))
                    printf("delete failed, no changes made\n");
                else {
                    printf("modified csll = ");
                    csll_print(head);
                }
                break;
            }
            // del left
            case 12: {
                if (!csll_delLeft(head))
                    printf("delete left failed, no changes made\n");
                else {
                    printf("modified csll = ");
                    csll_print(head);
                }
                break;
            }
            // del right
            case 13: {
                if (!csll_delRight(head))
                    printf("delete right failed, no changes made\n");
                else {
                    printf("modified csll = ");
                    csll_print(head);
                }
                break;
            }
            default: {
                printf("choice invalid\n");
            }
        }
    } while(ch);
    csll_free(&head);
    return 0;
}

/* OUTPUT:

choices:
   0: exit
   1: access node at index
   2: print csllist
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

csll = {}
length = 0

choices:
   0: exit
   1: access node at index
   2: print csllist
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

enter value = 23
modified csll = { 23 }

choices:
   0: exit
   1: access node at index
   2: print csllist
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

enter value = 87
modified csll = { 23, 87 }

choices:
   0: exit
   1: access node at index
   2: print csllist
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

enter value = 23
modified csll = { 23, 87, 23 }

choices:
   0: exit
   1: access node at index
   2: print csllist
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

enter value = 986
modified csll = { 23, 87, 23, 986 }

choices:
   0: exit
   1: access node at index
   2: print csllist
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

enter value = 12312
modified csll = { 23, 87, 23, 986, 12312 }

choices:
   0: exit
   1: access node at index
   2: print csllist
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

enter value = 43
modified csll = { 23, 87, 23, 986, 12312, 43 }

choices:
   0: exit
   1: access node at index
   2: print csllist
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

enter value = 889
modified csll = { 23, 87, 23, 986, 12312, 43, 889 }

choices:
   0: exit
   1: access node at index
   2: print csllist
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

csll = { 23, 87, 23, 986, 12312, 43, 889 }
length = 7

choices:
   0: exit
   1: access node at index
   2: print csllist
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

min = 23 at index = 0

choices:
   0: exit
   1: access node at index
   2: print csllist
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

max = 12312 at index = 4

choices:
   0: exit
   1: access node at index
   2: print csllist
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
enter your choice: 12

modified csll = { 87, 23, 986, 12312, 43, 889 }

choices:
   0: exit
   1: access node at index
   2: print csllist
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
enter your choice: 10

enter posn = 2
modified csll = { 87, 23, 12312, 43, 889 }

choices:
   0: exit
   1: access node at index
   2: print csllist
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
