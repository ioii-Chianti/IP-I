#include <stdio.h>
#include <stdlib.h>
// #include "function.h"

typedef struct _Node {
    int data;
    struct _Node *next;
} Node;

Node* createList(int *a, int size) {
    Node *head = (Node *)malloc(sizeof(Node));
    Node *node = head;
    for (int i = 0; i < size; i++) {
        if (i != size - 1) {
            node->data = a[i];
            node->next = (Node *)malloc(sizeof(Node));
            node = node->next;
        } else {
            node->data = a[i];
            node->next = NULL;
        }
    }
    return head;
}

Node *newNode(int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = value;
    node->next = NULL;
    return node;
}

// 不能malloc完又指向NULL

void push_front(Node **head, int val) {
    Node *node = newNode(val);
    node->next = *head;
    *head = node;
}
void deleteElementByIdx(Node** head, int idx) {
    Node *toDelete;
    if (!idx) {
        toDelete = *head;
        *head = (*head)->next;
    } else {
        Node *previous = NULL, *current = *head;
        while (idx--) {
            if (current->next) {
                previous = current;
                current = current->next;
            } else
                return;
        }
        toDelete = current;
        previous->next = current->next;
        current = previous->next;
    }
    free(toDelete);
}

Node *copyList(Node *head) {
    if (!head)
        return NULL;
    Node *copy = newNode(head->data);
    copy->next = copyList(head->next);
    return copy;
}

void SwapElementByIdx(Node** head, int idx1, int idx2) {
    Node *node1, *node2;
    node1 = node2 = *head;

    while (idx1--)
        node1 = node1->next;
    while (idx2--)
        node2 = node2->next;

    int temp = node1->data;
    node1->data = node2->data;
    node2->data = temp;
}
void traversal(Node* head);

int main(){
    int T, M, inst, i;
    int val, idx1, idx2;
    scanf("%d%d", &T, &M);
    Node *head = NULL;
    int *array = (int *)malloc(sizeof(int) * M);
    for (i = 0; i < M; ++i) {
        scanf("%d", &array[i]);
    }
    if(M > 0) {
        head = createList(array, M);
        traversal(head);
    }
    while(T--){
        scanf("%d", &inst);
        if(inst == 0){ // insert
            scanf("%d", &val);
            push_front(&head, val);
        }else if(inst == 1){ // copy link list
            Node* otherHead = copyList(head);
            /* free original list*/
            while(head != NULL){
                Node* temp = head;
                head = head->next;
                free(temp);
            }
            head = otherHead;
        }else if(inst == 2){ // delete element
            scanf("%d", &val);
            deleteElementByIdx(&head, val);
        }else if(inst == 3){ // swap link element
            scanf("%d%d", &idx1, &idx2);
            SwapElementByIdx(&head, idx1, idx2);
        }
        traversal(head);
    }

    /* free linked list*/
    while(head != NULL){
        Node* temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}
void traversal(Node* head){
    if(head == NULL)
        return;
    while(head != NULL){
        printf("%d ", head->data);
        head = head->next;
    }printf("\n");
}
