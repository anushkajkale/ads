#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent a node in the singly linked list
struct Node {
    int data;
    struct Node* next;
};

// Structure to represent the stack
struct Stack {
    struct Node* top;
};

// Function to create an empty stack
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}

// Function to check if the stack is empty
bool StackEmpty(struct Stack* stack) {
    return stack->top == NULL;
}

// Function to push an element onto the stack
void push(struct Stack* stack, int data) {
    // Create a new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    // Assign data to the new node
    newNode->data = data;
    // Link the new node to the current top of the stack
    newNode->next = stack->top;
    // Make the new node the new top of the stack
    stack->top = newNode;
}

// Function to pop an element from the stack
int pop(struct Stack* stack) {
    if (StackEmpty(stack)) {
        printf("Stack is empty.\n");
        return -1; // Return -1 indicating stack underflow
    }
    // Store the data of the top node
    int data = stack->top->data;
    // Move the top to the next node
    struct Node* temp = stack->top;
    stack->top = stack->top->next;
    // Free the memory of the popped node
    free(temp);
    // Return the popped data
    return data;
}

// Function to display the stack
void displayStack(struct Stack* stack) {
    if (StackEmpty(stack)) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack: ");
    struct Node* current = stack->top;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    struct Stack* stack = createStack();

    // Push elements onto the stack
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);

    // Display the stack
    displayStack(stack);

    // Pop an element from the stack
    int popped = pop(stack);
    if (popped != -1)
        printf("Popped element: %d\n", popped);

    // Display the stack after popping
    displayStack(stack);

    // Pop all elements from the stack
    while (!StackEmpty(stack)) {
        popped = pop(stack);
        if (popped != -1)
            printf("Popped element: %d\n", popped);
    }

    // Display the stack after popping all elements
    displayStack(stack);

    return 0;
}
23