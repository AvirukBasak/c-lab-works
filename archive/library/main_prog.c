/* Demonstrating use of user defined library
 * function:
 *
 * The following program continuously asks for
 * input and checks if the number is an Armstrong
 * number. Program termintes if 0 is entered.
 */

# include <stdio.h>
# include "lib_armstrong.h"

int main()
{
    int num;
    while (1) {
        printf ("Enter a number: ");
        scanf ("%d", &num);
        if (num == 0) {
            printf ("Program terminated\n");
            return 0;
        }
        if (is_armstrong (num)) {
            printf ("%d is armstrong\n", num);
        } else {
            printf ("%d isn't armstrong\n", num);
        }
    }
    return 0;
}


