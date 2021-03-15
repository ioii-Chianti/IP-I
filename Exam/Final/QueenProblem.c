#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#define MAX 15

int N;
long long grid[MAX][MAX], MaxPoint, SecPoint;
int col[MAX], diag[MAX * 2 + 1], antidiag[MAX * 2 + 1];

void queen(int index, long long point) {
    for (int i = 0; i < N; i++) {
        if (!col[i] && !diag[index + i] && !antidiag[index - i + MAX]) {
            col[i] = diag[index + i] = antidiag[index - i + MAX] = 1;
            if(index != N-1)
                queen(index + 1, point + grid[index][i]);
            else {
                long long res = point + grid[index][i];
                if (res != MaxPoint && res != SecPoint) {
                    if (res > MaxPoint) {
                        SecPoint = MaxPoint;
                        MaxPoint = res;
                    } else if (res > SecPoint)
                        SecPoint = res;
                }
            }
            col[i] = diag[index + i] = antidiag[index - i + MAX] = 0;
        }
    }
}

int main() {
    MaxPoint = SecPoint = LLONG_MIN;
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%lld", &grid[i][j]);

    queen(0, 0);
    if (SecPoint == LLONG_MIN)
        printf("Invalid\n");
    else
        printf("%lld\n", SecPoint);

    return 0;
}
