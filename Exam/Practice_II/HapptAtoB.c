#include <stdio.h>
#include <string.h>
#include <limits.h>
#define SIZE 3

int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
char A[SIZE][SIZE], B[SIZE][SIZE];

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

int happy(int row, int col, int rem_move) {
/*  DFS Tree:
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            printf("%c%c", A[i][j], j == SIZE - 1 ? '\n' : ' ');
*/
    int same = 1;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (A[i][j] != B[i][j])
                same = 0;
    if (same)
        return 1;
    else if (!same && !rem_move)
        return 0;

    for (int vec = 0; vec < 4; vec++) {
        int nxt_r = row + dr[vec];
        int nxt_c = col + dc[vec];

        if (0 <= nxt_r && nxt_r < SIZE && 0 <= nxt_c && nxt_c < SIZE) {
            swap(&A[row][col], &A[nxt_r][nxt_c]);
            if (happy(nxt_r, nxt_c, rem_move - 1))
                return 1;
            swap(&A[row][col], &A[nxt_r][nxt_c]);
        }
    }
    return 0;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int limit;
        scanf("%d\n", &limit);
        memset(A, '\0', sizeof(A));
        memset(B, '\0', sizeof(B));

        for (int i = 0; i < SIZE; i++)
            scanf("%s", A[i]);
        for (int i = 0; i < SIZE; i++)
            scanf("%s", *(B + i));
        
        int start_x, start_y;
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                if (A[i][j] == 'x') {
                    start_x = i;
                    start_y = j;
                }
        printf("%s\n", happy(start_x, start_y, limit) ? "Yes" : "No");
    }

    return 0;
}