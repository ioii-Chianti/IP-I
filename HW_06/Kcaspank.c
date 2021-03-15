#include <stdio.h>
#define MAXN 20

int weight[MAXN];
unsigned long value[MAXN];

unsigned long max(unsigned long a, unsigned long b) {
    return (a > b) ? a : b;
}

unsigned long knapsack(int rem_N, int rem_W) {
    // Base Case: 沒有剩餘物品或負重
    if (rem_N == 0 || rem_W == 0)
        return 0;   // Terminal Statement!

    // 若最後一個物品重量大於當前剩餘負重則跳過
    if (weight[rem_N - 1] > rem_W)
        return knapsack(rem_N - 1, rem_W);
    else
        return max(
            value[rem_N - 1] + knapsack(rem_N - 1, rem_W - weight[rem_N - 1]),
            knapsack(rem_N - 1, rem_W));
}   // 考慮取最後一個或不取哪個值比較大

int main() {
    int num, maxWeight;
    scanf("%d %d", &num, &maxWeight);
    for (int i = 0; i < num; i++)
        scanf("%d %lu", &weight[i], &value[i]);
    printf("%lu\n", knapsack(num, maxWeight));

    return 0;
}