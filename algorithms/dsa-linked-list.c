#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct sllnode {
    int val;
    struct sllnode *next;
} *sllnode;

typedef struct {
    void *address;
    size_t index;
} TupleX2;

sllnode new_node(int val);
sllnode sll_get(sllnode head, size_t index);
bool sll_traverse(sllnode head, void(*callback)(size_t index, sllnode node));
void sll_print(sllnode head);
TupleX2 sll_search(sllnode head, int val);
bool sll_prepend(sllnode head, int val);
bool sll_append(sllnode head, int val);
bool sll_insert(sllnode head, size_t index, int val);
bool sll_insertAftVal(sllnode head, int searchVal, int val);
bool sll_delIndex(sllnode head, size_t idx);
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

// return a tuple of index and node where target value is located
TupleX2 sll_search(sllnode head, int val)
{
    if (!head) {
        TupleX2 rslt = { NULL, 0 };
        return rslt;
    }
    sllnode p = head->next;
    size_t i = 0;
    while (p != NULL) {
        if (p->val == val) {
            TupleX2 rslt = { p, i };
            return rslt;
        }
        p = p->next;
        i++;
    }
    TupleX2 rslt = { p, i };
    return rslt;
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
    TupleX2 loc = sll_search(head, searchVal);
    if (!loc.address) return false;
    sllnode p = loc.address;
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
        printf("\nchoices:\n"
               "   0: exit\n"
               "   1: access node at index\n"
               "   2: print sllist\n"
               "   3: search for matching value\n"
               "   4: prepend value\n"
               "   5: append value\n"
               "   6: insert a value\n"
               "   7: insert a value after another\n"
               "   8: delete value at index\n"
               "enter your choice: ");
        scanf("%d", &ch);
        printf("\n");
        switch (ch) {
            // exit
            case 0: {
                sll_free(&head);
                exit(0);
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
                TupleX2 loc = sll_search(head, val);
                if (!loc.address)
                    printf("not found\n");
                else
                    printf("value found at index = %zu\n", loc.index);
                break;
            }
            // prepend
            case 4: {
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
            case 5: {
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
            case 6: {
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
            case 7: {
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
            case 8: {
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
            default: {
                printf("choice invalid\n");
            }
        }
    } while(true);
    sll_free(&head);
    return 0;
}
