/**
 * @author  Aviruk Basak, CSE214047, Sem 3, Year 2
 * @topic   Using Langrang Interpolation to find f(a) for a given data set and a given value of 'a'
 * @date    25-7-2022
 */

# include <stdio.h>
# include <stdlib.h>

double lagrangeInterp(double *arr_x, double *arr_y, size_t total_points, double a)
{
    size_t i, j;
    double rslt = 0,     // result
           numtr = 1,    // numerator of a term
           dentr = 1;    // denominator of a term
    for (i = 0; i < total_points; i++) {
        numtr = arr_y[i];
        dentr = 1;
        for (j = 0; j < total_points; j++) {
            if (i != j) {
                numtr = numtr * (a - arr_x[j]);
                dentr = dentr * (arr_x[i] - arr_x[j]);
            }
        }
        rslt += numtr / dentr;
    }
    return rslt;
}

int main()
{
    size_t total_points, i;
    double *arr_x,         // X coordinates array
           *arr_y,         // Y coordinates array
           a,              // value whose f(a) is to be found
           rslt = 0;       // result

    printf("Enter total points = ");
    scanf("%zu", &total_points);

    arr_x = malloc(sizeof(double) * total_points);
    arr_y = malloc(sizeof(double) * total_points);

    printf("Enter items of array X = ");
    for (i = 0; i < total_points; i++)
        scanf("%lf", &arr_x[i]);

    printf("Enter items of array Y = ");
    for (i = 0; i < total_points; i++)
        scanf("%lf", &arr_y[i]);

    while (1) {
        printf("\nEnter value of a = ");
        scanf("%lf", &a);
        rslt = lagrangeInterp(arr_x, arr_y, total_points, a);
        if (a - (long long int) a == 0) {
            printf("f(%lld) = %0.5lf\n", (long long int) a, rslt);
        } else {
            printf("f(%0.5lf) = %0.5lf\n", a, rslt);
        }
    }

    free(arr_x);
    free(arr_y);

    return 0;
}
