#include <stdio.h>
#define SIZE 25

int N, M;
int seq[SIZE] = {0}, step[SIZE] = {0};   // Store the index of seq

void combine(int curStep, int start) {
    if (curStep == M) {
        for (int i = 0; i < M; i++) {
            printf("%d", seq[step[i]]);
            if (i != M - 1)
                printf(" ");
        } printf("\n");
    } else
        for (int i = start; i < N; i++) {
            step[curStep] = i;
            combine(curStep + 1, i + 1);
        }
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++)
        scanf("%d", &seq[i]);
    combine(0, 0);

    return 0;
}

