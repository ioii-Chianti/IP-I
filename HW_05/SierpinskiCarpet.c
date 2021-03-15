#include <stdio.h>
#include <math.h>
#define MAX 2200   // 3^7 = 2187

int carpet[MAX][MAX] = {0};

void fill(int n, int x, int y) {   // 範圍的指數和大正頂點
    if (n == 1)     // 指數1 = 邊長3；只需填滿中間一格
        carpet[x][y] = 1;
    else {
        int range_0 = pow(3, n);     // 欲處理的範圍
        int side_1 = pow(3, n - 1);  // 大正邊長
        int bias = pow(3, n - 2) * 2;  // 大正頂點到小正頂點的位移量
        if (carpet[x][y] != 1)      // 填小正時避開大正
            for (int i = x; i < x + side_1; i++)
                for (int j = y; j < y + side_1; j++)
                    carpet[i][j] = 1;     // 填滿從頂點到邊長的範圍
        
        for (int i = 0; i < range_0; i += side_1)   // 用ij改變左上小正座標得到周圍八個小正的座標
            for (int j = 0; j < range_0; j += side_1)
                fill(n - 1, x - bias + i, y - bias + j);    // 傳入縮小的範圍和九個小正的座標
    }
}

int main() {
    int N, X, Y, LEN;
    scanf("%d", &N);
    X = pow(3, N - 1);  // 大正頂點X座標
    Y = pow(3, N - 1);  // 大正頂點Y座標
    LEN = pow(3, N);    // 地毯總邊長
    fill(N, X, Y);

    for (int i = 0; i < LEN; i++) {
        for (int j = 0; j < LEN; j++)
            if (carpet[i][j] == 0)
                printf(".");
            else
                printf("#");
        printf("\n");
    }

    return 0;
}