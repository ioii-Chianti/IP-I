#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    long data;
    struct _Node *next;
} Node;

Node createLinkedList(int size) {
    Node head;
    scanf("%ld", &(head.data));
    head.next = (Node *)malloc(sizeof(Node));
    Node *newNode = head.next;

    for (int i = 1; i < size - 1; i++) {
        scanf("%ld", &(newNode->data));
        newNode->next = (Node *)malloc(sizeof(Node));
        newNode = newNode->next;
    }
    scanf("%ld", &(newNode->data));
    newNode->next = NULL;
    return head;
}

void destroyLinkedList(Node *start) {
    Node *toFree;
    while (start != NULL) {
        toFree = start;
        start = start->next;
        free(toFree);
    }
    return;
}

Node eliminate(long toDelete) {
    Node *previous = NULL,
        *current = &head;
    while (current != NULL && current->data != toDelete) {
        previous = current;
        current = current->next;
    }

    if (current == &head) {
        head = *(current->next);
        free(current);
    } else if (current) {
        previous->next = current->next;
        free(current);
    }
    return head;
}

int search(long toSearch) {
    Node *node = &head;
    while (node) {
        if (node->data == toSearch) {
            if (node->next)
            return 1;
        }
        node = node->next;
    }
    return 0;
}

Node head;
int main() {
    int N;
    scanf("%d", &N);
    head = createLinkedList(N);

    int T;
    scanf("%d", &T);
    while (T--) {
        int operation;
        scanf("%d", &operation);

        switch (operation) {
            case 1: {
                long target;
                scanf("%ld", &target);
                head = eliminate(target);
                break;
            } case 2: {
                long target;
                scanf("%ld", &target);
                printf("%s\n", search(target) ? "Yes" : "No");
                break;
            }
        }
    }

    // Node temp = &head;
    // for (int i = 0; i < N; i++) {
    //     printf("%ld ", temp->data);
    //     temp = temp->next;
    // }

    destroyLinkedList(head.next);
    return 0;
}