#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the singly linked list
struct Node {
    int data;
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
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the linked list
void insertEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = newNode;
    }
}

// Function to reverse a singly linked list
struct Node* reverse(struct Node* head) {
    struct Node* prev = NULL;
    struct Node* current = head;
    struct Node* next = NULL;
    while (current != NULL) {
        next = current->next; // Store next node
        current->next = prev; // Reverse current node's pointer
        prev = current; // Move pointers one position ahead
        current = next;
    }
    head = prev; // Update head to the last node
    return head;
}

// Function to display the elements of a singly linked list
void displayList(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("List: ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    // Create a singly linked list: 1 -> 2 -> 3 -> 4 -> 5
    struct Node* head = NULL;
    insertEnd(&head, 1);
    insertEnd(&head, 2);
    insertEnd(&head, 3);
    insertEnd(&head, 4);
    insertEnd(&head, 5);

    printf("Original ");
    displayList(head);

    // Reverse the list
    head = reverse(head);

    printf("Reversed ");
    displayList(head);

    return 0;
}
28