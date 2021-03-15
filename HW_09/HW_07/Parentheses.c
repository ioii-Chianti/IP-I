#include <stdio.h>
#define MAX 105

char parenthese[MAX];

long long calculate(int left, int right) {
    if (right - left == 1)
        return 1;

    long long sum = 0;
    for (int i = left; i < right; i++) {
        if (parenthese[i] == '(') sum++;
        if (parenthese[i] == ')') sum--;
        if (!sum)
            return calculate(left, i) + calculate(i + 1, right);
    }
    return 2 * calculate(left + 1, right - 1);
}

int main() {
    int N;
    scanf("%d", &N);
    getchar();
    gets(parenthese);
    printf("%lld\n", calculate(0, N - 1));
    return 0;
}