# include <stdio.h>
# include <stdlib.h>

typedef struct demo
{
    int n1;
    int n2;
    int n3;
} demo;

int main()
{
    demo d1, d2;
    d1.n1 = 5;
    d1.n2 = 6;
    d1.n3 = 7;
    printf ("d1 after declaration:\n"
            "     n1 = %d\n"
            "     n2 = %d\n"
            "     n3 = %d\n", d1.n1, d1.n2, d1.n3);
    d2 = d1;
    printf ("d2 after assignment:\n"
            "     n1 = %d\n"
            "     n2 = %d\n"
            "     n3 = %d\n", d2.n1, d2.n2, d2.n3);
    d1.n1 = 11;
    d1.n2 = 12;
    d1.n3 = 13;
    printf ("d1 after modification:\n"
            "     n1 = %d\n"
            "     n2 = %d\n"
            "     n3 = %d\n", d1.n1, d1.n2, d1.n3);
    printf ("d2 after d1 modification:\n"
            "     n1 = %d\n"
            "     n2 = %d\n"
            "     n3 = %d\n", d2.n1, d2.n2, d2.n3);
    return 0;
}
