/**
 * @author  Aviruk Basak, CSE214047, Sem 3, Year 2
 * @topic   SDA sorting algotithms
 * @date    25-11-2022
 */

# include <stdio.h>
# include <stdlib.h>

typedef int ArrayType;
typedef ArrayType *Array;

Array arr_sel_sort(Array arr, size_t sz);
Array arr_bub_sort(Array arr, size_t sz);
Array arr_ins_sort(Array arr, size_t sz);

Array arr_new(size_t size);
void arr_print(Array arr, size_t size);
void arr_free(Array* arr_ptr);

Array arr_sel_sort(Array arr, size_t sz)
{
    int i, j, m;
    for (i = 0; i < sz-1; i++) {
        m = i;
        for (j = i+1; j < sz; j++)
            if (arr[j] < arr[m]) m = j;
        if (m != i) {
            ArrayType tmp = arr[m];
            arr[m] = arr[i];
            arr[i] = tmp;
        }
    }
    return arr;
}

Array arr_bub_sort(Array arr, size_t sz)
{
    int i, j;
    for (i = 0; i < sz-1; i++)
        for (j = 0; j < sz-i - 1; j++)
            if (arr[j] > arr[j+1]) {
                ArrayType tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
    return arr;
}

Array arr_ins_sort(Array arr, size_t sz)
{
    int i, key, j;
    for (i = 1; i < sz; i++) {
        key = arr[i];
        j = i -1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
    return arr;
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
            "   3: selection sort\n"
            "   4: bubble sort\n"
            "   5: insertion sort\n"
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
            // selection sort
            case 3: {
                printf("arr  = ");
                arr_print(arr_sel_sort(arr, len), len);
                break;
            }
            // bubble sort
            case 4: {
                printf("arr  = ");
                arr_print(arr_bub_sort(arr, len), len);
                break;
            }
            // insertion sort
            case 5: {
                printf("arr  = ");
                arr_print(arr_ins_sort(arr, len), len);
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
   3: selection sort
   4: bubble sort
   5: insertion sort
enter your choice: 1

enter no of elements to store: 17
enter 17 elements = 78 34 56 12 3 98 23 4 56 91 42 69 420 21 90 101 92

choices:
   0: exit
   1: input array
   2: print array
   3: selection sort
   4: bubble sort
   5: insertion sort
enter your choice: 2

arr  = { 78, 34, 56, 12, 3, 98, 23, 4, 56, 91, 42, 69, 420, 21, 90, 101, 92 }
len  = 17

choices:
   0: exit
   1: input array
   2: print array
   3: selection sort
   4: bubble sort
   5: insertion sort
enter your choice: 3

arr  = { 3, 4, 12, 21, 23, 34, 42, 56, 56, 69, 78, 90, 91, 92, 98, 101, 420 }

choices:
   0: exit
   1: input array
   2: print array
   3: selection sort
   4: bubble sort
   5: insertion sort
enter your choice: 4

arr  = { 3, 4, 12, 21, 23, 34, 42, 56, 56, 69, 78, 90, 91, 92, 98, 101, 420 }

choices:
   0: exit
   1: input array
   2: print array
   3: selection sort
   4: bubble sort
   5: insertion sort
enter your choice: 5

arr  = { 3, 4, 12, 21, 23, 34, 42, 56, 56, 69, 78, 90, 91, 92, 98, 101, 420 }

choices:
   0: exit
   1: input array
   2: print array
   3: selection sort
   4: bubble sort
   5: insertion sort
enter your choice: 0

*/
