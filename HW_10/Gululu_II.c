#include <stdio.h>
#include <stdlib.h>
#define MAX 1000000000

char rec[MAX];

int main() {
    int length;
    scanf("%d", &length);
    for (int i = 0; i < length; i++) {
        unsigned index;
        scanf("%u", &index);
        rec[(int)index] = '1';
    }
    int T;
    scanf("%d", &T);
    while (T--) {
        int operation;
        unsigned toDelete, toSearch;
        scanf("%d", &operation);
        switch (operation) {
            case 1:
                scanf("%u", &toDelete);
                rec[(int)toDelete] = '0';
                break;
            case 2:
                scanf("%u", &toSearch);
                printf("%s\n", rec[(int)toSearch] == '1' ? "Yes" : "No");
                break;
        }
    }
    return 0;
}