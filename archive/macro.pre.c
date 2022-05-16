# include <stdio.h>
# include <stdlib.h>

int get_randn()
{
    int num = (int) (rand() % 100);
    printf ("num = %d\n", num);
    return num;
}

int main()
{
    printf ("%d\n", (
        {
            typeof (45) macro_a = (45);
            typeof (65) macro_b = (65);
            macro_a < macro_b ? macro_a : macro_b;
        }
    ));
    printf ("%d\n", (
        {
            typeof (get_randn()) macro_a = (get_randn());
            typeof (get_randn()) macro_b = (get_randn());
            macro_a < macro_b ? macro_a : macro_b;
        }
    ));
    return 0;
}
