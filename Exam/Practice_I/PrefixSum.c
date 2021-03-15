#include <stdio.h>
#define MAX 1000000

long long element[MAX] = {0};
long long prefixSum[MAX] = {0};
int main() {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%lld", &element[i]);
        if (i == 0)
            prefixSum[i] = element[i];
        else
            prefixSum[i] = prefixSum[i - 1] + element[i];
    }

    int M;
    long long ans;
    scanf("%d", &M);
    for (int i = 1; i <= M; i++) {
        int L, R;
        scanf("%d %d", &L, &R);
        ans = prefixSum[R - 1] - prefixSum[L - 2];
        printf("%lld\n", ans);
    }
    return 0;
}
