#include <stdio.h>
#include <string.h>
#define MAX 100

int main() {
    char integer[MAX];
    memset(integer, '\0', sizeof(integer));
    scanf("%s", integer);
    int length = strlen(integer);   // strlen不會計算'\0'，無論是字串結尾或是初始化值

    int nonsenseTag = 0;
    for (int i = 0; i < length; i++) {
        if (integer[i] == '2' || integer[i] == '3' || integer[i] == '4' || integer[i] == '5' || integer[i] == '7') {
            nonsenseTag = 1;
            break;
        }
        else if (integer[i] == '6')
            integer[i] = '9';
        else if (integer[i] == '9')
            integer[i] = '6';
    }

    if (nonsenseTag == 1)
        printf("No\n");
    else {
        int nonzeroTag = -1;    // 由後往前找第一個非0位置
        for (int i = length - 1; i >= 0; i--)
            if (integer[i] != '0') {
                nonzeroTag = i;
                break;
            }

        if (nonzeroTag == -1)
            printf("0");    // 全為0只需輸出一個0
        else {
            for (int i = nonzeroTag; i >= 0; i--)
                printf("%c", integer[i]);
            printf("\n");   // 由找到的非0位置開始輸出
        }
    }   return 0;
}