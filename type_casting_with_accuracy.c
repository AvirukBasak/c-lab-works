/* Program to demonstrate type casting
 */

# include <stdio.h>

int main()
{
    int x = 8574, y = 100;

    /* NOTE: this casts x to float and then does the division
     * If (float) isn't used, the result will only be 85.
     */
    float result = (float) x / y;

    printf ("Result = %0.2lf\n", result);
    return 0;
}
