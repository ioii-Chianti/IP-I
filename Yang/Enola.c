#include<stdio.h>

int main() {
    int n, m;
    char a[1000], b[1000];
    
    while (scanf("%d %d", &n, &m) != EOF) {
        scanf("%s %s", a, b);

        int flag[1000] = {0};
        if (n != m)
            printf("NO\n");
        else {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++)
                    if (a[i] == b[j] && flag[j] == 0) {
                        flag[j] = 1;
                        break;
                    }
            }
            for(int i = 0; i < n; i++)
                if (flag[i] != 1) {
                    printf("NO\n");
                    break;
                }
                else if ( i == n - 1)
                    printf("YES\n");
        }
    }
    
    return 0;
}
