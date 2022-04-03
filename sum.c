/* Program to calculate sum of two numbers
 */

# include <stdio.h>

int main() {
    int num_1 = 0,
        num_2 = 0;

    printf ("Enter num_1 = ");
    scanf ("%d", &num_1);
    printf ("Enter num_2 = ");
    scanf ("%d", &num_2);

    int sum = num_1 + num_2;
    printf ("Sum = %d\n", sum);
    return 0;
}
