#include<stdio.h>
#include<stdlib.h>
// #include "function.h"
#define maxn 100005

int arr[maxn];
int cmp(const void *a, const void *b) {
    return *(int *)a < *(int *)b ? 1 : 0;
}

int main() {
	int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);
    qsort(arr + 1, n, sizeof(int), cmp);    // 起始位置、幾個元素、元素大小、比較函數
    for (int i = 1; i <= n; i++) {
        if(i != 1)
            printf(" ");
        printf("%d", arr[i]);
    }
    printf("\n");
    return 0;
}

