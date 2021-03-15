#include <stdio.h>

int main(){
    int N, X, Y, Z, both, csOnly;
    scanf("%d %d %d %d", &N, &X, &Y, &Z);
    both = X + Y + Z - N;
    csOnly = X - both;
    printf("%d %d", both, csOnly);

    return 0;
}
