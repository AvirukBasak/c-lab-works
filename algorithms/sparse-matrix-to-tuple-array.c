/**
 * @author  Aviruk Basak, CSE214047, Sem 3, Year 2
 * @topic   C program to store a sparse matrix as an array of 3 tuples
 * @date    7-9-2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Tuple {
    int row;
    int col;
    int val;
} Tuple;

typedef struct TupleArray {
    size_t length;
    Tuple *arr;
} *TupleArray;

TupleArray new_tupleArr(size_t size);
TupleArray matrix_toTuple3Arr(int rows, int cols, int matrix[rows][cols], size_t size);
size_t matrix_countNonZero(int rows, int cols, int matrix[rows][cols]);
void matrix_printArr(TupleArray arr);
void matrix_freeArr(TupleArray *arr);

TupleArray new_tupleArr(size_t size)
{
    TupleArray arr = malloc(sizeof(struct TupleArray));
    if (!arr) abort();
    arr->arr = malloc(size * sizeof(struct Tuple));
    if (!arr->arr) abort();
    arr->length = size;
    return arr;
}

TupleArray matrix_toTuple3Arr(int rows, int cols, int matrix[rows][cols], size_t size)
{
    int i, j, k;
    TupleArray arr = new_tupleArr(size);
    for (i = 0, k = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            if (matrix[i][j] != 0) {
                arr->arr[k].row = i;
                arr->arr[k].col = j;
                arr->arr[k].val = matrix[i][j];
                k++;
            }
    return arr;
}

size_t matrix_countNonZero(int rows, int cols, int matrix[rows][cols])
{
    int nonZeroCount = 0;
    int i, j;
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            if (matrix[i][j] != 0)
                nonZeroCount++;
    return nonZeroCount;
}

void matrix_printArr(TupleArray arr)
{
    int i;
    if (!arr) abort();
    printf("{\n");
    for (i = 0; i < arr->length; i++)
        printf("    (%d, %d): %d\n", arr->arr[i].row, arr->arr[i].col, arr->arr[i].val);
    printf("}\n");
}

void matrix_freeArr(TupleArray *arr)
{
    if (!*arr || !(*arr)->arr) return;
    free((*arr)->arr);
    free(*arr);
    *arr = NULL;
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
    size_t size = matrix_countNonZero(rows, cols, matrix);
    if (size > rows * cols * 1 / 3) {
        printf("\nerror: input isn't a sparse matrix\n");
        return 0;
    }
    TupleArray arr = matrix_toTuple3Arr(rows, cols, matrix, size);
    printf("\nresult = ");
    matrix_printArr(arr);
    matrix_freeArr(&arr);
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
