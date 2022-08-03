/**
 * @author  Aviruk Basak, CSE214047, Sem 3, Year 2
 * @topic   1 dimensional array data structure implemented in C
 * @date    3-8-2022
 * @cc      gcc -Wall -D ARR_TYPE=int -D TYPE_FORMAT='"%d"' -o dsa-int-array dsa-array.c
 */

# include <stdio.h>
# include <stdlib.h>

# if !defined(ARR_TYPE) || !defined(TYPE_FORMAT)
#    undef  ARR_TYPE
#    undef  TYPE_FORMAT
#    define ARR_TYPE     int
#    define TYPE_FORMAT  "%d"
# endif

# define ERR_NULLPTR     (200)
# define ERR_OUTOFBOUNDS (201)
# define ERR_ARRAYFULL   (203)

typedef ARR_TYPE  ArrayType;
typedef ARR_TYPE* Array;

void array_nullptr_check(char *fname, Array arr);
Array new_array(size_t size);
void array_print(Array arr, size_t size);
void array_traverse(Array arr, size_t size, void (*callback)(ArrayType el));
size_t array_search(Array arr, size_t size, ArrayType key);
size_t *array_searchAll(Array arr, size_t size, ArrayType key, size_t *matches);
Array array_insert(Array arr, size_t size, size_t loc, ArrayType key);
Array array_deleteLoc(Array arr, size_t size, size_t loc);
Array array_deleteKey(Array arr, size_t size, ArrayType key);
Array array_concat(Array arr1, size_t sz1, Array arr2, size_t sz2, size_t *new_sz);
Array array_merge(Array arr1, size_t sz1, Array arr2, size_t sz2, size_t *new_sz);
Array array_intersect(Array arr1, size_t sz1, Array arr2, size_t sz2, size_t *new_sz);
void array_free(Array* arr_ptr);

void array_nullptr_check(char *fname, Array arr)
{
    if (!arr) {
        printf("array: %s: null pointer\n", fname);
        exit(ERR_NULLPTR);
    }
}

Array new_array(size_t size)
{
    // calloc initialises all indices with 0, last index 0 indicates atleast 1 empty index
    Array arr = calloc(sizeof(ArrayType), size);
    array_nullptr_check("new", arr);
    return arr;
}

void array_print(Array arr, size_t size)
{
    size_t i;
    array_nullptr_check("print", arr);
    printf("{ ");
    for (i = 0; i < size; i++) {
        printf(TYPE_FORMAT "%s", arr[i], i == size -1 ? " " : ", ");
    }
    printf("}\n");
}

void array_traverse(Array arr, size_t size, void (*callback)(ArrayType el))
{
    size_t i;
    array_nullptr_check("traverse", arr);
    for (i = 0; i < size; i++) {
        callback(arr[i]);
    }
}

size_t array_search(Array arr, size_t size, ArrayType key)
{
    size_t i;
    for (i = 0; i < size; i++) {
        if (arr[i] == key)
            return i;
    }
    return size;
}

size_t *array_searchAll(Array arr, size_t size, ArrayType key, size_t *matches)
{
    return NULL;
}

Array array_insert(Array arr, size_t size, size_t loc, ArrayType key)
{
    size_t i;
    array_nullptr_check("insert", arr);
    if (loc >= size) {
        printf("array: insert: index out of bounds\n");
        exit(ERR_OUTOFBOUNDS);
    } else if (arr[size -1] != 0) {
        printf("array: insert: array is full\n");
        exit(ERR_ARRAYFULL);
    }
    for (i = size -1; i > loc; i--) {
        arr[i] = arr[i -1];
    }
    arr[loc] = key;
    return arr;
}

void array_free(Array* arr_ptr)
{
    if (arr_ptr && *arr_ptr) {
        free(*arr_ptr);
        *arr_ptr = NULL;
    }
}

int main()
{
    return 0;
}
