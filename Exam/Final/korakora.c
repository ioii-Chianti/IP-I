#include <stdio.h>
#include <stdlib.h>
#define MAX 100005

long long arr[MAX];

typedef struct _Node {
    struct _Node *prev, *next;
    long long val;
} Node;

Node* newNode(long long val) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->prev = node->next = NULL;
    node->val = val;
    return node;
}

int cmp(const void *arg1, const void *arg2) {
    long long x = *(long long *)arg1;
    long long y = *(long long *)arg2;
    if (x > y) return 1;
    if (x == y) return 0;
    return -1;
}

int main() {
    int N;
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
        scanf("%lld", &arr[i]);
    qsort(arr + 1 , N, sizeof(long long), cmp);  // start from arr[1]

    Node *head = newNode(arr[-1]);
    Node *cur = head, *mid;
    for (int i = 1; i <= N; i++) {
        cur->next = newNode(arr[i]);
        cur->next->prev = cur;
        cur = cur->next;
        if (i == (N + 1) / 2)
            mid = cur;
    }

    int T, cntDivide = 0;
    scanf("%d", &T);
    while (T--) {
        int operation, k;
        scanf("%d", &operation);
        switch (operation) {
            case 1:
                mid = mid->prev;
                mid->next = mid->next->next;
                mid->next->prev = mid;
                N--;
                if (N % 2)
                    mid = mid->next;
                break;
            case 2:
                scanf("%d", &k);
                long long ans = 0;
                if (cntDivide < 60) {
                    cur = head->next;
                    for (int i = 1; i <= N; i++) {
                        if (i == k)
                            ans = cur->val;
                        cur->val /= 2ll;
                        cur = cur->next;
                    }
                }
                printf("%lld\n", ans);
                cntDivide++;
                break;
        }
    }
    return 0;
}