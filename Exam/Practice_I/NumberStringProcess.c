#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1011

int main() {
    int length;
    char str[MAX];
    memset(str, '\0', sizeof(str));
    scanf("%d %s", &length, str);

    int Q;
    scanf("%d", &Q);
    while (Q--) {
        int a, b, sz;
        long long numA, numB;
        char A[MAX], B[MAX];
        memset(A, '\0', sizeof(A));
        memset(B, '\0', sizeof(B));
        scanf("%d %d %d", &a, &b, &sz);    // 取得A和B
        for (int k = a, p = 0; k < a + sz; k++, p++)
            A[p] = str[k];
        for (int k = b, p = 0; k < b + sz; k++, p++)
            B[p] = str[k];

        for (int k = a; k < length; k++)   // 更新原陣列
            str[k] = str[k + sz];
        length -= sz;
        for (int k = b - sz; k < length; k++)
            str[k] = str[k + sz];
        length -= sz;

        numA = atoll(A);
        numB = atoll(B);
        printf("%lld\n", numA * numB);
    }
        return 0;
}