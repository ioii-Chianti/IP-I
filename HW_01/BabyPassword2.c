/**/

#include <stdio.h>

int main()
{
    char origin, actual;
    int shift;
    scanf("%c %d", &actual, &shift);

    if (actual >= 'A' && actual <='Z')
    {
        actual += 32;
        actual = actual - 'a' + 26;
        origin = (actual - shift) % 26 + 'a';
    }
    else
    {
        actual -= 32;
        actual = actual - 'A' + 26;
        origin = (actual - shift) % 26 + 'A';
    }
    printf("%c\n", origin);

    return 0;
}
