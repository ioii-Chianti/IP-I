#include <stdio.h>
#define MAX 60000

int type[MAX];

int main() {
    int n;
    scanf("%d", &n);
    char str[15];
    for (int i = 0; i < n; i++) {
        scanf("%s", str);
        int ternary = 0;
        for (int j = 0; j < 10; j++) {
            int curNum = (str[j] == 'x' ? 2 : str[j] - '0');   
            ternary = ternary * 3 + curNum;
        }
        type[ternary] = 1;
    }
    int cnt = 0;
    for (int i = 0; i < 60000; i++)
        cnt += type[i];
    printf("%d\n", cnt);
    return 0;
}