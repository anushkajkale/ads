#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Structure to represent a stack
struct Stack {
    int top;
    unsigned capacity;
    int* array;
};

// Function to create a stack
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to push an element onto the stack
void push(struct Stack* stack, int item) {
    stack->array[++stack->top] = item;
}

// Function to pop an element from the stack
int pop(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return '$'; // This character indicates an error or empty stack
}

// Function to get the top element of the stack without popping it
int peek(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top];
    return '$'; // This character indicates an error or empty stack
}

// Function to check if the character is an operand
int isOperand(char ch) {
    return isalnum(ch);
}

// Function to get the precedence of an operator
int precedence(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
    }
    return -1;
}

// Function to convert infix expression to postfix expression
char* infixToPostfix(char* infix) {
    struct Stack* stack = createStack(strlen(infix) + 1); // +1 for null terminator
    char* postfix = (char*)malloc((strlen(infix) + 1) * sizeof(char)); // +1 for null terminator
    int i, k;
    for (i = 0, k = -1; infix[i]; ++i) {
        if (isOperand(infix[i]))
            postfix[++k] = infix[i];
        else if (infix[i] == '(')
            push(stack, '(');
        else if (infix[i] == ')') {
            while (!isEmpty(stack) && peek(stack) != '(')
                postfix[++k] = pop(stack);
            if (!isEmpty(stack) && peek(stack) != '(')
                return NULL; // Invalid expression
            else
                pop(stack);
        } else { // Operator
            while (!isEmpty(stack) && precedence(infix[i]) <= precedence(peek(stack)))
                postfix[++k] = pop(stack);
            push(stack, infix[i]);
        }
    }
    while (!isEmpty(stack))
        postfix[++k] = pop(stack);
    postfix[++k] = '\0';
    return postfix;
}

// Function to evaluate a postfix expression
int evaluatePostfix(char* postfix) {
    struct Stack* stack = createStack(strlen(postfix) + 1); // +1 for null terminator
    int i, operand1, operand2;
    for (i = 0; postfix[i]; ++i) {
        if (isdigit(postfix[i]))
            push(stack, postfix[i] - '0');
        else { // Operator
            operand2 = pop(stack);
            operand1 = pop(stack);
            switch (postfix[i]) {
                case '+':
                    push(stack, operand1 + operand2);
                    break;
                case '-':
                    push(stack, operand1 - operand2);
                    break;
                case '*':
                    push(stack, operand1 * operand2);
                    break;
                case '/':
                    push(stack, operand1 / operand2);
                    break;
            }
        }
    }
    return pop(stack);
}

int main() {
    char infix[100];
    printf("Enter the infix expression: ");
    scanf("%s", infix);

    char* postfix = infixToPostfix(infix);
    if (postfix == NULL) {
        printf("Invalid infix expression!\n");
        return 1;
    }

    printf("Postfix expression: %s\n", postfix);

    int result = evaluatePostfix(postfix);
    printf("Result after evaluation: %d\n", result);

    free(postfix);

    return 0;
}
22