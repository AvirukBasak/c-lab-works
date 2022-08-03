/**
 * @author  Aviruk Basak, CSE214047, Sem 3, Year 2
 * @topic   Using Bisection Method to find f(a) for a given data set and a given value of 'a'
 * @date    3-8-2022
 * @cc      gcc -Wall -lm -o fixed-pt-iter fixed-pt-iter.c
 */

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

# define TOLERANCE      (0.001)
# define MAX_ITERATIONS (1000)
# define FLOAT_FORMAT   "%0.3lf"

typedef struct {
    double a;
    double b;
} Tuple;

int signum(double x);
void printWithErr(Tuple intrvl);
Tuple iterateAndSolve(double (*f)(double x), Tuple intrvl);

void printWithErr(Tuple intrvl)
{
    double ea, er, ep;
    ea = intrvl.a - intrvl.b;
    er = ea / intrvl.a;
    ep = er * 100;
    printf("  result = " FLOAT_FORMAT ", " FLOAT_FORMAT "\n", intrvl.a, intrvl.b);
    printf("    exact error      = " FLOAT_FORMAT "\n", ea);
    printf("    relative error   = " FLOAT_FORMAT "\n", er);
    printf("    percentage error = " FLOAT_FORMAT "\n", ep);
}

double iterateAndSolve(double (*f)(double x), Tuple intrvl)
{
    double xn;
    size_t i = 0;
    while (i < MAX_ITERATIONS) {
        if (f(xn) == 0 || fabs(intrvl.a - intrvl.b) < TOLERANCE) {
            return intrvl;
        } else {
            intrvl.a = xn;
            xn = f(xn);
            intrvl.b = xn;
        }
        i++;
    }
    return intrvl;
}

double f1(double x)
{
    // f(x) =
    return 0;
}

double f2(double x)
{
    // f(x) =
    return 0;
}

double f3(double x)
{
    // f(x) =
    return 0;
}

double f4(double x)
{
    // f(x) =
    return 0;
}

int main()
{
    Tuple it1 = { 0, 0 };
    printf("\nf(x) =\n");
    printRoot(iterateAndSolve(f1, it1));

    Tuple it2 = { 0, 0 };
    printf("\nf(x) =\n");
    printRoot(iterateAndSolve(f2, it2));

    Tuple it3 = { 0, 0 };
    printf("\nf(x) =\n");
    printRoot(iterateAndSolve(f3, it3));

    Tuple it4 = { 0, 0 };
    printf("\nf(x) =\n");
    printRoot(iterateAndSolve(f4, it4));

    return 0;
}
