#include <stdio.h>
#include <stdlib.h>
#define MAX 2000
#define max(a, b) ((a) > (b) ? (a) : (b))

int num_member[MAX], isChosen[MAX];
long long Maximum[MAX], Sum[MAX], *banana[MAX];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int num_group;
        scanf("%d", &num_group);
        
        for (int i = 0; i < num_group; i++) {   //各組初始化
            Maximum[i] = Sum[i] = isChosen[i] = 0;
            scanf("%d", &num_member[i]);

            banana[i] = (long long *)malloc(num_member[i] * sizeof(long long));
            for (int j = 0; j < num_member[i]; j++) {
                scanf("%lld", &banana[i][j]);
                Sum[i] += banana[i][j];
                Maximum[i] = max(Maximum[i], banana[i][j]);
            }   // 輸入時同時計算加總和最大值
        }

        int O = 0, order[MAX] = {};
        for (int i = 0; i < num_group; i++) {   //填滿order的迴圈
            int curIndex = -1;
            for (int j = 0; j < num_group; j++) {   //找當前最優先
                if (isChosen[j])     // 當前組別是否用過
                    continue;
                if (curIndex == -1)     // 找到第一個沒被用過的組別
                    curIndex = j;
                else if (Sum[j] > Sum[curIndex])        // 依照優先條件找最優先的組別 : 加總最高 > 單體最高 > 人數
                    curIndex = j;
                else if (Sum[j] == Sum[curIndex] && Maximum[j] > Maximum[curIndex])
                    curIndex = j;
                else if (Sum[j] == Sum[curIndex] && Maximum[j] == Maximum[curIndex] && num_member[j] > num_member[curIndex])
                    curIndex = j;
            }
            isChosen[curIndex] = 1;
            order[O++] = curIndex;
        }   // 跑完全部組別後得出最優先的組 放進order並設成拿過

        for (int i = 0; i < num_group; i++)
            for (int j = 0; j < num_member[order[i]]; j++)
                printf("%lld%c", banana[order[i]][j], j == num_member[order[i]] - 1 ? '\n' : ' ');

        for (int i = 0; i < num_group; i++)
            free(banana[i]);
    }
    return 0;
}