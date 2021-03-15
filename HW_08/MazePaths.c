#include <stdio.h>
#include <string.h>
#include <limits.h>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define MAX 101

int ROW, COL, cnt, minStep;
char maze[MAX][MAX];

void path(int row, int col, int curStep) {
    if (maze[row][col] == 'F') {
        cnt++;
        minStep = min(curStep, minStep);
    } else {
        maze[row][col] = '#';
        if (row > 0 && maze[row - 1][col] != '#')
            path(row - 1, col, curStep + 1);
        if (row < ROW - 1 && maze[row + 1][col] != '#')
            path(row + 1, col, curStep + 1);
        if (col > 0 && maze[row][col - 1] != '#')
            path(row, col - 1, curStep + 1);
        if (col < COL - 1 && maze[row][col + 1] != '#')
            path(row, col + 1, curStep + 1);
        maze[row][col] = '$';
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        cnt = 0;
        minStep = INT_MAX;
        memset(maze, '0', sizeof(maze));

        int Sx, Sy;
        scanf("%d %d\n", &ROW, &COL);
        for (int i = 0; i < ROW; i++) {
            scanf("%s", maze + i);
            for (int j = 0; j < COL; j++)
                if (maze[i][j] == 'S') {
                    Sx = i;
                    Sy = j;
                }
        }
        path(Sx, Sy, 0);
        if (minStep == INT_MAX)
            printf("%d %d\n", 0, -1);
        else
            printf("%d %d\n", cnt, minStep);
    }

    return 0;
}