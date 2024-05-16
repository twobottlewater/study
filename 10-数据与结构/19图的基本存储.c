#include <stdio.h>
#include <stdlib.h>



typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
} Graph;

// 创建一个图
Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->adjLists = (Node**)malloc(numVertices * sizeof(Node*));

    // 初始化邻接链表
    for (int i = 0; i < numVertices; i++) {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

// 添加一条边
void addEdge(Graph* graph, int src, int dest) {
    // 创建一个新的节点
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = dest;

    // 将节点添加到源节点的邻接链表中
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // 如果图是无向的，还需要添加一条边到目标节点的邻接链表中
    // addEdge(graph, dest, src);
}

// 打印图
void printGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        printf("顶点 %d 的邻接节点：", i);
        Node* temp = graph->adjLists[i];
        while (temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

// 释放图
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->adjLists[i];
        while (temp != NULL) {
            Node* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph->adjLists);
    free(graph);
}





int main() {
    // 创建一个图，有 5 个顶点
    Graph* graph = createGraph(5);

    // 添加边
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);

    // 打印图
    printGraph(graph);

    // 释放图
    freeGraph(graph);

    return 0;
}
