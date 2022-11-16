/**
 * @author  Aviruk Basak, CSE214047, Sem 3, Year 2
 * @topic   Binary search tree implementation
 * @date    08-11-2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Type;
typedef struct BST *BST;

#define BST_ISNULLPTR(ptr) if (!ptr) abort();

BST new_bst();
BST bst_newnode(Type val, bool init);
void bst_print_inorder(BST bst);
BST bst_search(BST bst, Type val);
bool bst_insert(BST bst, Type val);
bool bst_delete(BST bst, Type val);

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
            fprintf(stderr, "bst: error: value already exists\n");
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

bool bst_delete(BST bst, Type val)
{
    if (!bst) abort();
    // value found at childless root
    if (bst->val == val && !bst->lc && !bst->rc) {
        bst->isinit = true;
        bst->val = 0;
        return true;
    }
    BST prev = NULL, p = bst;
    while (p)
        if (val == p->val) break;
        else {
            prev = p;
            if (val < p->val) p = p->lc;
            else p = p->rc;
        }
    if (!p) return false;
    // target node has right child
    if (p->rc) {
        BST tmp = p->rc;
        prev = p;
        while (tmp->lc) {
            prev = tmp;
            tmp = tmp->lc;
        }
        p->val = tmp->val;
        if (prev == p) prev->rc = tmp->rc;
        else prev->lc = tmp->rc;
        free(tmp);
    }
    // target node has no right child but has parent
    else if (prev) {
        BST tmp;
        if (prev->lc == p) {
            tmp = prev->lc;
            prev->lc = p->lc;
        } else {
            tmp = prev->rc;
            prev->rc = p->lc;
        }
        free(tmp);
    }
    // target node has no parent, i.e. root
    else {
        BST tmp = p;
        p = p->lc;
        free(tmp);
    }
    return true;
}

int main()
{
    BST bst = new_bst();
    int ch = 0;
    do {
        printf("\nchoices:\n"
               "   0: exit\n"
               "   1: print in-order\n"
               "   2: search element\n"
               "   3: insert new elements\n"
               "   4: delete an element\n"
               "enter your choice: ");
        scanf("%d", &ch);
        printf("\n");
        switch (ch) {
            // exit
            case 0: {
                break;
            }
            // print
            case 1: {
                printf("in-order = { ");
                bst_print_inorder(bst);
                printf("}\n");
                break;
            }
            // search
            case 2: {
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
            case 3: {
                int val;
                printf("enter val = ");
                scanf("%d", &val);
                bst_insert(bst, val);
                break;
            }
            // delete
            case 4: {
                int val;
                printf("enter value to delete: ");
                scanf("%d", &val);
                bst_delete(bst, val);
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



*/
