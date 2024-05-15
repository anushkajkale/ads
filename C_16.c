#include <stdio.h>
#include <stdlib.h>

struct Graph {
    int numVertices;
    int** adjMatrix;
};

struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->adjMatrix = (int**)malloc(numVertices * sizeof(int*));
    for (int i = 0; i < numVertices; ++i) {
        graph->adjMatrix[i] = (int*)calloc(numVertices, sizeof(int));
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1; // If undirected graph
}

void displayAdjMatrix(struct Graph* graph) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < graph->numVertices; ++i) {
        for (int j = 0; j < graph->numVertices; ++j) {
            printf("%d ", graph->adjMatrix[i][j]);
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

        for (int i = 0; i < graph->numVertices; ++i) {
            if (graph->adjMatrix[current][i] && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
    printf("\n");
    free(visited);
    free(queue);
}

void DFS(struct Graph* graph, int startVertex) {
    int* visited = (int*)calloc(graph->numVertices, sizeof(int));
    int* stack = (int*)malloc(graph->numVertices * sizeof(int));
    int top = -1;

    printf("Depth-First Search Traversal: ");
    stack[++top] = startVertex;
    visited[startVertex] = 1;

    while (top != -1) {
        int current = stack[top--];
        printf("%d ", current);

        for (int i = 0; i < graph->numVertices; ++i) {
            if (graph->adjMatrix[current][i] && !visited[i]) {
                stack[++top] = i;
                visited[i] = 1;
            }
        }
    }
    printf("\n");
    free(visited);
    free(stack);
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

    displayAdjMatrix(graph);

    int startVertex;
    printf("Enter the starting vertex for BFS and DFS traversals: ");
    scanf("%d", &startVertex);

    BFS(graph, startVertex);
    DFS(graph, startVertex);

    // Free allocated memory
    for (int i = 0; i < numVertices; ++i) {
        free(graph->adjMatrix[i]);
    }
    free(graph->adjMatrix);
    free(graph);

    return 0;
}
