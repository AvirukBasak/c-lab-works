/* Program to demonstrate pre-post increment operators
 */

# include <stdio.h>

int main()
{
    int x = 5, y = 7, result = 0;

    printf ("Before calculation:\n"
            "  x = %d\n"
            "  y = %d\n", x, y);

    // at this stage result = 5 + 8 and x = 6, y = 8
    result = x++ + ++y;

    printf ("\nResult = %d\n\n", result);

    printf ("After calculation:\n"
            "  x = %d\n"
            "  y = %d\n", x, y);

    return 0;
}
