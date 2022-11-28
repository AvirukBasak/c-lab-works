/**
 * @author  Aviruk Basak, CSE214047, Sem 3, Year 2
 * @topic   SDA searching algotithms
 * @date    25-11-2022
 */

# include <stdio.h>
# include <stdlib.h>

typedef int ArrayType;
typedef ArrayType *Array;

int arr_lnr_search(Array arr, size_t sz, ArrayType val);
int arr_bin_search(Array arr, size_t sz, ArrayType val);

Array arr_new(size_t size);
void arr_print(Array arr, size_t size);
void arr_free(Array* arr_ptr);

int arr_lnr_search(Array arr, size_t sz, ArrayType val)
{
    for (int i = 0; i < sz; i++)
        if (arr[i] == val) return i;
    return -1;
}

int arr_bin_search(Array arr, size_t sz, ArrayType val)
{
    int l = 0,
        u = sz-1,
        m = sz / 2,
        c = 0;
    while (c++ < sz)
        if (arr[m] > val)
            m = (l + (u = m)) / 2;
        else if (arr[m] < val)
            m = ((l = m) + u) / 2;
        else return m;
    return -1;
}

Array arr_new(size_t size)
{
    Array arr = calloc(sizeof(ArrayType), size);
    return arr;
}

void arr_print(Array arr, size_t size)
{
    size_t i;
    printf("{ ");
    for (i = 0; i < size; i++) {
        printf("%d%s", arr[i], i == size-1 ? " " : ", ");
    }
    printf("}\n");
}

void arr_free(Array* arr_ptr)
{
    if (arr_ptr && *arr_ptr) {
        free(*arr_ptr);
        *arr_ptr = NULL;
    }
}

int main()
{
    Array arr = NULL;
    do {
        printf(
            "\nchoices:\n"
            "   0: exit\n"
            "   1: input array\n"
            "   2: print array\n"
            "   3: linear search for value\n"
            "   4: binary search value\n"
            "enter your choice: "
        );
        int choice;
        scanf("%d", &choice);
        printf("\n");
        switch (choice) {
            // exit
            case 0: exit(0);
            // input array
            case 1:
                // free previous array
                arr_free(&arr);
                printf("enter no of elements to store: ");
                const size_t len = ({ size_t _len; scanf("%zu", &_len); _len; });
                arr = arr_new(len);
                printf("enter %zu elements = ", len);
                for (int i = 0; i < len; i++)
                    scanf("%d", &arr[i]);
                break;
            // print
            case 2: {
                printf("arr  = ");
                arr_print(arr, len);
                printf("len  = %zu\n", len);
                break;
            }
            // linear search
            case 3: {
                printf("enter value to be searched: ");
                ArrayType val;
                scanf("%d", &val);
                int idx = arr_lnr_search(arr, len, val);
                if (idx < 0) {
                    printf("value not found\n");
                } else {
                    printf("value '%d' found at index = %d\n", val, idx);
                }
                break;
            }
            // binary search
            case 4: {
                printf("enter value to be searched: ");
                ArrayType val;
                scanf("%d", &val);
                int idx = arr_bin_search(arr, len, val);
                if (idx < 0) {
                    printf("value not found\n");
                } else {
                    printf("value '%d' found at index = %d\n", val, idx);
                }
                break;
            }
            default: printf("choice invalid\n");
        }
    } while (1);
    return 0;
}

/* OUTPUT:

choices:
   0: exit
   1: input array
   2: print array
   3: linear search for value
   4: binary search value
enter your choice: 1

enter no of elements to store: 10
enter 10 elements = 2 4 8 12 34 56 59 68 93 102

choices:
   0: exit
   1: input array
   2: print array
   3: linear search for value
   4: binary search value
enter your choice: 2

arr  = { 2, 4, 8, 12, 34, 56, 59, 68, 93, 102 }
len  = 10

choices:
   0: exit
   1: input array
   2: print array
   3: linear search for value
   4: binary search value
enter your choice: 4

enter value to be searched: 24
value not found

choices:
   0: exit
   1: input array
   2: print array
   3: linear search for value
   4: binary search value
enter your choice: 4

enter value to be searched: 34
value '34' found at index = 4

choices:
   0: exit
   1: input array
   2: print array
   3: linear search for value
   4: binary search value
enter your choice: 3

enter value to be searched: 34
value '34' found at index = 4

choices:
   0: exit
   1: input array
   2: print array
   3: linear search for value
   4: binary search value
enter your choice: 3

enter value to be searched: 93
value '93' found at index = 8

choices:
   0: exit
   1: input array
   2: print array
   3: linear search for value
   4: binary search value
enter your choice: 0

*/
