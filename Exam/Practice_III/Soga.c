#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    int value;
    struct _Node *left;
    struct _Node *right;
} Node;

Node *head;

Node *newNode(Node *pre, int val) {
    Node *node = (Node *)malloc(sizeof(Node));
    pre->right = node;
    node->value = val;
    node->left = pre;
    node->right = NULL;
    return node;
}

void deleteNode(Node *toDelete) {
    if (toDelete == head) {
        head = head->right;
        head->left = NULL;
    } else {
        Node *Left = toDelete->left, *Right = toDelete->right;
        Left->right = Right;
        Right->left = Left;
    } free(toDelete);
}

void traversal(Node *head) {
    Node *cur = head;
    while (cur) {
        printf("%d ", cur->value);
        cur = cur->right;
    } printf("\n");
}

int main() {
    int N, T;
    scanf("%d", &N);

    Node *previous, *current, *mid;
    int rightFlag = 0;
    for (int i = 0; i < N; i++) {
        int value;
        if (!i) {
            head = (Node *)malloc(sizeof(Node));
            scanf("%d", &(head->value));
            head->left = NULL;
            previous = head;
        } else {
            scanf("%d", &value);
            current = newNode(previous, value);
            previous = current;
            current = current->right;
        }
        if (i == (N-1)/2) {
            mid = previous;
            if ((N-1) % 2) rightFlag = 1;
        }
    }
    // traversal(head);
    Node *happy = head, *toDelete;
    scanf("%d", &T);
    while (T--) {
        int operation, dir;
        scanf("%d", &operation);
        switch (operation) {
            case 1:
                scanf("%d", &dir);
                if (dir == -1)
                    happy = happy->left;
                else
                    happy = happy->right;
                break;
            case 2:
                printf("%d\n", happy->value);
                break;
            case 3:
                toDelete = mid;
                if (mid == happy)
                    happy = happy->right;
                if (rightFlag) {
                    mid = mid->right;
                    rightFlag = 0;
                } else {
                    mid = mid->left;
                    rightFlag = 1;
                }
                deleteNode(toDelete);
                // traversal(head);
                break;
        }
    } return 0;
}