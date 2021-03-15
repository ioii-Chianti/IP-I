#include <stdio.h>
#include <stdlib.h>
// #include "function.h"
#include <math.h>

void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int **s(int *ptr, int len) {
    int **doublePtr = (int **)malloc((int)sqrt(len) * sizeof(int *));

    for (int i = 0; i < len; i++)
        for (int j = 0; j < len - 1 - i; j++) {
            if (*(ptr + j) > *(ptr + j + 1))
                swap(&*(ptr + j), &*(ptr + j + 1));
        }

    for (int i = 0, j = 0; i < (int)sqrt(len); i++, j += (int)sqrt(len))
        doublePtr[i] = &(ptr[j]);
        // doublePtr[i] = ptr + j;

    return doublePtr;
}

int main() {
    int len;
    int **ans;

    scanf("%d", &len);
    int *a = (int *)malloc(len * sizeof(int));

    for (int i = 0; i < len; i++)
        scanf("%d", &a[i]);

    ans = s(a, len);

    for (int i = 0; i < (int)sqrt(len); i++) {
        for (int j = 0; j < (int)sqrt(len); j++)
            printf("%d", ans[i][j]);
        printf("\n");
    }

    free(a);
	return 0;
}
