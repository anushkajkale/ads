#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct Queue {
    struct TreeNode* array[100];
    int front, rear;
};

struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = -1;
    return queue;
}

int isEmpty(struct Queue* queue) {
    return queue->front == -1;
}

void enqueue(struct Queue* queue, struct TreeNode* item) {
    if (queue->rear == 99) {
        printf("Queue is full. Enqueue operation failed.\n");
        return;
    }
    if (isEmpty(queue))
        queue->front = 0;
    queue->rear++;
    queue->array[queue->rear] = item;
}

struct TreeNode* dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Dequeue operation failed.\n");
        return NULL;
    }
    struct TreeNode* item = queue->array[queue->front];
    if (queue->front == queue->rear)
        queue->front = queue->rear = -1;
    else
        queue->front++;
    return item;
}

struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void insert(struct TreeNode** root, int data) {
    if (*root == NULL) {
        *root = createNode(data);
    } else {
        struct TreeNode* current = *root;
        struct TreeNode* parent = NULL;
        while (current != NULL) {
            parent = current;
            if (data < current->data)
                current = current->left;
            else
                current = current->right;
        }
        if (data < parent->data)
            parent->left = createNode(data);
        else
            parent->right = createNode(data);
    }
}

void levelwiseDisplay(struct TreeNode* root) {
    if (root == NULL)
        return;

    struct Queue* queue = createQueue();
    enqueue(queue, root);
    enqueue(queue, NULL);  // Using NULL as a delimiter for levels

    while (!isEmpty(queue)) {
        struct TreeNode* current = dequeue(queue);
        if (current == NULL) {
            printf("\n");
            if (!isEmpty(queue))  // Add delimiter for next level if queue is not empty
                enqueue(queue, NULL);
        } else {
            printf("%d ", current->data);
            if (current->left != NULL)
                enqueue(queue, current->left);
            if (current->right != NULL)
                enqueue(queue, current->right);
        }
    }

    free(queue);
}

void mirrorImage(struct TreeNode* root) {
    if (root == NULL)
        return;

    struct TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;

    mirrorImage(root->left);
    mirrorImage(root->right);
}

int main() {
    struct TreeNode* root = NULL;
    int choice, data;

    do {
        printf("\nMenu:\n1. Insert\n2. Display Level-wise Pyramid\n3. Display Mirror Image\n4. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the key to insert: ");
                scanf("%d", &data);
                insert(&root, data);
                break;
            case 2:
                printf("\nLevel-wise Pyramid Display:\n");
                levelwiseDisplay(root);
                break;
            case 3:
                printf("\nMirror Image Display:\n");
                mirrorImage(root);
                levelwiseDisplay(root);
                mirrorImage(root);  // Restore original tree after printing mirror image
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 4);

    return 0;
}