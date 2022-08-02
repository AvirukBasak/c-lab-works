/**
 * @author  Aviruk Basak, CSE214047, Sem 3, Year 2
 * @topic   Using Langrang Interpolation to find f(a) for a given data set and a given value of 'a'
 * @date    25-7-2022
 * @cc      gcc -Wall -lm -o bisection-method bisection-method.c
 */

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

typedef struct { double a; double b; } Interval;
int signum(double x);
Interval calcInterval(double (*f)(double x));
double *bisectAndSolve(double (*f)(double x));
void printRoots(double *roots);

size_t ITERATIONS;

int sign(double x)
{
    if (x < 0)
        return -1;
    else if (x > 0)
        return +1;
    else
        return x;
}

Interval calcInterval(double (*f)(double x))
{
    Interval itvl = { 0, 0 };
    return itvl;
}

double *bisectAndSolve(double (*f)(double x))
{
    double a, b, t, fa, fb, ft;
    size_t i = 0;
    Interval itvl = calcInterval(f);
    a = itvl.a;
    b = itvl.b;
    for (i = 0; i < ITERATIONS; i++) {
        t = a + b / 2;
        fa = f(a);
        fb = f(b);
        ft = f(t);
        if (sign(fa) == sign(ft)) {
            a = t;
        } else if (sign(fb) == sign(ft)) {
            b = t;
        } else {
            printf("¯\\_(ツ)_/¯\n");
        }
    }
    return NULL;
}

void printRoots(double *roots)
{
    size_t root_count, i;
    if (!roots) {
        printf("error: no roots passed\n");
        abort();
    }
    root_count = (size_t) roots[0];
    printf("roots = { ");
    for (i = 1; i <= root_count; i++) {
        printf("%0.5lf%s", roots[i], i == root_count ? " " : ", ");
    }
    printf("}\n");
    free(roots);
}

double f1(double x)
{
    // f1(x) = x⁴ - x - 10
    return pow(x, 4) - x - 10;
}

double f2(double x)
{
    // f1(x) = x - e^x
    return x - exp(x);
}

double f3(double x)
{
    // f1(x) = e^(-x) - 3 log(x)
    return exp(-x) - 3 * log(x);
}

double f4(double x)
{
    // f1(x) = e^(-x) * (x² + 5x + 2) + 1
    return exp(-x) * (pow(x, 2) + 5 * x + 2) + 1;
}

int main()
{
    ITERATIONS = 15;
    printRoots(bisectAndSolve(f1));
    printRoots(bisectAndSolve(f2));
    printRoots(bisectAndSolve(f3));
    printRoots(bisectAndSolve(f4));
    return 0;
}
