# include <stdio.h>

# define B8_BIN "%08llu"         // format specifier for 8 bit binary
# define byte unsigned char      // definition of a byte type

// this function takes 1 byte and returns its binary
unsigned long long bin (byte n)
{
    unsigned long long bin = 0;
    unsigned int rem, i = 1;
    while (n) {
        rem = n % 2;
        n /= 2;
        bin += rem * i;
        i *= 10;
    }
    return bin;
}

int main()
{
    // put your experiments here
    byte x = 10;
    printf("%d  -> " B8_BIN "\n", x, bin(x));
    printf("1's -> " B8_BIN "\n", bin(~x));
    printf("2's -> " B8_BIN "\n", bin(-x));
}
