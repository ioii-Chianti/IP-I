#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "function.h"

long long arr[500][500] = {};

void swap(long long *x, long long *y) {
    long long temp = *x;
    *x = *y;
    *y = temp;
}

void sort(long long *arr, int len) {
    for (int i = 0; i < len; i++)
        for (int j = 0; j < len - 1 - i; j++)
            if (*(arr + j) > *(arr + j + 1))
                swap(&*(arr + j), &*(arr + j + 1));
}

void array2d_sort(int row, int col, long long arr[][500]) {
    // upper triangle
    for (int k = 0; k < col; k++) {
        long long toSort[500] = {};
        int x = 0, y = k, p = 0;
        while (x < row && y < col)
            toSort[p++] = arr[x++][y++];
        sort(toSort, p);

        x = 0, y = k, p = 0;
        while (x < row && y < col)
            arr[x++][y++] = toSort[p++];
    }

    // lower triangle
    for (int k = 0; k < row; k++) {
        long long toSort[500] = {};
        int x = k, y = 0, p = 0;
        while (x < row && y < col)
            toSort[p++] = arr[x++][y++];
        sort(toSort, p);

        x = k, y = 0, p = 0;
        while (x < row && y < col)
            arr[x++][y++] = toSort[p++];
    }
}

int main(void){

    int row, col;
    scanf("%d%d", &row, &col);

    for(int i = 0; i < row; ++i)
        for(int j = 0; j < col; ++j)
            scanf("%lld", &arr[i][j]);

    array2d_sort(row, col, arr);

    for(int i = 0; i < row; ++i)
        for(int j = 0; j < col; ++j)
            printf("%lld%c", arr[i][j], (j == col - 1) ? '\n' : ' ');

    return 0;
}