#include <stdio.h>
#define MAXLEN 100001
#define MAXELE 10001

int main() {
    int N, seq[MAXLEN] = {0};
    unsigned long long counter[MAXELE] = {0};
    scanf("%d", &N);   // 數列長度及數列
    for (int i = 0; i < N; i++) {
        scanf("%d", &seq[i]);
        counter[seq[i]]++;   // 陣列元素計數器
    }

    unsigned long long ans = 0;
    for (int i = 0; i < MAXELE; i++)   // 檢查計數器的元素
        if (counter[i] != 0 && counter[i] != 1)   // 每個非0和1的元素的累加
            for (int j = counter[i] - 1; j > 0; j--)
                ans += j;
                
    printf("%llu\n", ans);

    return 0;
}