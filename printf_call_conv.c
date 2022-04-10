/* Program to demonstrate pre-post increment operators
 */

# include <stdio.h>

int main()
{
    int x = 5, y = 7;

    printf ("%d, %d, %d\n", x++, x, ++x);
    printf ("%d, %d, %d\n", ++y, y, y++);

    return 0;
}
