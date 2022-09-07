/**
 * @author  Aviruk Basak, CSE214047, Sem 3, Year 2
 * @topic   C program to store a sparse matrix as a linked list of 3 tuples
 * @date    7-9-2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TupleNode {
    int row;
    int col;
    int val;
    struct TupleNode *next;
} *TupleNode;

TupleNode new_tuplenode(int row, int col, int val);
TupleNode matrix_toTuple3Sll(int rows, int cols, int matrix[rows][cols]);
bool matrix_isSparse(int rows, int cols, int matrix[rows][cols]);
void matrix_printSll(TupleNode head);
void matrix_freeSll(TupleNode *head);

TupleNode new_tuplenode(int row, int col, int val)
{
    TupleNode node = malloc(sizeof(struct TupleNode));
    if (!node) abort();
    node->row = row;
    node->col = col;
    node->val = val;
    node->next = NULL;
    return node;
}

TupleNode matrix_toTuple3Sll(int rows, int cols, int matrix[rows][cols])
{
    int i, j;
    TupleNode head = new_tuplenode(0,0,0);
    TupleNode p = head;
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            if (matrix[i][j] != 0) {
                p->next = new_tuplenode(i, j, matrix[i][j]);
                p = p->next;
            }
    return head;
}

bool matrix_isSparse(int rows, int cols, int matrix[rows][cols])
{
    int elCount = rows * cols;
    int zeroCount = 0;
    int i, j;
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            if (matrix[i][j] == 0)
                zeroCount++;
    return zeroCount > elCount * 2 / 3;
}

void matrix_printSll(TupleNode head)
{
    if (!head) abort();
    TupleNode p = head->next;
    printf("{\n");
    while (p != NULL) {
        printf("    (%d, %d): %d\n", p->row, p->col, p->val);
        p = p->next;
    }
    printf("}\n");
}

void matrix_freeSll(TupleNode *head)
{
    if (!*head) return;
    TupleNode p = *head;
    while (p != NULL) {
        TupleNode tmp = p->next;
        free(p);
        p = tmp;
    }
    *head = NULL;
}

int main()
{
    int i, j, rows, cols;
    printf("enter row and col size: ");
    scanf("%d", &rows);
    scanf("%d", &cols);
    // C-99 variable array definition syntax: stack allocated arrays
    int matrix[rows][cols];
    printf("\ninput data in matrix:\n");
    for (i = 0; i < rows; i++) {
        printf("row %d: ", i);
        for (j = 0; j < cols; j++)
            scanf("%d", &matrix[i][j]);
    }
    if (!matrix_isSparse(rows, cols, matrix)) {
        printf("\nerror: input isn't a sparse matrix\n");
        return 0;
    }
    TupleNode head = matrix_toTuple3Sll(rows, cols, matrix);
    printf("\nresult = ");
    matrix_printSll(head);
    matrix_freeSll(&head);
    return 0;
}

/* OUTPUT:

enter row and col size: 4 5

input data in matrix:
row 0: -1 0 0 0 2
row 1: 4 0 5 0 0
row 2: 0 0 0 0 1
row 3: 7 0 0 0 0

result = {
    (0, 0): -1
    (0, 4): 2
    (1, 0): 4
    (1, 2): 5
    (2, 4): 1
    (3, 0): 7
}

*/
