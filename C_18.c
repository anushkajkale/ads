#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 100

// Function to find the vertex with minimum key value
int minKey(int key[], bool mstSet[], int vertices) {
    int min = INT_MAX, minIndex;

    for (int v = 0; v < vertices; v++) {
        if (mstSet[v] == false && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }

    return minIndex;
}

// Function to print the constructed MST stored in parent[]
void printMST(int parent[], int graph[MAX_VERTICES][MAX_VERTICES], int vertices) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < vertices; i++)
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
}

// Function to implement Prim's algorithm to find MST of a graph
void primMST(int graph[MAX_VERTICES][MAX_VERTICES], int vertices) {
    int parent[vertices]; // Array to store constructed MST
    int key[vertices];    // Key values used to pick minimum weight edge in cut
    bool mstSet[vertices]; // To represent set of vertices not yet included in MST

    // Initialize all keys as INFINITE
    for (int i = 0; i < vertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    // Always include first 0th vertex in MST.
    key[0] = 0; // Make key 0 so that this vertex is picked as first vertex
    parent[0] = -1; // First node is always root of MST

    // The MST will have V vertices
    for (int count = 0; count < vertices - 1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int u = minKey(key, mstSet, vertices);

        // Add the picked vertex to the MST Set
        mstSet[u] = true;

        // Update key value and parent index of the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not yet included in MST
        for (int v = 0; v < vertices; v++) {
            // graph[u][v] is non zero only for adjacent vertices of m
            // mstSet[v] is false for vertices not yet included in MST
            // Update the key only if graph[u][v] is smaller than key[v]
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print the constructed MST
    printMST(parent, graph, vertices);
}

int main() {
    int vertices, edges;
    int graph[MAX_VERTICES][MAX_VERTICES];

    // Accept number of vertices and edges from user
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    // Initialize graph with all 0s
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            graph[i][j] = 0;
        }
    }

    // Accept edges from user and their weights
    printf("Enter edges (source destination weight):\n");
    for (int i = 0; i < edges; i++) {
        int source, destination, weight;
        scanf("%d %d %d", &source, &destination, &weight);
        graph[source][destination] = weight;
        graph[destination][source] = weight; // For undirected graph
    }

    // Print the Minimum Spanning Tree (MST) using Prim's algorithm
    printf("Minimum Spanning Tree using Prim's algorithm:\n");
    primMST(graph, vertices);

    return 0;
}
18