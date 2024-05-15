#include <stdio.h>
#include <stdlib.h>

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int numVertices;
    struct Node** adjList;
};

struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->adjList = (struct Node**)malloc(numVertices * sizeof(struct Node*));
    for (int i = 0; i < numVertices; ++i) {
        graph->adjList[i] = NULL;
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = dest;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = src;
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

void displayAdjList(struct Graph* graph) {
    printf("Adjacency List:\n");
    for (int i = 0; i < graph->numVertices; ++i) {
        printf("%d -> ", i);
        struct Node* temp = graph->adjList[i];
        while (temp) {
            printf("%d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void BFS(struct Graph* graph, int startVertex) {
    int* visited = (int*)calloc(graph->numVertices, sizeof(int));
    int* queue = (int*)malloc(graph->numVertices * sizeof(int));
    int front = 0, rear = 0;

    printf("Breadth-First Search Traversal: ");
    queue[rear++] = startVertex;
    visited[startVertex] = 1;

    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current);

        struct Node* temp = graph->adjList[current];
        while (temp) {
            int neighbor = temp->vertex;
            if (!visited[neighbor]) {
                queue[rear++] = neighbor;
                visited[neighbor] = 1;
            }
            temp = temp->next;
        }
    }
    printf("\n");
    free(visited);
    free(queue);
}

void DFSUtil(struct Graph* graph, int vertex, int* visited) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    struct Node* temp = graph->adjList[vertex];
    while (temp) {
        int neighbor = temp->vertex;
        if (!visited[neighbor]) {
            DFSUtil(graph, neighbor, visited);
        }
        temp = temp->next;
    }
}

void DFS(struct Graph* graph, int startVertex) {
    int* visited = (int*)calloc(graph->numVertices, sizeof(int));
    printf("Depth-First Search Traversal: ");
    DFSUtil(graph, startVertex, visited);
    printf("\n");
    free(visited);
}

int main() {
    int numVertices, numEdges;
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &numVertices);
    printf("Enter the number of edges in the graph: ");
    scanf("%d", &numEdges);

    struct Graph* graph = createGraph(numVertices);

    printf("Enter the edges (source and destination vertices) in the graph:\n");
    for (int i = 0; i < numEdges; ++i) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    displayAdjList(graph);

    int startVertex;
    printf("Enter the starting vertex for BFS and DFS traversals: ");
    scanf("%d", &startVertex);

    BFS(graph, startVertex);
    DFS(graph, startVertex);

    // Free allocated memory
    for (int i = 0; i < numVertices; ++i) {
        struct Node* temp = graph->adjList[i];
        while (temp) {
            struct Node* prev = temp;
            temp = temp->next;
            free(prev);
        }
    }
    free(graph->adjList);
    free(graph);

    return 0;
}
