#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the doubly linked list
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node with the given data
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the beginning of the doubly linked list
void insertBegin(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
    }
}

// Function to insert a node at the end of the doubly linked list
void insertEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = newNode;
        newNode->prev = current;
    }
}

// Function to insert a node after a given node in the doubly linked list
void insertAfter(struct Node* prevNode, int data) {
    if (prevNode == NULL) {
        printf("Previous node cannot be NULL.\n");
        return;
    }
    struct Node* newNode = createNode(data);
    newNode->next = prevNode->next;
    if (prevNode->next != NULL)
        prevNode->next->prev = newNode;
    prevNode->next = newNode;
    newNode->prev = prevNode;
}

// Function to delete the first occurrence of a node with given key in the doubly linked list
void deleteNode(struct Node** head, int key) {
    if (*head == NULL) {
        printf("List is empty. Cannot delete.\n");
        return;
    }
    struct Node* current = *head;
    // If the key is found in the first node itself
    if (current->data == key) {
        *head = current->next;
        if (*head != NULL)
            (*head)->prev = NULL;
        free(current);
        return;
    }
    // Search for the node with the key
    while (current != NULL && current->data != key)
        current = current->next;
    // If the key is not found in the list
    if (current == NULL) {
        printf("Key not found in the list.\n");
        return;
    }
    // Remove the node
    if (current->prev != NULL)
        current->prev->next = current->next;
    if (current->next != NULL)
        current->next->prev = current->prev;
    free(current);
}

// Function to display the doubly linked list in forward direction
void displayForward(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("Forward List: ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Function to display the doubly linked list in reverse direction
void displayBackward(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    // Move to the last node
    while (head->next != NULL)
        head = head->next;
    printf("Backward List: ");
    // Traverse backwards and print the data
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->prev;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;

    // Insert at the beginning
    insertBegin(&head, 10);
    insertBegin(&head, 20);
    insertBegin(&head, 30);

    displayForward(head);
    displayBackward(head);

    // Insert at the end
    insertEnd(&head, 40);
    insertEnd(&head, 50);

    displayForward(head);
    displayBackward(head);

    // Insert after a specific node
    insertAfter(head->next, 35);

    displayForward(head);
    displayBackward(head);

    // Delete a node
    deleteNode(&head, 30);

    displayForward(head);
    displayBackward(head);

    return 0;
}
29