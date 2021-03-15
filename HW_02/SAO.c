#include <stdio.h>

int main () {
    int n, order[500];
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d", &order[i]);

    int round;
    scanf("%d", &round);
    for (int T = 1; T <= round; T++)
    {       /* 計數器的陣列編號 = 菜單編號，故counter[0]必定為0 */
        int start, end, counter[520] = {0};
        scanf("%d %d", &start, &end);
        for (int i = start - 1; i < end; i++)
            counter[order[i]]++;

        int maxOrder, maxValue = 0;
        for (int j = 1; j < 520; j++) {
            if (counter[j] > maxValue) {
                maxValue = counter[j];
                maxOrder = j;
            }
        } printf("%d\n", maxOrder);
    }

    return 0;
}