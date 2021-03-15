#include<stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    unsigned long long walk[200] = {0};
    for (int i = 0; i < 3; i++)
        walk[i] = 1;

    for (int i = 3; i <= N; i++)
       walk[i] = walk[i - 3] + walk[i - 1];
    printf("%llu\n", walk[N]);

    return 0;
}