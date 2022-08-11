# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define MAX_SZ 1000
typedef char* string;

// WARNING: updates string via passed pointer
int strnin(string str, size_t len)
{
    size_t i;
    char c;
    if (!str || len >= MAX_SZ)
        return 0;
    for (i = 0; i < len;) {
        c = getchar();
        if ((i == 0) && c == '\n')
            continue;
        else {
            str[i] = c;
            i++;
        }
    }
    str[i] = 0;
    # ifdef DEBUG
        printf("inp: %s\n", str);
    # endif
    return i;
}

// WARNING: modifies passed string
string strrev(string str)
{
    char tmp;
    size_t i, len = strlen(str);
    for (i = 0; i < len / 2; i++) {
        tmp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = tmp;
    }
    return str;
}

int main()
{
    int len;
    char str[MAX_SZ] = "";
    printf("enter string length: ");
    scanf("%u", &len);
    printf("enter string of length %u: ", len);
    strnin(str, len);
    printf("strrev(str) = %s\n", strrev(str));
    return 0;
}
