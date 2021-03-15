#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node {
    int val;
    struct _Node *next;
} Node;

typedef struct {
    int size;
    Node **childlist;   // 一個陣列裡面裝linked list
} Graph;

Graph graph;

Node *newNode(int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = value;
    node->next = NULL;
    return node;
}

void freeGraph(Graph *g) {
    Node **list = g->childlist;
    for (int i = 0; i < g->size; i++) {
        Node *node = list[i];
        while (node) {
            Node *toFree = node;
            node = node->next;
            free(toFree);
        }
    } return;
}

void dfs(Node **list, int *dp, int root_val) {
    Node *node = list[root_val];
    while (node) {
        dfs(list, dp, node->val);
        dp[root_val] += (dp[node->val] + 1);
        node = node->next;
    }
}

void printGraph(Graph *graph){
    int i;
    int size = graph->size;
    for (i = 0; i < size; ++i) {
        printf("%d: ",i+1);
        Node* head = graph->childlist[i];
        while(head != NULL){
            printf("%d ",head->val+1);
            head = head->next;
        }printf("\n");
    }
}

int main() {
    int n;
    scanf("%d", &n);
    graph.size = n;
    graph.childlist = (Node **)malloc(n * sizeof(Node *));
    for (int i = 0; i < n; i++)
        graph.childlist[i] = NULL;

    int x_val, y_val;
    while (scanf("%d%d", &x_val, &y_val) != EOF) {
        Node *newChild = newNode(y_val - 1);
        // add edge to graph, 把孩子連成list
        newChild->next = graph.childlist[x_val - 1];
        graph.childlist[x_val - 1] = newChild;
    }   // 把原有的值往外推，接在頭 N -> O -> O -> NULL

    int *dp = (int *)malloc(n * sizeof(int));
    memset(dp, 0, sizeof(dp));
    dfs(graph.childlist, dp, 0);
    for (int i = 0; i < n; i++)
        printf("%d%c", dp[i], i != n - 1 ? ' ' : '\n');
    // free all resource
    freeGraph(&graph);
    free(dp);
    return 0;
}