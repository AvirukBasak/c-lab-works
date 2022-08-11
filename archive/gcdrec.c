# include <stdio.h>

int gcd(int D, int d)
{
    if (D % d == 0)
        return d;
    else
        return gcd (d, D % d);
}

int main()
{
    int a, b, D, d;
    printf("enter 2 numbers: ");
    scanf("%d %d", &a, &b);
    D = (a >= b) ? a : b;
    d = (a <= b) ? a : b;
    printf("gcd = %d\n", gcd(D, d));
    return 0;
}
