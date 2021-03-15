#include <stdio.h>
#include <string.h>

void rotate(int (*arr)[4]) {
    int result[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            result[j][3 - i] = arr[i][j];
    memcpy(arr, result, sizeof(result));
    return;
}   // clockwise rotation *1

void moveUp(int (*arr)[4]) {
    int pre[4] = {1, 1, 1, 1};  // 紀錄下一回合要檢查過的位置
    for (int i = 1; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            if (arr[i][j]) {
                if (arr[pre[j] - 1][j] == 0) {   // 頭上還有0
                    arr[pre[j] - 1][j] = arr[i][j];
                    arr[i][j] = 0;
                    pre[j]--;
                } else if (arr[pre[j] - 1][j] == arr[i][j]) {   // 上面一樣就*2
                    arr[pre[j] - 1][j] *= 2;
                    arr[i][j] = 0;
                } else if (pre[j] != i) {
                    arr[pre[j]][j] = arr[i][j];
                    arr[i][j] = 0;
                }
                pre[j]++;
            }
        for (int k = 0; k < 4;k++) {
            for (int l = 0; l < 4; l++)
                printf("%d ", arr[k][l]);
            printf("\n");
        }
    }
    return;
}

int main() {
    int dir[4] = {0, 2, 3, 1};   // How many times of rotation for each direction
    int grid[4][4], ans[4][4];

    while (scanf("%d%d%d%d", &grid[0][0], &grid[0][1], &grid[0][2], &grid[0][3]) != EOF) {
        for (int i = 1; i < 4;i++)
            for (int j = 0; j < 4; j++)
                scanf("%d", &grid[i][j]);

        for (int d = 0; d < 4; d++) {
            memcpy(ans, grid, sizeof(grid));    // copy grid to ans
            for (int i = dir[d]; i < 4; i++)    // 轉到能變成往上移
                rotate(ans);
            moveUp(ans);
            for (int i = 0; i < dir[d]; i++)    // 轉回來
                rotate(ans);

            int same = 1;
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    if (grid[i][j] != ans[i][j])
                        same = 0;
            // if (same)
            //     printf("Invalid\n");
            // else
            //     for (int i = 0; i < 4; i++)
            //         for (int j = 0; j < 4; j++)
            //             printf("%d%c", ans[i][j], j == 3 ? '\n' : ' ');
        }
    }
    return 0;
}