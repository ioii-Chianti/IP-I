#include<stdio.h>
#include<stdlib.h>
// #include "function.h"

typedef struct _Node {
    int data;
    struct _Node *next;
} Node;

int deleteRepeat;

Node *rearrange(Node *head) {
    Node *pre = head, *cur = head->next;
    while (cur) {
        if (pre->data == cur->data) {
            pre->next = cur->next;
            cur = pre->next;
        } else {
            pre = cur;
            cur = cur->next;
        }
    }
    return head;
}

Node* Merge_lists(Node* head1, Node* head2) {
    if (!deleteRepeat) {
        head1 = rearrange(head1);
        head2 = rearrange(head2);
        deleteRepeat = 1;
    }

    if (!head1) return head2;
    if (!head2) return head1;

    if (head1->data < head2->data) {
        head1->next = Merge_lists(head1->next, head2);
        return head1;
    } else if (head1->data == head2->data) {

    } else {
        head2->next = Merge_lists(head1, head2->next);
        return head2;
    }
}

Node* Create_Node(int val);
void Print_list(Node* head);

int main() {
    int N,M,val;
    scanf("%d %d",&N,&M);

    Node* head1 = NULL;
    Node* cur_node = NULL;
    for(int i=0; i<N; i++){
        scanf("%d",&val);
        Node* new_node = Create_Node(val);
        if(head1==NULL){
            head1 = new_node;
            cur_node = new_node;
        }
        else{
            cur_node->next = new_node;
            cur_node = new_node;
        }
    }

    Node* head2 = NULL;
    cur_node = NULL;
    for(int i=0; i<M; i++){
        scanf("%d",&val);
        Node* new_node = Create_Node(val);
        if(head2==NULL){
            head2 = new_node;
            cur_node = new_node;
        }
        else{
            cur_node->next = new_node;
            cur_node = new_node;
        }
    }

    Node* merge_head = Merge_lists(head1, head2);
    Print_list(merge_head);

	return 0;
}

Node* Create_Node(int val)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = val;
    node->next = NULL;
    return node;
}

void Print_list(Node* head)
{
    Node *temp = head;
	while(temp!=NULL){
        if(temp->next==NULL) printf("%d\n", temp->data);
		else printf("%d ", temp->data);
		temp = temp->next;
	}
}
