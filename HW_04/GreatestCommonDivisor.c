#include <stdio.h>

int gcd(int x, int y) {
    if (y == 0)
        return x;
    else
        return gcd(y, x % y);
}
int main() {
    int numA, numB;
    scanf("%d %d", &numA, &numB);
    printf("%d\n", gcd(numA, numB));

    return 0;
}