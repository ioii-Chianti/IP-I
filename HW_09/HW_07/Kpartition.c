#include <stdio.h>
#define MAX 10

int isPossibleRec(int *seq, int len, int k, int *subset, int subsetSum, int *taken, int curIdx, int limitIdx) {
    if (subset[curIdx] == subsetSum) {
        if (curIdx == k - 2)
            return 1;   // ???
        return isPossibleRec(seq, len, k, subset, subsetSum, taken, curIdx + 1, len - 1);
    }

    for (int i = limitIdx; i >= 0; i--) {
        if (taken[i])
            continue;
        int tmp = subset[curIdx] + seq[i];
        if (tmp <= subsetSum) {
            taken[i] = 1;
            subset[curIdx] += seq[i];
            int nxt = isPossibleRec(seq, len, k, subset, subsetSum, taken, curIdx, i - 1);

            taken[i] = 0;
            subset[curIdx] -= seq[i];
            if (nxt)
                return 1;
        }
    }
    return 0;
}

int isPossible(int *seq, int len, int k) {

    // Cannot be equally divided -> False
    int Sum = 0;
    for (int i = 0; i < len; i++)
        Sum += seq[i];
    if (Sum % k != 0)
        return 0;

    int taken[len], subset[k], subsetSum = Sum / k;
    for (int i = 0; i < len; i++) taken[i] = 0;
    for (int i = 0; i < k; i++) subset[i] = 0;   // initiallize

    subset[0] = seq[len - 1];   // 最後一個元素放進第一個子集
    taken[len - 1] = 1;   // 標記拿過最後一個了

    return isPossibleRec(seq, len, k, subset, subsetSum, taken, 0, len - 1);
}

int main() {
    int q;
    scanf("%d", &q);
    while (q--) {
        int SEQ[MAX], LEN, K;
        scanf("%d %d", &LEN, &K);
        for (int i = 0; i < LEN; i++)
            scanf("%d", &SEQ[i]);

        if (isPossible(SEQ, LEN, K))
            printf("True\n");
        else
            printf("False\n");
    }
    return 0;
}