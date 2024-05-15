#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent a node in the queue
struct Node {
    int data;
    struct Node* next;
};

// Structure to represent the queue
struct Queue {
    struct Node* front;
    struct Node* rear;
};

// Function to create an empty queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Function to check if the queue is empty
bool QueueEmpty(struct Queue* queue) {
    return queue->front == NULL;
}

// Function to enqueue an element into the queue
void enqueue(struct Queue* queue, int data) {
    // Create a new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    newNode->data = data;
    newNode->next = NULL;
    // If the queue is empty, make the new node front and rear
    if (QueueEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        // Link the new node to the current rear and update rear
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// Function to dequeue an element from the queue
int dequeue(struct Queue* queue) {
    if (QueueEmpty(queue)) {
        printf("Queue is empty.\n");
        return -1; // Return -1 indicating queue underflow
    }
    // Store the data of the front node
    int data = queue->front->data;
    // Move the front to the next node
    struct Node* temp = queue->front;
    queue->front = queue->front->next;
    // If the queue becomes empty after dequeuing, update rear to NULL
    if (queue->front == NULL)
        queue->rear = NULL;
    // Free the memory of the dequeued node
    free(temp);
    // Return the dequeued data
    return data;
}

// Function to display the queue
void displayQueue(struct Queue* queue) {
    if (QueueEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue: ");
    struct Node* current = queue->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to display the front element of the queue
void displayFront(struct Queue* queue) {
    if (QueueEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Front element: %d\n", queue->front->data);
}

// Function to display the rear element of the queue
void displayRear(struct Queue* queue) {
    if (QueueEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Rear element: %d\n", queue->rear->data);
}

int main() {
    struct Queue* queue = createQueue();

    // Enqueue elements into the queue
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);

    // Display the queue
    displayQueue(queue);

    // Display the front and rear elements of the queue
    displayFront(queue);
    displayRear(queue);

    // Dequeue an element from the queue
    int dequeued = dequeue(queue);
    if (dequeued != -1)
        printf("Dequeued element: %d\n", dequeued);

    // Display the queue after dequeue operation
    displayQueue(queue);

    return 0;
}
25