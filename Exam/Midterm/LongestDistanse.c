#include <stdio.h>
#include <string.h>
#define max(a, b) ((a) > (b) ? a : b)

char binary[65];
int toBinary(long long num) {
    memset(binary, '\0', sizeof(binary));
    if (num == 0)
        binary[0] = '0';
    else {
        int p = 0;
        while (num) {
            binary[p++] = num % 2 + '0';
            num /= 2;
        }
    } return strlen(binary);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long num;
        scanf("%lld", &num);

        int len = toBinary(num), curDis = 0, longDis = -1, allone = 1, start = 0;
        for (int i = 0; i < len; i++) {
            if (allone && binary[i] == '0')
                allone = 0;
            if (binary[i] == '0' && start)
                curDis++;
            else {
                if (start) {
                    longDis = max(longDis, curDis);
                    curDis = 0;
                } else start = 1;
            }
        } printf("%d\n", allone ? 0 : longDis);
    }
    return 0;
}