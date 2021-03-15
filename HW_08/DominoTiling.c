#include <stdio.h>

int count(int n) {
    int f[n + 1], g[n + 1];
    f[0] = 1;
    f[1] = 0;
    g[0] = 0;
    g[1] = 1;
    for (int i = 2; i <= n; i++) {
        f[i] = f[i - 2] + 2 * g[i - 1];
        g[i] = f[i - 1] + g[i - 2];
    }
    return f[n];
}

int main() {
    int N;
    scanf("%d", &N);
    printf("%d\n", count(N));

    return 0;
}