#include <stdio.h>
#include <string.h>
#define MAX 500000

typedef struct {
    int around[4];
    long long value;
} Point;

int cur_step, portal; // 當前位置和傳送點在record中的編號
Point record[MAX];
void fuck();

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int operation, dir;
        long long new_val;
        scanf("%d", &operation);
        switch (operation) {
            case 1:
                scanf("%d", &dir);
                scanf("%lld", &new_val);
                int new_index = cur_step + dir + 1;
                record[new_index].value = new_val;
                record[new_index].around[(dir + 2) % 4] = cur_step;
                record[cur_step].around[dir] = new_index;
                // fuck();
                break;
            case 2:
                scanf("%d", &dir);
                cur_step = record[cur_step].around[dir];
                // fuck();
                break;
            case 3:
                scanf("%lld", &new_val);
                record[cur_step].value = new_val;
                // fuck();
                break;
            case 4:
                printf("%lld\n", record[cur_step].value);
                // fuck();
                break;
            case 5:
                portal = cur_step;
                // fuck();
                break;
            case 6:
                cur_step = portal;
                // fuck();
                break;
        }
    } return 0;
}

void fuck() {
    printf("----- BUG -----\n");
    printf("Current value: %lld\n", record[cur_step].value);
    printf("Portal: %d\n", portal);
    for (int i = 0; i < 4; i++)
        printf("Current around[%d]: %d\n", i, record[cur_step].around[i]);
    printf("----- END -----\n\n");
 
    return;
}