#include <stdio.h>
#define MAX 100

int main() {
    int row, col, arr[MAX][MAX] = {0};
    scanf("%d %d", &row, &col);
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            scanf("%d", &arr[i][j]);

    int Q;
    scanf("%d", &Q);
 /* 旋轉矩陣只有四種可能，將新矩陣用原矩陣編號列出後觀察規律印出即可；
    照著由左往右、由上往下的順序，先不動為i、同個i中的變數為j */
    switch (Q % 4) {
    case 0:
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                printf("%d", arr[i][j]);
                if (j != col - 1) printf(" ");
            }
            printf("\n");
        }
        break;
    case 1:
        for (int i = 0; i < col; i++) {
            for (int j = row - 1; j >= 0; j--) {
                printf("%d", arr[j][i]);
                if (j != 0) printf(" ");
            }
            printf("\n");
        }
        break;
    case 2:
        for (int i = row - 1; i >= 0; i--) {
            for (int j = col - 1; j >= 0; j--) {
                printf("%d", arr[i][j]);
                if (j != 0) printf(" ");
            }
            printf("\n");
        }
        break;
    case 3:
        for (int i = col - 1; i >= 0; i--) {
            for (int j = 0; j < row; j++) {
                printf("%d", arr[j][i]);
                if (j != row - 1) printf(" ");
            }
            printf("\n");
        }
        break;
    }
    return 0;
}
