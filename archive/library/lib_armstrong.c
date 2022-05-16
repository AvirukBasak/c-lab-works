# include "lib_armstrong.h"

int power (int base, int index);
int dig_count (int n);

int is_armstrong (int n)
{
    int i, sum = 0, length = dig_count (n);
    for (i = n; i > 0; i /= 10) {
        sum += power (i % 10, length);
    }
    return sum == n;
}

int power (int base, int index)
{
    int i, p = 1;
    for (i = 0; i < index; i++) {
        p *= base;
    }
    return p;
}

int dig_count (int n)
{
    int i, count = 0;
    for (i = n; i > 0; i /= 10) {
        count ++;
    }
    return count;
}
