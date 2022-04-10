# include <stdio.h>
# include <stdlib.h>

# define MIN(A, B) ({\
    typeof (A) macro_a = (A);                 \
    typeof (B) macro_b = (B);                 \
    macro_a < macro_b ? macro_a : macro_b;    \
})

int get_randn()
{
    int num = (int) (rand() % 100);
    printf ("num = %d\n", num);
    return num;
}

int main()
{
    printf ("%d\n", MIN (45, 65));
    printf ("%d\n", MIN (get_randn(), get_randn()));
    return 0;
}
