#include<stdio.h>

int main(){
    int A, B, A1, A2, A3, B1, B2, remainder;
    scanf("%d %d", &A, &B);

    A1 = A / 100;
    remainder = A % 100;
    A2 = remainder / 10;
    remainder %= 10;
    A3 = remainder;

    B1 = B / 10;
    B2 = B % 10;

    //

    float sumA, sumB, answer;
    sumA = A1 + A2 + A3;
    sumB = B1 + B2;
    answer = sumA / sumB;
    printf("result:%6.2f\n", answer);

    return 0;
}
