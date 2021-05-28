#include <stdio.h>
#include <string.h>
#define SIZE 1011

int place(char *ans, int cur, int val) {
    char temp[10];
    int digit = 0;
    while (val > 0) {
        temp[digit++] = (char)(val % 10 + '0');
        val /= 10;
    }
    for (int i = digit - 1; i >= 0; i--)
        ans[cur++] = temp[i];
    return cur;
}

int main() {
    char str[SIZE], ans[SIZE * 4];
    memset(str, '\0', sizeof(str));
    scanf("%s", str);
    char pre = str[0];
    int len = strlen(str), cur = 0, cnt = 0;

    for (int i = 0; i <= len; i++) {
        char ch = str[i];
        if (ch == pre)
            cnt++;
        else {
            if ('0' <= pre && pre <= '9') {
                if (cnt > 1)
                    cur = place(ans, cur, cnt);
                ans[cur++] = '\'';
                ans[cur++] = pre;
                ans[cur++] = '\'';
            } else {
                if (cnt < 3)
                    while (cnt--)
                        ans[cur++] = pre;
                else {
                    cur = place(ans, cur, cnt);
                    ans[cur++] = pre;
                }
            }
            pre = ch, cnt = 1;
        }
    }
    ans[cur] = '\0';
    printf("%s\n", ans);
    double rate = (double)cur / len;
    if (rate < 1)
        printf("Compress rate: %.3f\n", rate);
    else
		printf("The string can't zip\n");
    return 0;
}