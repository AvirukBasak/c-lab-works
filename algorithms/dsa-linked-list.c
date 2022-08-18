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
sllnode access(sllnode head, size_t index);
void printsll(sllnode head);
bool insertAftVal(sllnode head, int searchVal, int val);
TupleX2 search(sllnode head, int val);
bool insert(sllnode head, size_t index, int val);
bool insertAftVal(sllnode head, int searchVal, int val);
bool delIndex(sllnode head, size_t idx);
void sllfree(sllnode *head);

// allocate a new node
sllnode new_node(int val)
{
    sllnode node = calloc(1, sizeof(struct sllnode));
    if (!node) return node;
    node->val = val;
    node->next = NULL;
    return node;
}

sllnode access(sllnode head, size_t index)
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

void printsll(sllnode head)
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

// return the node where target value is located
TupleX2 search(sllnode head, int val)
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

// insert by index, true if successful
bool insert(sllnode head, size_t index, int val)
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
bool insertAftVal(sllnode head, int searchVal, int val)
{
    if (!head) return false;
    TupleX2 loc = search(head, searchVal);
    if (!loc.address) return false;
    sllnode p = loc.address;
    sllnode newnode = new_node(val);
    if (!newnode) return false;
    newnode->next = p->next;
    p->next = newnode;
    (head->val)++;
    return true;
}

bool delIndex(sllnode head, size_t index)
{
    if (!head) return false;
    if (index >= head->val || !(head->next)) {
        printf ("sllist: delIndex: index out of bounds\n");
        return false;
    }
    size_t i;
    sllnode p = head->next;
    for (i = 0; i < index; i++) {
        if (p->next == NULL)
            break;
        p = p->next;
    }
    if (index == 0 && head->next) {
        sllnode tmp = head->next;
        head->next = head->next->next;
        free(tmp);
    } else {
        sllnode tmp = p->next;
        p->next = p->next ? p->next->next : p->next;
        free(tmp);
    }
    (head->val)--;
    return true;
}

void sllfree(sllnode *head)
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
               "   4: insert a value\n"
               "   5: insert a value after another\n"
               "   6: append value\n"
               "   7: prepend value\n"
               "   8: delete value at index\n"
               "enter your choice: ");
        scanf("%d", &ch);
        printf("\n");
        switch (ch) {
            // exit
            case 0: {
                sllfree(&head);
                exit(0);
            }
            // access
            case 1: {
                size_t pos;
                printf("enter posn = ");
                scanf("%zu", &pos);
                sllnode node = access(head, pos);
                printf("value at index %zu = %d\n", pos, node->val);
                break;
            }
            // print
            case 2: {
                printf("sll = ");
                printsll(head);
                printf("length = %d\n", head->val);
                break;
            }
            // search
            case 3: {
                int val;
                printf("enter value = ");
                scanf("%d", &val);
                TupleX2 loc = search(head, val);
                if (!loc.address)
                    printf("not found\n");
                else
                    printf("value found at index = %zu\n", loc.index);
                break;
            }
            // insert
            case 4: {
                int val;
                size_t pos;
                printf("enter value = ");
                scanf("%d", &val);
                printf("enter posn = ");
                scanf("%zu", &pos);
                if (!insert(head, pos, val))
                    printf("insert failed, no changes made\n");
                else {
                    printf("modified sll = ");
                    printsll(head);
                }
                break;
            }
            // insert after
            case 5: {
                int val, refval;
                printf("enter value = ");
                scanf("%d", &refval);
                printf("enter reference value = ");
                scanf("%d", &val);
                if (!insertAftVal(head, refval, val))
                    printf("insert after value failed, no changes made\n");
                else {
                    printf("modified sll = ");
                    printsll(head);
                }
                break;
            }
            // append
            case 6: {
                int val;
                size_t pos = head->val;
                printf("enter value = ");
                scanf("%d", &val);
                if (!insert(head, pos, val))
                    printf("append failed, no changes made\n");
                else {
                    printf("modified sll = ");
                    printsll(head);
                }
                break;
            }
            // prepend
            case 7: {
                int val;
                size_t pos = 0;
                printf("enter value = ");
                scanf("%d", &val);
                if (!insert(head, pos, val))
                    printf("prepend failed, no changes made\n");
                else {
                    printf("modified sll = ");
                    printsll(head);
                }
                break;
            }
            // delete
            case 8: {
                size_t pos;
                printf("enter posn = ");
                scanf("%zu", &pos);
                if (!delIndex(head, pos))
                    printf("delete failed, no changes made\n");
                else {
                    printf("modified sll = ");
                    printsll(head);
                }
                break;
            }
            default: {
                printf("choice invalid\n");
            }
        }
    } while(true);
    sllfree(&head);
    return 0;
}
