#include <stdio.h>
#include <stdlib.h>

// 链表节点结构，用于存储每个顶点的邻接顶点
typedef struct AdjListNode {
    int dest;
    struct AdjListNode* next;
} AdjListNode;

// 邻接链表结构，每个顶点都有一个
typedef struct AdjList {
    AdjListNode* head;  // 指向链表的头节点
} AdjList;

// 图结构，包含顶点的数量和邻接链表数组
typedef struct Graph {
    int V;
    AdjList* array;
} Graph;

// 创建新的邻接链表节点
AdjListNode* newAdjListNode(int dest) {
    AdjListNode* newNode = (AdjListNode*) malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// 创建一个图，大小为V个顶点
Graph* createGraph(int V) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->V = V;

    // 创建一个大小为V的邻接链表数组
    graph->array = (AdjList*) malloc(V * sizeof(AdjList));

    // 初始化每个邻接链表为空
    for (int i = 0; i < V; ++i) {
        graph->array[i].head = NULL;
    }

    return graph;
}

// 向图中添加边
void addEdge(Graph* graph, int src, int dest) {
    // 添加从src到dest的边
    AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // 由于是无向图，还要添加从dest到src的边
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}


// DFS辅助函数，递归地遍历顶点
void DFSUtil(Graph* graph, int v, int visited[]) {
    visited[v] = 1;  // 标记当前节点为已访问
    printf("%d ", v);

    // 递归访问当前顶点的所有邻接顶点
    AdjListNode* node = graph->array[v].head;
    while (node != NULL) {
        if (!visited[node->dest]) {
            DFSUtil(graph, node->dest, visited);
        }
        node = node->next;
    }
}

// 深度优先遍历图
void DFS(Graph* graph) {
    // 标记所有顶点为未访问
    int* visited = (int*) malloc(graph->V * sizeof(int));
    for (int i = 0; i < graph->V; i++) {
        visited[i] = 0;
    }

    // 对每个未访问的顶点调用递归辅助函数
    for (int i = 0; i < graph->V; i++) {
        if (!visited[i]) {
            DFSUtil(graph, i, visited);
        }
    }

    free(visited);
}


int main()
 {
    // 创建一个图，有5个顶点
    Graph* graph = createGraph(9);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    addEdge(graph, 0, 6);
    addEdge(graph, 0, 5);
    addEdge(graph, 5, 8);
    addEdge(graph, 6, 7);
     printf("深度优先遍历 (从顶点0开始):\n");

    DFS(graph);

    // 释放图结构占用的内存
    for (int v = 0; v < graph->V; ++v) {
        AdjListNode* node = graph->array[v].head;
        while (node) {
            AdjListNode* temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);

    return 0;
}
