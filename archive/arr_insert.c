# include <stdio.h>
# include <stdlib.h>

# define ARR_MAX_SIZE 1000

int main()
{
    int i, len, idx, num, arr[ARR_MAX_SIZE];

    printf("Enter arr len: ");
    scanf("%d", &len);

    if (len > ARR_MAX_SIZE) {
        fprintf(stderr, "insert: %d: array length too large\n", len);
        exit(1);
    }

    for (i = 0; i < len; i++) {
        printf("arr[%d] = ", i);
        scanf("%d", &arr[i]);
    }

    printf("Enter index: ");
    scanf("%d", &idx);

    if (idx > len) {
        fprintf(stderr, "insert: %d: index out of bounds\n", idx);
        exit(2);
    }

    printf("Enter num: ");
    scanf("%d", &num);

    for (i = len; i > idx; i--)
        arr[i] = arr[i-1];
    arr[idx] = num;

    for (i = 0; i < len + 1; i++)
        printf("arr[%d] = %d\n", i, arr[i]);
    return 0;    
}
