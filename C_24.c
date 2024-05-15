#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the stack
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
int isEmpty(struct Stack* stack) {
    return stack->top == NULL;
}

// Function to push an element onto the stack
void push(struct Stack* stack, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Function to pop an element from the stack
int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return -1; // Return -1 indicating stack underflow
    }
    int data = stack->top->data;
    struct Node* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    return data;
}

// Function to calculate factorial of a number using stack
int factorial(int n) {
    struct Stack* stack = createStack();
    int fact = 1;
    for (int i = 1; i <= n; i++) {
        push(stack, i);
    }
    while (!isEmpty(stack)) {
        fact *= pop(stack);
    }
    return fact;
}

// Function to generate Fibonacci series using stack
void fibonacci(int n) {
    struct Stack* stack = createStack();
    push(stack, 0);
    push(stack, 1);
    printf("Fibonacci series up to %d terms:\n", n);
    if (n >= 1) {
        printf("0 ");
    }
    if (n >= 2) {
        printf("1 ");
    }
    for (int i = 3; i <= n; i++) {
        int second = pop(stack);
        int first = pop(stack);
        int next = first + second;
        push(stack, second);
        push(stack, next);
        printf("%d ", next);
    }
    printf("\n");
}

int main() {
    int choice, n;
    do {
        printf("Select an option:\n");
        printf("1. Calculate factorial of a number\n");
        printf("2. Generate Fibonacci series\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter a number to calculate factorial: ");
                scanf("%d", &n);
                printf("Factorial of %d is %d\n", n, factorial(n));
                break;
            case 2:
                printf("Enter the number of terms in Fibonacci series: ");
                scanf("%d", &n);
                fibonacci(n);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 3);
    return 0;
}
24