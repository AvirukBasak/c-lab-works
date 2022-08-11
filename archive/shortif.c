# include <stdio.h>

# define true  (1)
# define false (0)

void print(char *s) {
    printf("%s", s);
}

int main()
{
    // test 1
    (true) ? (
        printf("st 1\n"),
        printf("st 2\n"),
        printf("st 3\n"),
        0
    ) : (
        printf("else\n"),
        0
    );

    // test 2
    (true) && (
        print("short 1\n"),
        print("short 2\n"),
        0
    );

    return 0;
}
