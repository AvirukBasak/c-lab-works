/**
 * @author  Aviruk Basak, CSE214047, Sem 3, Year 2
 * @topic   Matrix data structure implemented in C using a 1D matrix
 * @date    29-7-2022
 * @cc      gcc -Wall -D MTX_TYPE=int -D TYPE_FORMAT='"%d"' -o dsa-int-Matrix dsa-Matrix.c
 */

# include <stdio.h>
# include <stdlib.h>

# if !defined(MTX_TYPE) || !defined(TYPE_FORMAT)
#    undef  MTX_TYPE
#    undef  TYPE_FORMAT
#    define MTX_TYPE     int
#    define TYPE_FORMAT  "%d"
# endif

# define ERR_NULLPTR       (200)
# define ERR_OUTOFBOUNDS   (201)
# define ERR_MATINCOM      (202)
# define ERR_MENUDRIVELIM  (204)

# define MENUDRIVE_LIMIT  ((size_t) 10000)

typedef MTX_TYPE  MatrixType;

typedef struct Matrix {
    MatrixType *ptr;
    size_t rows;
    size_t cols;
} *Matrix;

void mtx_nullPtrCheck(char *fname, Matrix arr);
Matrix new_matrix(size_t rows, size_t cols);
Matrix mtx_arrToMatrix(size_t rows, size_t cols, MatrixType arr[rows][cols]);
void mtx_print(Matrix mtx);
MatrixType mtx_get(Matrix mtx, size_t row, size_t col);
void mtx_set(Matrix mtx, size_t row, size_t col, MatrixType val);
Matrix mtx_add(Matrix mtx1, Matrix mtx2);
Matrix mtx_scale(Matrix mtx, MatrixType scalar);
Matrix mtx_multiply(Matrix mtx1, Matrix mtx2);
Matrix mtx_transpose(Matrix mtx);
void mtx_free(Matrix *mtx_ptr);

void arr_nullPtrCheck(char *fname, Matrix mtx)
{
    if (!mtx || !mtx->ptr) {
        printf("matrix: %s: null pointer\n", fname);
        exit(ERR_NULLPTR);
    }
}

Matrix new_matrix(size_t rows, size_t cols)
{
    Matrix mtx = malloc(sizeof(struct Matrix));
    arr_nullPtrCheck("new1", mtx);
    mtx->ptr = malloc(rows * cols * sizeof(MatrixType));
    arr_nullPtrCheck("new2", mtx);
    return mtx;
}

Matrix mtx_arrToMatrix(size_t rows, size_t cols, MatrixType arr[rows][cols])
{
    size_t i, j;
    Matrix mtx = new_matrix(rows, cols);
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            mtx_set(mtx, i, j, arr[i][j]);
    return mtx;
}

void mtx_print(Matrix mtx)
{
    arr_nullPtrCheck("print", mtx);
    size_t i, j;
    printf("size = %zu x %zu\n", mtx->rows, mtx->cols);
    for (i = 0; i < mtx->rows; i++) {
        for (j = 0; j < mtx->cols; j++)
            printf("%zu: " TYPE_FORMAT "\t", j, mtx_get(mtx, i, j));
        printf("\n");
    }
}

MatrixType mtx_get(Matrix mtx, size_t row, size_t col)
{
    arr_nullPtrCheck("get", mtx);
    if (row >= mtx->rows || col >= mtx->cols) {
        printf("matrix: get: index out of bounds: %zu, %zu\n", row, col);
        exit(ERR_OUTOFBOUNDS);
    }
    return mtx->ptr[row * mtx->rows + col];
}

void mtx_set(Matrix mtx, size_t row, size_t col, MatrixType val)
{
    arr_nullPtrCheck("set", mtx);
    mtx->ptr[row * mtx->rows + col] = val;
}

Matrix mtx_add(Matrix mtx1, Matrix mtx2)
{
    arr_nullPtrCheck("add", mtx1);
    arr_nullPtrCheck("add", mtx2);
    if (mtx1->rows != mtx2->rows || mtx1->cols != mtx2->cols) {
        printf("matrix: add: incompatible matrices\n");
        exit(ERR_MATINCOM);
    }
    size_t i, j;
    Matrix rmtx = new_matrix(mtx1->rows, mtx1->cols);
    for (i = 0; i < rmtx->rows; i++) {
        for (j = 0; j < rmtx->cols; j++) {
            MatrixType sum = mtx_get(mtx1, i, j) + mtx_get(mtx2, i, j);
            set_mtx(rmtx, i, j, sum);
        }
    }
    return rmtx;
}

Matrix mtx_scale(Matrix mtx, MatrixType scalar)
{
    arr_nullPtrCheck("scale", mtx);
    size_t i, j;
    Matrix rmtx = new_matrix(mtx->rows, mtx->cols);
    for (i = 0; i < rmtx->rows; i++) {
        for (j = 0; j < rmtx->cols; j++) {
            MatrixType prod = mtx_get(mtx, i, j) * scalar;
            set_mtx(rmtx, i, j, prod);
        }
    }
    return rmtx;
}

Matrix mtx_multiply(Matrix mtx1, Matrix mtx2)
{
    arr_nullPtrCheck("multiply", mtx1);
    arr_nullPtrCheck("multiply", mtx2);
}

Matrix mtx_transpose(Matrix mtx)
{
    arr_nullPtrCheck("transpose", mtx);
    Matrix tmtx = new_matrix(mtx->cols, mtx->rows);
    size_t i, j;
    for (i = 0; i < tmtx->rows; i++)
        for (j = 0; j < tmtx->cols; j++)
            mtx_set(tmtx, i, j, mtx_get(mtx, j, i));
    return tmtx;
}

void arr_free(Matrix* mtx_ptr)
{
    if (mtx_ptr && *mtx_ptr && (*mtx_ptr)->ptr) {
        free((*mtx_ptr)->ptr);
        free(*mtx_ptr);
        *mtx_ptr = NULL;
    }
}
