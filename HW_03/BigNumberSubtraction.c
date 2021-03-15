#include<stdio.h>
#include<string.h>
#define max 100

int main() {
    int lenofA, lenofB, swapTag = 0, minusTag = 0;
    char A[max], B[max];
    memset(A, '0', sizeof(A));
    memset(B, '0', sizeof(B));  
    scanf("%d %s %d %s", &lenofA, A, &lenofB, B);

    if (lenofA < lenofB)            // Swap
        swapTag = 1;
    else if (lenofA == lenofB)
        for (int i = 0; i < lenofA; i++) {
            if (A[i] > B[i])
                break;
            else if (A[i] == B[i])
                continue;
            else
                swapTag = 1;
        }

    if (swapTag == 1) {
        minusTag = 1;
        for (int i = 0; i < lenofB; i++) {
            char tmpC = B[i];
            B[i] = A[i];
            A[i] = tmpC;
        }
        int tmpI = lenofA;
        lenofA = lenofB;
        lenofB = tmpI;
    }

    if (lenofA > lenofB) {          // Shift
        int bias = lenofA - lenofB;
        for (int i = lenofB - 1; i >= 0 ; i--)
            B[i + bias] = B[i];
        for (int i = 0; i < bias; i++)
            B[i] = '0';
    }

    int borrow = 0, ans[max] = {0};
    for (int i = lenofA - 1; i >= 0; i--) {
        int numA = A[i] - '0';
        int numB = B[i] - '0';
        ans[i] = numA - numB - borrow;

        if (ans[i] >= 0)
            borrow = 0;
        else if (ans[i] < 0) {
            ans[i] += 10;
            borrow = 1;
        }
    }

    int nonzeroTag;
    for (int i = 0; i < lenofA; i++) {
        if (ans[i] == 0)
            nonzeroTag = -1;
        else {
            nonzeroTag = i;
            break;
        }
    }

    if (nonzeroTag == -1)
        printf("0");
    else {
        if (minusTag == 1) printf("-");
        for (int i = nonzeroTag; i < lenofA; i++)
            printf("%d", ans[i]);
    }

    return 0;
}