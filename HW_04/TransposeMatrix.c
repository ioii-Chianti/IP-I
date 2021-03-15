#include <stdio.h>
#define MAX 1011
int matrix[MAX][MAX] = {0};
int matrixT[MAX][MAX] = {0};
/* Stack Overflow: Declare array as dlobal variable */

int main() {
    int row, col;
    scanf("%d %d", &row, &col);

    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++) {
            scanf("%d", &matrix[i][j]);
            matrixT[j][i] = matrix[i][j];
        }   // Transpose: exchange row and column

    for (int i = 0; i < col; i++) {     // num of row and col should be exchange 
        for (int j = 0; j < row; j++) {
            printf("%d", matrixT[i][j]);
            if (j != row - 1) printf(" ");
        } printf("\n");
    }

    return 0;
}