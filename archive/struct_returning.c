# include <stdio.h>
# include <stdlib.h>

typedef struct demo
{
    int n1;
    int n2;
    int n3;
} demo;

demo *return_by_reference()
{
    demo *d_ptr = malloc (1 * sizeof (demo));
    d_ptr->n1 = 5;
    d_ptr->n2 = 6;
    d_ptr->n3 = 7;
    return d_ptr;
}

demo return_by_value()
{
    demo *d_ptr = malloc (1 * sizeof (demo));
    // struct pointer dereferenced and value returned
    demo d = *d_ptr;
    free (d_ptr);
    d.n1 = 11;
    d.n2 = 12;
    d.n3 = 13;
    return d;
}

int main()
{
    demo *ad = return_by_reference();
    demo bd = return_by_value();
    printf ("ptr: n1 = %d\n"
            "     n2 = %d\n"
            "     n3 = %d\n", ad->n1, ad->n2, ad->n3);
    // printf ("\n");
    printf ("val: n1 = %d\n"
            "     n2 = %d\n"
            "     n3 = %d\n", bd.n1, bd.n2, bd.n3);
    free (ad);
    return 0;
}
