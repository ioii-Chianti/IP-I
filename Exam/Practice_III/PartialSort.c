#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct _Node {
    int data;
    struct _Node *next;
} Node;

Node *Create_Node(int val);
void Print_list(Node* head);

Node* Partial_sort(Node *head, int target) {
    Node *pre = NULL, *cur = head;
    Node *newHead = NULL, *newNode;
    int headSet = 0;

    while (cur) {
        if (cur->data < target) {
            if (!headSet) {
                newHead = Create_Node(cur->data);
                newNode = newHead;
                headSet = 1;
            } else {
                newNode->next = Create_Node(cur->data);
                newNode = newNode->next;
            }
            // Print_list(newHead);

            if (pre)
                cur = pre->next = cur->next;
            else
                cur = head = head->next;
            continue;
        }
        pre = cur;
        cur = cur->next;
    }
    if (newHead) {
        newNode->next = head;
        return newHead;
    } else
        return head;
}

Node* Split_and_Swap(Node *head, int start, int end) {
    int pivot = 0;
    Node *cur = head;
    Node *aPart_tail, *aPart_tailnxt, *bPart_headpre, *bPart_head, *tail;
    if (end - start == 1) {
        while (cur) {
            if (pivot == start)
                aPart_tail = cur;
            else if (pivot == end)
                bPart_head = cur;
            else if (cur->next == NULL)
                tail = cur;
            cur = cur->next;
            pivot++;
        }
        Node *temp = NULL;
        aPart_tail->next = temp;
        tail->next = head;
        return bPart_head;
    } else {
        while (cur) {
            if (pivot == start) {
                aPart_tail = cur;
                aPart_tailnxt = cur->next;
            } else if (pivot + 1 == end) {
                bPart_headpre = cur;
                bPart_head = cur->next;
            } else if (cur->next == NULL)
                tail = cur;
            cur = cur->next;
            pivot++;
        }
        Node *temp = NULL;
        bPart_headpre->next = head;
        aPart_tail->next = temp;
        tail->next = aPart_tailnxt;
        return bPart_head;
    }
}

int main() {
    int N, target, split_start, split_end, val;
    scanf("%d %d %d %d", &N, &target, &split_start, &split_end);

    Node *head = NULL;
    Node *cur_node = NULL;
    for (int i = 0; i < N; i++) {
        scanf("%d", &val);
        Node *new_node = Create_Node(val);
        if (!head) {
            head = new_node;
            cur_node = new_node;
        } else {
            cur_node->next = new_node;
            cur_node = new_node;
        }
    }

    head = Partial_sort(head, target);
    head = Split_and_Swap(head, split_start, split_end);
    Print_list(head);

    return 0;
}

Node* Create_Node(int val) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = val;
    node->next = NULL;
    return node;
}

void Print_list(Node* head) {
    Node *temp = head;
    while (temp) {
        if(temp->next==NULL)
            printf("%d\n", temp->data);
        else
            printf("%d ", temp->data);
        temp = temp->next;
    }
}
