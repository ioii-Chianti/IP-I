#include <stdio.h>

int main() {
    int n, pivot = 1;
    scanf("%d", &n);
    int map[500][500];

    /* 迴圈變數只考慮該方向的範圍，另外的列或行用R表示，其中方向是層數的函數 */

    for (int T = 0; T < n; T++) {
        for (int r = T; r < 2 * n - 1 - T; r++)
            map[T][r] = pivot++;
        for (int d = T; d < 2 * n - 1 - T; d++)
            map[d][2 * n - 1 - T] = pivot++;
        for (int l = 2 * n - 1 - T; l > T; l--)
            map[2 * n - 1 - T][l] = pivot++;
        for (int u = 2 * n - 1 - T; u > T; u--)
            map[u][T] = pivot++;
    }

    for(int row = 0; row < 2 * n; row++) {
        for (int col = 0; col < 2 * n; col++) {
        printf("%d", map[row][col]);
        if (col != 2 * n - 1) printf(" ");
        } printf("\n");
    }

    return 0;
}