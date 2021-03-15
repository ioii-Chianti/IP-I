#include <stdio.h>
#define MAX 100
#define max(a, b) ((a) > (b) ? a : b)

int thief(int *value, int len) {
    int dp[MAX];
    dp[0] = value[0];
    dp[1] = max(dp[0], value[1]);
    for (int i = 2; i < len; i++)
        dp[i] = max(value[i] + dp[i - 2], dp[i - 1]);

    return dp[len - 1];
}

int main() {
    int N, value[MAX], stolen[MAX];
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", value + i);
        stolen[i] = 0;
    }
    
    printf("%d ", thief(value, N));

    return 0;
}
