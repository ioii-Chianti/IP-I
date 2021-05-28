#include <stdio.h>
#include <string.h>
#define MAX 20

int K, P1win;
int permuted[MAX], isChosen[MAX];

int canWin(int *arr, int len) {
    int prefix[MAX] = {};
    prefix[0] = arr[0];
    for (int i = 1; i < len; i++) {
        prefix[i] = prefix[i - 1] + arr[i];
        if (prefix[i] >= K) {
            if (i % 2 == 0)
                return 1;
            else
                return 0;
        }
    }
    // for (int i = 0; i < len; i++)
    //     printf("%d ", prefix[i]);
}

void permutation(int curIndex, int n) {
    if (P1win)
        return;
    if (curIndex == n) {
        for (int i = 0; i < n; i++)
            printf("%d ", permuted[i]);
        printf("\n");
        P1win = canWin(permuted, n);
    } else {
        for (int i = 1; i <= n; i++) {
            if (isChosen[i])
                continue;
            isChosen[i] = 1;
            permuted[curIndex] = i;
            

            permutation(curIndex + 1, n);
            isChosen[i] = 0;
        }
    }
    return;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        P1win = 0;
        int N;
        scanf("%d %d", &N, &K);
        permutation(0, N);
        printf("%s\n", P1win ? "True" : "False");
    }
    return 0;
}