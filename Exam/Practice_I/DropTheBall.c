#include <stdio.h>
#include <string.h>
#define MAX 520

int main() {
    int ROW, COL;
    char map[MAX][MAX];
    memset(map, '\0', sizeof(map));
    scanf("%d %d\n", &ROW, &COL);   // 有'\n'才不會把確認放進字元陣列
    for (int i = 0; i < ROW; i++)
        scanf("%s", &map[i][0]);    // 每行輸入字串

    int Q;
    scanf("%d", &Q);
    while (Q--) {   // 次數迴圈最佳表示法
        int col, flagL = 0, flagR = 0, flagS = 0;   // 3種特殊狀況之Flag
        scanf("%d", &col);
        --col;   // 起始欄轉陣列編號

        /* 球每次往下一列，並在每一列中討論兩種方向及各方向的三種狀況 */
        for (int row = 0; row < ROW; row++) {
            if (map[row][col] == '/') {
                if (col - 1 < 0) {
                    flagL = 1;
                    break;
                } else if (map[row][col - 1] == '\\') {
                    flagS = 1;
                    break;
                } else
                    col--;
            }
            else if (map[row][col] == '\\') {
                if (col + 1 >= COL) {
                    flagR = 1;
                    break;
                } else if (map[row][col + 1] == '/') {
                    flagS = 1;
                    break;
                } else
                    col++;
            }
        }
        if (flagL == 1)
            printf("Left!\n");
        else if (flagR == 1)
            printf("Right!\n");
        else if (flagS == 1)
            printf("Stuck QQ\n");
        else
            printf("Position: %d\n", col + 1);   // 編號值轉欄數
    }
    
    return 0;
}