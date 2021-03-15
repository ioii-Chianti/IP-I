#include <stdio.h>
#define MAX 10

int permuted[MAX], isChosen[MAX];

void permutation(int curIndex, int n) {
    if (curIndex == n) {
        for (int i = 0; i < n; i++)
            printf("%d ", permuted[i]);
        printf("\n");
    } else {
        for (int i = 1; i <= n; i++) {
            if (isChosen[i])
                continue;
            isChosen[i] = 1;
            permuted[curIndex] = i;
            permutation(curIndex + 1, n);
            isChosen[i] = 0;    // DFS
        }
    }
}

int main() {
    int N;
    scanf("%d", &N);
    permutation(0, N);

    return 0;
}