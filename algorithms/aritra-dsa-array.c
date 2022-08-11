#include <stdio.h>
#include <stdlib.h>
#define ARR_MAX_SZ (1000)
typedef int Array[ARR_MAX_SZ];

void arrprint(Array A, int l, int u);
int search(Array A, int l, int u, int val);
int *searchAll(Array A, int l, int u, int val, int *matches);
void insert(Array A, int l, int *u, int index, int val);
void delIndex(Array A, int l, int *u, int index);
void delValue(Array A, int l, int *u, int val);
int *concat(Array A, int l1, int u1, Array B, int l2, int u2, int *l3, int *u3);
int *merge(Array A, int l1, int u1, Array B, int l2, int u2, int *l3, int *u3);
int *intersect(Array A, int l1, int u1, Array B, int l2, int u2, int *l3, int *u3);

void arrprint(Array A, int l, int u)
{
    int i;
    printf("{ ");
    for (i = l; i <= u; i++)
        printf("%d%s", A[i], i == u ? " " : ", ");
    printf("}\n");
}

int search(Array A, int l, int u, int val)
{
    int i;
    for (i = l; i <= u; i++)
        if (A[i] == val)
            return i;
    return ARR_MAX_SZ;
}

int *searchAll(Array A, int l, int u, int val, int *matches)
{
    int *indices, i;
    *matches = 0;
    indices = NULL;
    for (i = l; i <= u; i++)
        if (A[i] == val) {
            indices = realloc(indices, ++(*matches) * sizeof(int));
            if (!indices) {
                printf("err: search all: null pointer\n");
                exit(1);
            }
            indices[*matches -1] = i;
        }
    return indices;
}

void insert(Array A, int l, int *u, int index, int val)
{
    int i;
    if (index < l || index > *u +1) {
        printf("err: insert: index out of bounds\n");
        exit(1);
    } else if (A[*u +1] != 0) {
        printf("err: insert: array is full\n");
        exit(1);
    }
    for (i = *u +1; i > index; i--)
        A[i] = A[i -1];
    A[index] = val;
    (*u)++;
}

void delIndex(Array A, int l, int *u, int index)
{
    int i;
    if (index > *u) {
        printf("err: delete index: index out of bounds\n");
        exit(1);
    }
    for (i = index; i <= *u; i++)
        A[i] = A[i +1];
    A[i] = 0;
    (*u)--;
}

void delValue(Array A, int l, int *u, int val)
{
    int *indices = NULL, matches = 0, i;
    indices = searchAll(A, l, *u, val, &matches);
    if (!indices) {
        printf("err: delete value: null pointer\n");
        exit(1);
    }
    for (i = matches -1; i >= 0; i--)
        delIndex(A, l, &(*u), indices[i]);
    free(indices);
}

int *concat(Array A, int l1, int u1, Array B, int l2, int u2, int *l3, int *u3)
{
    int i, j, k;
    i = j = k = 0;
    *l3 = l1;
    *u3 = u1 + u2;
    int *C = calloc(sizeof(int), *u3 - *l3 +1);
    while (i <= u1)
        C[k++] = A[i++];
    while (j <= u2)
        C[k++] = B[j++];
    return C;
}

int *merge(Array A, int l1, int u1, Array B, int l2, int u2, int *l3, int *u3)
{
    int i, j, k;
    i = j = k = 0;
    *l3 = l1;
    *u3 = u1 + u2;
    int *C = calloc(sizeof(int), *u3 - *l3 +1);
    while (i <= u1 && j <= u2)
        if (A[i] < B[j])
            C[k++] = A[i++];
        else if (B[j] < A[i])
            C[k++] = B[j++];
        else
            C[k++] = A[i++] = B[j++];
    while (i <= u1)
        C[k++] = A[i++];
    while (j <= u2)
        C[k++] = B[j++];
    return C;
}

int *intersect(Array A, int l1, int u1, Array B, int l2, int u2, int *l3, int *u3)
{
    int i, j, k;
    i = j = k = 0;
    *l3 = l1;
    *u3 = u1 + u2;
    int *C = calloc(sizeof(int), *u3 - *l3 +1);
    while (i <= u1 && j <= u2)
        if (A[i] < B[j])
            i++;
        else if (B[j] < A[i])
            j++;
        else
            C[k++] = A[i++] = B[j++];
    return C;
}

int main()
{
    int ch;
    Array A;
    int i, l = 0, u;
    printf("lower lim: 0\n");
    printf("upper lim: ");
    scanf("%d", &u);
    printf("enter %d elements = ", u +1);
    for (i = 0; i <= u; i++)
        scanf("%d", &A[i]);
    for (i = u +1; i < ARR_MAX_SZ; i++)
        A[i] = 0;
    do {
        printf(
            "\nchoices:\n"
            "   0: exit\n"
            "   1: print array\n"
            "   2: search for matching value\n"
            "   3: search for every matching value\n"
            "   4: insert a value\n"
            "   5: delete value at index\n"
            "   6: delete every match of a value\n"
            "   7: concatenate two arrays\n"
            "   8: merge two sorted arrays\n"
            "   9: intersection of two sorted arrays\n"
            "enter your choice: "
        );
        scanf("%d", &ch);
        printf("\n");
        switch (ch) {
            // exit
            case 0: {
                break;
            }
            // print
            case 1: {
                printf("A = ");
                arrprint(A, l, u);
                break;
            }
            // search
            case 2: {
                int val, index;
                printf("enter value to be searched: ");
                scanf("%d", &val);
                index = search(A, l, u, val);
                if (index == ARR_MAX_SZ)
                    printf("value not found\n");
                else
                    printf("value '" "%d" "' found at index = %d\n", val, index);
                break;
            }
            // searchAll
            case 3: {
                int val, i, *indices, matches;
                printf("enter value to be searched: ");
                scanf("%d", &val);
                indices = searchAll(A, l, u, val, &matches);
                if (matches == 0)
                    printf("value not found\n");
                else {
                    printf("value '" "%d" "' found at indices: ", val);
                    for (i = 0; i < matches; i++) {
                        printf("%d%s", indices[i], i == matches -1 ? "" : ", ");
                    }
                    printf("\n");
                }
                free(indices);
                break;
            }
            // insert
            case 4: {
                int val, index;
                printf("enter index of insertion: ");
                scanf("%d", &index);
                printf("enter value to be inserted: ");
                scanf("%d", &val);
                insert(A, l, &u, index, val);
                printf("A = ");
                arrprint(A, l, u);
                break;
            }
            // delIndex
            case 5: {
                int index;
                printf("enter index of deletion: ");
                scanf("%d", &index);
                delIndex(A, l, &u, index);
                printf("A = ");
                arrprint(A, l, u);
                break;
            }
            // delValue
            case 6: {
                int val;
                printf("enter value to delete: ");
                scanf("%d", &val);
                delValue(A, l, &u, val);
                printf("A = ");
                arrprint(A, l, u);
                break;
            }
            // concat
            case 7: {
                int l2 = 0, u2, l3, u3;
                printf("second array lower lim: 0\n");
                printf("second array upper lim: ");
                scanf("%d", &u2);
                int *B = calloc(sizeof(int), u2 +1);
                printf("enter %d elements = ", u2 +1);
                for (i = 0; i <= u2; i++)
                    scanf("%d", &B[i]);
                int *C = concat(A, l, u, B, l2, u2, &l3, &u3);
                printf("C = ");
                arrprint(C, l3, u3);
                free(B);
                free(C);
                break;
            }
            // merge
            case 8: {
                int l2 = 0, u2, l3, u3;
                printf("second array lower lim: 0\n");
                printf("second array upper lim: ");
                scanf("%d", &u2);
                int *B = calloc(sizeof(int), u2 +1);
                printf("enter %d elements = ", u2 +1);
                for (i = 0; i <= u2; i++)
                    scanf("%d", &B[i]);
                int *C = merge(A, l, u, B, l2, u2, &l3, &u3);
                printf("C = ");
                arrprint(C, l3, u3);
                free(B);
                free(C);
                break;
            }
            // intersect
            case 9: {
                int l2 = 0, u2, l3, u3;
                printf("second array lower lim: 0\n");
                printf("second array upper lim: ");
                scanf("%d", &u2);
                int *B = calloc(sizeof(int), u2 +1);
                printf("enter %d elements = ", u2 +1);
                for (i = 0; i <= u2; i++)
                    scanf("%d", &B[i]);
                int *C = intersect(A, l, u, B, l2, u2, &l3, &u3);
                printf("C = ");
                arrprint(C, l3, u3);
                free(B);
                free(C);
                break;
            }
            default: {
                printf("choice invalid\n");
            }
        }
    } while (ch);
    return 0;
}
