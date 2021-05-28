#include <stdio.h>

int cnt[20000];	// around 3^9

int encoding(char board[][5]) {
    int ret = 0;
    for(int i=0;i<3;i++)
        for (int j = 0; j < 3; j++)
            ret = (ret * 3) + (board[i][j] == 'x' ? 2 : board[i][j] - '0');
    return ret;
}
void swap(char *a,char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}
int sol(int curstep, int K, char board[][5], int x, int y) {
    int ret = 0, enc = encoding(board);
    ret += cnt[enc], cnt[enc] = 0;
    if(curstep == K)
        return ret;
    static int dx[] = {-1, 0, 0, 1}, dy[] = {0, -1, 1, 0};
    for (int dir = 0; dir < 4; dir++) {
        int nx = x + dx[dir], ny = y + dy[dir];
        if(nx < 0 || nx >= 3 || ny < 0 || ny >= 3)
            continue;
        swap(&board[x][y], &board[nx][ny]);
        ret += sol(curstep + 1, K, board, nx, ny);
        swap(&board[x][y], &board[nx][ny]);
    }
    return ret;
}
int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    char board[3][5];
    for (int i = 0; i < N + 1; i++) {
        for(int j=0;j<3;j++)
            scanf("%s", board[j]);
        cnt[encoding(board)]++;   // 當前的A的編碼放進一計數陣列
    }
    int sx, sy;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == 'x')
                sx = i, sy = j;
    printf("%d\n", sol(0, K, board, sx, sy));
    return 0;
}