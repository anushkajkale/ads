#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 5 // Maximum size of the circular queue

// Structure to represent a circular queue
struct CircularQueue {
    int* array;
    int front, rear, size;
    unsigned capacity;
};

// Function to create an empty circular queue
struct CircularQueue* createCircularQueue(unsigned capacity) {
    struct CircularQueue* queue = (struct CircularQueue*)malloc(sizeof(struct CircularQueue));
    queue->capacity = capacity;
    queue->size = 0;
    queue->front = 0;
    queue->rear = -1; // -1 indicates an empty queue
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

// Function to check if the circular queue is empty
bool isEmpty(struct CircularQueue* queue) {
    return queue->size == 0;
}

// Function to check if the circular queue is full
bool isFull(struct CircularQueue* queue) {
    return queue->size == queue->capacity;
}

// Function to add an element to the rear end of the circular queue
void enqueueRear(struct CircularQueue* queue, int item) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity; // Circular increment
    queue->array[queue->rear] = item;
    queue->size++;
    printf("%d enqueued to rear end of the queue.\n", item);
}

// Function to add an element to the front end of the circular queue
void enqueueFront(struct CircularQueue* queue, int item) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }
    queue->front = (queue->front - 1 + queue->capacity) % queue->capacity; // Circular decrement
    queue->array[queue->front] = item;
    queue->size++;
    printf("%d enqueued to front end of the queue.\n", item);
}

// Function to remove an element from the rear end of the circular queue
int dequeueRear(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1; // Return -1 indicating queue underflow
    }
    int item = queue->array[queue->rear];
    queue->rear = (queue->rear - 1 + queue->capacity) % queue->capacity; // Circular decrement
    queue->size--;
    return item;
}

// Function to remove an element from the front end of the circular queue
int dequeueFront(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1; // Return -1 indicating queue underflow
    }
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity; // Circular increment
    queue->size--;
    return item;
}

// Function to display the circular queue
void displayQueue(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Circular Queue: ");
    int i;
    for (i = queue->front; i != queue->rear; i = (i + 1) % queue->capacity)
        printf("%d ", queue->array[i]);
    printf("%d\n", queue->array[i]);
}

int main() {
    struct CircularQueue* queue = createCircularQueue(MAX_SIZE);

    enqueueRear(queue, 10);
    enqueueRear(queue, 20);
    enqueueRear(queue, 30);

    displayQueue(queue);

    enqueueFront(queue, 40);
    enqueueFront(queue, 50);

    displayQueue(queue);

    printf("Dequeued from rear end: %d\n", dequeueRear(queue));
    printf("Dequeued from front end: %d\n", dequeueFront(queue));

    displayQueue(queue);

    return 0;
}
26