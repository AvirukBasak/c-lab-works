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

void arr_nullPtrCheck(char *fname, Array arr);
Array new_array(size_t size);
Array arr_resize(Array arr, size_t size, size_t new_sz);
void arr_print(Array arr, size_t size);
void arr_traverse(Array arr, size_t size, void (*callback)(ArrayType el));
size_t arr_search(Array arr, size_t size, ArrayType val);
size_t *arr_searchAll(Array arr, size_t size, ArrayType val, size_t *matches);
Array arr_insert(Array arr, size_t size, size_t index, ArrayType val);
Array arr_deleteIndex(Array arr, size_t size, size_t index);
Array arr_deleteValue(Array arr, size_t size, ArrayType val);
Array arr_concat(Array arr1, size_t sz1, Array arr2, size_t sz2, size_t *new_sz);
Array arr_merge(Array arr1, size_t sz1, Array arr2, size_t sz2, size_t *new_sz);
Array arr_intersect(Array arr1, size_t sz1, Array arr2, size_t sz2, size_t *new_sz);
void arr_free(Array* arr_ptr);

void arr_nullPtrCheck(char *fname, Array arr)
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
    arr_nullPtrCheck("new", arr);
    return arr;
}

Array arr_resize(Array arr, size_t size, size_t new_sz)
{
    size_t i;
    arr_nullPtrCheck("resize", arr);
    // calloc initialises all indices with 0, last index 0 indicates atleast 1 empty index
    Array arr2 = calloc(sizeof(ArrayType), new_sz);
    arr_nullPtrCheck("resize", arr2);
    for (i = 0; i < new_sz; i++) {
        if (i >= size)
            break;
        arr2[i] = arr[i];
    }
    free(arr);
    return arr2;
}

void arr_print(Array arr, size_t size)
{
    size_t i;
    arr_nullPtrCheck("print", arr);
    printf("{ ");
    for (i = 0; i < size; i++) {
        printf(TYPE_FORMAT "%s", arr[i], i == size -1 ? " " : ", ");
    }
    printf("}\n");
}

void arr_traverse(Array arr, size_t size, void (*callback)(ArrayType el))
{
    size_t i;
    arr_nullPtrCheck("traverse", arr);
    for (i = 0; i < size; i++) {
        callback(arr[i]);
    }
}

size_t arr_search(Array arr, size_t size, ArrayType val)
{
    size_t i;
    for (i = 0; i < size; i++) {
        if (arr[i] == val)
            return i;
    }
    return size;
}

size_t *arr_searchAll(Array arr, size_t size, ArrayType val, size_t *matches)
{
    size_t *locations, i;
    *matches = 0;
    locations = NULL;
    arr_nullPtrCheck("search all", arr);
    for (i = 0; i < size; i++) {
        if (arr[i] == val) {
            locations = realloc(locations, ++(*matches) * sizeof(size_t));
            if (!locations) {
                printf("array: search all: null pointer\n");
                exit(ERR_NULLPTR);
            }
            locations[*matches -1] = i;
        }
    }
    return locations;
}

Array arr_insert(Array arr, size_t size, size_t index, ArrayType val)
{
    size_t i;
    arr_nullPtrCheck("insert", arr);
    if (index >= size) {
        printf("array: insert: index out of bounds\n");
        exit(ERR_OUTOFBOUNDS);
    } else if (arr[size -1] != 0) {
        printf("array: insert: array is full\n");
        exit(ERR_ARRAYFULL);
    }
    for (i = size -1; i > index; i--) {
        arr[i] = arr[i -1];
    }
    arr[index] = val;
    return arr;
}

Array arr_deleteIndex(Array arr, size_t size, size_t index)
{
    size_t i;
    arr_nullPtrCheck("delete index", arr);
    if (index >= size) {
        printf("array: delete index: index out of bounds\n");
        exit(ERR_OUTOFBOUNDS);
    }
    for (i = index; i < size -1; i++) {
        arr[i] = arr[i +1];
    }
    arr[i] = 0;
    return arr;
}

Array arr_deleteValue(Array arr, size_t size, ArrayType val)
{
    size_t *locations = NULL, *matches = 0, i;
    arr_nullPtrCheck("delete value", arr);
    locations = arr_searchAll(arr, size, val, matches);
    if (!locations) {
        printf("array: delete value: null pointer\n");
        exit(ERR_NULLPTR);
    }
    for (i = 0; i < *matches; i++) {
        arr_deleteIndex(arr, size, locations[i]);
    }
    free(locations);
    return arr;
}

Array arr_concat(Array arr1, size_t sz1, Array arr2, size_t sz2, size_t *new_sz)
{
    size_t i, j, k;
    arr_nullPtrCheck("concat", arr1);
    arr_nullPtrCheck("concat", arr2);
    *new_sz = sz1 + sz2;
    Array arr3 = new_array(*new_sz);
    for (i = k = 0; i < sz1 && k < *new_sz; i++, k++) {
        arr3[k] = arr1[i];
    }
    for (j = 0; j < sz2 && k < *new_sz; j++, k++) {
        arr3[k] = arr1[j];
    }
    return arr3;
}

Array arr_merge(Array arr1, size_t sz1, Array arr2, size_t sz2, size_t *new_sz)
{
    
}

Array arr_intersect(Array arr1, size_t sz1, Array arr2, size_t sz2, size_t *new_sz);

void arr_free(Array* arr_ptr)
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
