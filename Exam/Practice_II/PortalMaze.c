#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 310

int ROW, COL, start_x, start_y, TP_x[30], TP_y[30];
int visited[MAX][MAX];
char maze[MAX][MAX];

int path(int x, int y) {
    static int dx[4] = {-1, 1, 0, 1}, dy[4] = {0, 0, -1, 1};
    visited[x][y] = 1;
/*  
    printf("%d %d\n", x, y);
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            printf("%d%c", visited[i][j], j == COL - 1 ? '\n' : ' ');
    printf("\n");
*/
    if (maze[x][y] == '&')
        return 1;
    for (int vec = 0; vec < 4; vec++) {
        int nxt_x = x + dx[vec];
        int nxt_y = y + dy[vec];

        if (nxt_x < 0 || nxt_x >= ROW || nxt_y < 0 || nxt_y >= COL)
            continue;
        if (islower(maze[nxt_x][nxt_y])) {
            char next = maze[nxt_x][nxt_y];
            nxt_x = TP_x[next - 'a'];
            nxt_y = TP_y[next - 'a'];
        }
        if (visited[nxt_x][nxt_y] || maze[nxt_x][nxt_y] == '#')
            continue;   //已走過小寫，則大寫vis = 1，故可判斷走過傳送門

        if (path(nxt_x, nxt_y))
            return 1;   // 找到終點不斷回傳1(第一次在line21)回到最外層
    }
    return 0;  // 走到死路會cont出for迴圈之後回傳0，不斷回傳0回到最外層
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d\n", &ROW, &COL);
        memset(visited, 0, sizeof(visited));

        for (int i = 0; i < ROW; i++) {
            scanf("%s", maze[i]);
            for (int j = 0; j < COL; j++) {
                if (maze[i][j] == '$')
                    start_x = i, start_y = j;
                if (isupper(maze[i][j])) {
                    TP_x[maze[i][j] - 'A'] = i;
                    TP_y[maze[i][j] - 'A'] = j;
                }
            }
        } printf("%s\n", path(start_x, start_y) ? "Yes" : "No");
    } return 0;
}