#include <stdio.h>
#include <limits.h>
#define MAX 10

int size, coordinate[MAX];  // 紀錄各列的星星所在的行
long long maxPoint, point, grid[MAX][MAX];

int valid(int row, int col) {   // 檢查是否與該列以上的星星衝突
    for (int curRow = 0; curRow < row; curRow++) {
        int curCol = coordinate[curRow];   // 愈被檢查的星星
        if (curCol == col)
            return 0;
        else if ((row + col) == (curRow + curCol))
            return 0;     // 同反對角座標相加相等
        else if ((row - col) == (curRow - curCol))
            return 0;     // 同對角線座標相減相等
    }
    return 1;
}

void star(int row) {
    if (row == size) {  // Base Case
        if (point > maxPoint)
            maxPoint = point;
    } else {
        for (int col = 0; col < size; col++)
            if (valid(row, col)) {
                coordinate[row] = col;
                point += grid[row][col];
                star(row + 1);
                point -= grid[row][col];
                coordinate[row] = -1;
            }
    }   // 若無任何valid，則不再進入 'if > Recursion > Base Case' 故maxPoint不會更新
}

int main() {
    maxPoint = LLONG_MIN; // Find greatest -> Set min;  find smallest -> set max
    scanf("%d", &size);
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            scanf("%lld", &grid[i][j]);
    star(0);
    if (maxPoint == LLONG_MIN)  // max wasn't renew
        printf("no solution\n");
    else
        printf("%lld\n", maxPoint);

    return 0;
}