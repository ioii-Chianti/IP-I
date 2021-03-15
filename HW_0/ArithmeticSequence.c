#include <stdio.h>

int main(){
    int a, n, d, an, sum;
    scanf("%d %d %d", &a, &n, &d);
    an = a + (n - 1) * d;
    sum = n * (a + an) / 2;
    printf("%d %d", an, sum);

    return 0;
}