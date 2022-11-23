/**
 * @author  Aviruk Basak, CSE214047, Sem 3, Year 2
 * @topic   Binary search tree implementation
 * @date    08-11-2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef int Type;
typedef struct BST *BST;

#define BST_ISNULLPTR(ptr) if (!ptr) abort();

BST new_bst();
BST bst_newnode(Type val, bool init);
void bst_print_inorder(BST bst);
void bst_print_preorder(BST bst);
void bst_print_postorder(BST bst);
BST bst_search(BST bst, Type val);
bool bst_insert(BST bst, Type val);

struct BST {
    BST lc;
    BST rc;
    Type val;
    bool isinit;
};

BST new_bst()
{
    BST node = bst_newnode(0, true);
    return node;
}

BST bst_newnode(Type val, bool init)
{
    BST node = malloc(sizeof(struct BST));
    BST_ISNULLPTR(node);
    node->lc = NULL;
    node->rc = NULL;
    node->val = val;
    node->isinit = init;
    return node;
}

void bst_print_inorder(BST bst)
{
    if (!bst) return;
    if (bst->isinit) return;
    bst_print_inorder(bst->lc);
    printf("%d, ", bst->val);
    bst_print_inorder(bst->rc);
}

void bst_print_preorder(BST bst)
{
    if (!bst) return;
    if (bst->isinit) return;
    printf("%d, ", bst->val);
    bst_print_inorder(bst->lc);
    bst_print_inorder(bst->rc);
}

void bst_print_postorder(BST bst)
{
    if (!bst) return;
    if (bst->isinit) return;
    bst_print_inorder(bst->lc);
    bst_print_inorder(bst->rc);
    printf("%d, ", bst->val);
}

bool bst_insert(BST bst, Type val)
{
    BST_ISNULLPTR(bst);
    if (bst->isinit) {
        bst->val = val;
        bst->isinit = false;
        return true;
    }
    BST node = bst;
    BST trailer = NULL;
    while (node) {
        if (val == node->val) {
            fprintf(stderr, "bst: error: value '%d' already exists\n", val);
            return false;
        }
        else if (val < node->val) {
            trailer = node;
            node = node->lc;
        }
        else {
            trailer = node;
            node = node->rc;
        }
    }
    node = bst_newnode(val, false);
    if (val < trailer->val)
        trailer->lc = node;
    else trailer->rc = node;
    return true;
}

BST bst_search(BST bst, Type val)
{
    BST_ISNULLPTR(bst);
    BST node = bst;
    while (node) {
        if (val == node->val) return node;
        else if (val < node->val) node = node->lc;
        else node = node->rc;
    }
    return NULL;
}

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

int main()
{
    BST bst = new_bst();
    int ch = 0;
    do {
        printf("\nchoices:\n"
               "   0: exit\n"
               "   1: print in-order\n"
               "   2: print pre-order\n"
               "   3: print post-order\n"
               "   4: search element\n"
               "   5: insert new elements\n"
               "enter your choice: ");
        scanf("%d", &ch);
        printf("\n");
        switch (ch) {
            // exit
            case 0: {
                break;
            }
            // in order
            case 1: {
                printf("in-order = { ");
                bst_print_inorder(bst);
                printf("}\n");
                break;
            }
            // pre order
            case 2: {
                printf("pre-order = { ");
                bst_print_preorder(bst);
                printf("}\n");
                break;
            }
            // post order
            case 3: {
                printf("post-order = { ");
                bst_print_postorder(bst);
                printf("}\n");
                break;
            }
            // search
            case 4: {
                int val;
                printf("enter val = ");
                scanf("%d", &val);
                BST node = bst_search(bst, val);
                if (node)
                    printf("bst contains '%d'\n", val);
                else
                    printf("bst does not contain '%d'\n", val);
                break;
            }
            // insert
            case 5: {
                #define IS_TERMINATOR(c) ( !c || c == '\n' || c == (char)EOF )
                printf("enter comma delimited list of elements = ");
                char *s = NULL;
                char c = getchar();
                while (true) {
                    if ((c = getchar()) == ' ');
                    else if (IS_TERMINATOR(c) || c == ',') {
                        s && bst_insert(bst, atoi(s));
                        s && ( free(s), true ) && ( s = NULL );
                        if (IS_TERMINATOR(c)) break;
                    } else if (c == '-' || c == '+' || isdigit(c))
                        s = str_appendchar(s, c);
                    else abort();
                }
                break;
            }
            default: {
                printf("choice invalid\n");
            }
        }
    } while (ch != 0);
    return 0;
}

/* OUTPUT:

choices:
   0: exit
   1: print in-order
   2: print pre-order
   3: print post-order
   4: search element
   5: insert new elements
enter your choice: 5

enter comma delimited list of elements = 12, 34, 19, 67, 45, 22

choices:
   0: exit
   1: print in-order
   2: print pre-order
   3: print post-order
   4: search element
   5: insert new elements
enter your choice: 1

in-order = { 12, 19, 22, 34, 45, 67, }

choices:
   0: exit
   1: print in-order
   2: print pre-order
   3: print post-order
   4: search element
   5: insert new elements
enter your choice: 2

pre-order = { 12, 19, 22, 34, 45, 67, }

choices:
   0: exit
   1: print in-order
   2: print pre-order
   3: print post-order
   4: search element
   5: insert new elements
enter your choice: 3

post-order = { 19, 22, 34, 45, 67, 12, }

choices:
   0: exit
   1: print in-order
   2: print pre-order
   3: print post-order
   4: search element
   5: insert new elements
enter your choice: 0

*/
