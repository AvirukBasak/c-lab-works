/* Program to calculate sum, difference, product, quotient
 * and reminder of two numbers
 */

# include <stdio.h>

int main()
{
    int num_1 = 0,
        num_2 = 0,
        sum = 0,
        difference = 0,
        product = 0,
        quotient = 0,
        remainder = 0;

    printf ("Enter num_1 = ");
    scanf ("%d", &num_1);
    printf ("Enter num_2 = ");
    scanf ("%d", &num_2);

    sum        = num_1 + num_2;
    difference = num_1 - num_2;
    product    = num_1 * num_2;
    quotient   = num_1 / num_2;
    remainder  = num_1 % num_2;

    printf ("\n");
    printf ("Sum         = %d\n", sum);
    printf ("Difference  = %d\n", difference);
    printf ("Product     = %d\n", product);
    printf ("Quotient    = %d\n", quotient);
    printf ("Remainder   = %d\n", remainder);
    return 0;
}
