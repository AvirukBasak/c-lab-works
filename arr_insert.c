# include <stdio.h>

# define ARR_MAX_SIZE 1000

int main()
{
    int i, len, idx, num, arr[ARR_MAX_SIZE];

    printf("Enter arr len: ");
    scanf("%d", &len);

    for (i = 0; i < len; i++) {
        printf("arr[%d] = ", i);
        scanf("%d", &arr[i]);
    }

    printf("Enter index: ");
    scanf("%d", &idx);
    printf("Enter num: ");
    scanf("%d", &num);

    for (i = len; i > idx; i--)
        arr[i] = arr[i-1];
    arr[idx] = num;

    for (i = 0; i < len + 1; i++)
        printf("arr[%d] = %d\n", i, arr[i]);
    return 0;    
}
