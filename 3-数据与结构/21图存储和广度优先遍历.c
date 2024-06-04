#include <stdio.h>
#include <stdlib.h>

// 链表节点，用于表示图中的边
typedef struct AdjListNode {
    int dest;
    struct AdjListNode* next;
} AdjListNode;

// 邻接表，每个节点对应图中的一个顶点
typedef struct AdjList {
    struct AdjListNode* head;  // 链表的头节点
} AdjList;

// 图的结构，包含顶点数和邻接表数组
typedef struct Graph {
    int V;
    struct AdjList* array;
} Graph;

// 队列节点
typedef struct QueueNode {
    int vertex;
    struct QueueNode* next;
} QueueNode;

// 队列，用于BFS遍历
typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// 函数声明
AdjListNode* newAdjListNode(int dest);
Graph* createGraph(int V);
void addEdge(Graph* graph, int src, int dest);
void BFS(Graph* graph, int startVertex);

Queue* createQueue();
void enqueue(Queue* queue, int vertex);
int dequeue(Queue* queue);
int isEmpty(Queue* queue);

int main() {
    // 创建图
    int V = 5;
    Graph* graph = createGraph(V);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    // 从顶点 0 开始进行BFS遍历
    printf("从顶点 0 开始的广度优先遍历：\n");
    BFS(graph, 0);

    return 0;
}

// 创建一个新的邻接链表节点
AdjListNode* newAdjListNode(int dest) {
    AdjListNode* newNode = (AdjListNode*) malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// 创建一个图，V 是顶点数
Graph* createGraph(int V) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->V = V;

    // 创建一个大小为 V 的数组，用于存储邻接表
    graph->array = (AdjList*) malloc(V * sizeof(AdjList));

    // 初始化每个邻接表为 NULL
    for (int i = 0; i < V; ++i) {
        graph->array[i].head = NULL;
    }

    return graph;
}

// 向图中添加边
void addEdge(Graph* graph, int src, int dest) {
    // 添加从 src 到 dest 的边
    AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // 由于是无向图，添加从 dest 到 src 的边
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// 实现 BFS 遍历
void BFS(Graph* graph, int startVertex) {
    int* visited = (int*)malloc(graph->V * sizeof(int));
    for (int i = 0; i < graph->V; i++) {
        visited[i] = 0;  // 初始化所有顶点为未访问
    }

    Queue* queue = createQueue();

    // 标记起始顶点为已访问并入队
    visited[startVertex] = 1;
    enqueue(queue, startVertex);

    while (!isEmpty(queue)) {
        // 出队一个顶点并访问
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        // 获取所有邻接顶点
        AdjListNode* temp = graph->array[currentVertex].head;
        while (temp) {
            int adjVertex = temp->dest;

            // 如果未访问，则标记为已访问并入队
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                enqueue(queue, adjVertex);
            }
            temp = temp->next;
        }
    }

    // 释放内存
    free(visited);
}

// 创建队列
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// 入队
void enqueue(Queue* queue, int vertex) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->vertex = vertex;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// 出队
int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        return -1;
    }
    QueueNode* temp = queue->front;
    int vertex = temp->vertex;

    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return vertex;
}

// 判断队列是否为空
int isEmpty(Queue* queue) {
    return queue->front == NULL;
}
