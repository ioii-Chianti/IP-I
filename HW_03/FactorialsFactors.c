#include <stdio.h>

int main() {
    int n, factor[1000] = {0};
    scanf("%d", &n);

    for (int i = n; i > 1; i--){
        int current = i;
        for (int fac = 2; current > 1; fac++)
            while (current % fac == 0) {
                factor[fac]++;
                current /= fac; // update
            }
    }

    unsigned long cnt = 1;
    for (int i = 0; i < 1000; i++)
        cnt *= factor[i] + 1;
    printf("%lu", cnt);

    return 0;
}