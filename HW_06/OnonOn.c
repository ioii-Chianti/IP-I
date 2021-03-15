#include <stdio.h>
#include <limits.h>
#define MAX 20

int ROW, COL, grid[MAX][MAX], minCnt;

void click(int r, int c) {
    grid[r][c] = !grid[r][c];
    if (r > 0)
        grid[r - 1][c] = !grid[r - 1][c];
    if (r < ROW - 1)
        grid[r + 1][c] = !grid[r + 1][c];
    if (c > 0)
        grid[r][c - 1] = !grid[r][c - 1];
    if (c < COL - 1)
        grid[r][c + 1] = !grid[r][c + 1];
}

void sol(int row, int col, int cnt) {
    if (col == COL) {
        row++;
        col = 0;
    }   // change line

    if (row == 0) {   /* 跑出按或不按的所有可能 */
        click(row, col);   // if click, go next and cnt++
        sol(row, col + 1, cnt + 1);
        click(row, col);   // 2k clicks = no click
        sol(row, col + 1, cnt);
    } else if (row < ROW) {
        if (!grid[row - 1][col]) {
            click(row, col);
            sol(row, col + 1, cnt + 1);
            click(row, col);   // 找最佳解的還原
        } else {
            sol(row, col + 1, cnt);
        }
    } else {
        for (int i = 0; i < COL; i++) {
            if (!grid[ROW - 1][i])
                return;
        }
        if (cnt < minCnt)
            minCnt = cnt;
    }
}

int main() {
    minCnt = INT_MAX;
    scanf("%d %d", &ROW, &COL);
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            scanf("%d", &grid[i][j]);

    sol(0, 0, 0);   // 傳入座標和計數器
    if (minCnt == INT_MAX)
        printf("no solution\n");
    else
        printf("%d\n", minCnt);

    return 0;
}