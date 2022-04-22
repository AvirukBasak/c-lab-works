# include <stdio.h>

int factorial (int num, int rslt)
{
    if (num == 0 || num == 1) {
        return rslt;
    } else {
        return factorial (num - 1, num * rslt);
    }
}

int main()
{
    int num;
    printf ("Enter a number: ");
    scanf ("%d", &num);
    printf ("Factorial = %d\n", factorial (num, 1));
    return 0;
}
