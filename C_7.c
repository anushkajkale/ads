#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int key;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(int key) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct TreeNode* insertNode(struct TreeNode* root, int key) {
    if (root == NULL)
        return createNode(key);

    struct TreeNode* current = root;
    struct TreeNode* parent = NULL;
    while (current != NULL) {
        parent = current;
        if (key < current->key)
            current = current->left;
        else if (key > current->key)
            current = current->right;
        else {
            printf("Key already exists in the tree.\n");
            return root;
        }
    }

    if (key < parent->key)
        parent->left = createNode(key);
    else
        parent->right = createNode(key);

    return root;
}

void preorderTraversal(struct TreeNode* root) {
    struct TreeNode* stack[100];
    int top = -1;

    if (root == NULL)
        return;

    stack[++top] = root;
    while (top >= 0) {
        struct TreeNode* current = stack[top--];
        printf("%d ", current->key);

        if (current->right != NULL)
            stack[++top] = current->right;
        if (current->left != NULL)
            stack[++top] = current->left;
    }
}

void postorderTraversal(struct TreeNode* root) {
    struct TreeNode* stack1[100];
    struct TreeNode* stack2[100];
    int top1 = -1, top2 = -1;

    if (root == NULL)
        return;

    stack1[++top1] = root;
    while (top1 >= 0) {
        struct TreeNode* current = stack1[top1--];
        stack2[++top2] = current;

        if (current->left != NULL)
            stack1[++top1] = current->left;
        if (current->right != NULL)
            stack1[++top1] = current->right;
    }

    while (top2 >= 0) {
        struct TreeNode* current = stack2[top2--];
        printf("%d ", current->key);
    }
}

int countNodes(struct TreeNode* root) {
    struct TreeNode* stack[100];
    int top = -1;
    int count = 0;

    if (root == NULL)
        return 0;

    stack[++top] = root;
    while (top >= 0) {
        struct TreeNode* current = stack[top--];
        count++;

        if (current->right != NULL)
            stack[++top] = current->right;
        if (current->left != NULL)
            stack[++top] = current->left;
    }

    return count;
}

void displayLeafNodes(struct TreeNode* root) {
    struct TreeNode* stack[100];
    int top = -1;

    if (root == NULL)
        return;

    stack[++top] = root;
    while (top >= 0) {
        struct TreeNode* current = stack[top--];

        if (current->left == NULL && current->right == NULL)
            printf("%d ", current->key);

        if (current->right != NULL)
            stack[++top] = current->right;
        if (current->left != NULL)
            stack[++top] = current->left;
    }
}

void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Insert\n");
    printf("2. Preorder Traversal\n");
    printf("3. Postorder Traversal\n");
    printf("4. Display total Number of Nodes\n");
    printf("5. Display Leaf nodes\n");
    printf("6. Exit\n");
}

int main() {
    struct TreeNode* root = NULL;
    int choice, key, totalNodes;

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the key to insert: ");
                scanf("%d", &key);
                root = insertNode(root, key);
                break;
            case 2:
                printf("Preorder Traversal: ");
                preorderTraversal(root);
                printf("\n");
                break;
            case 3:
                printf("Postorder Traversal: ");
                postorderTraversal(root);
                printf("\n");
                break;
            case 4:
                totalNodes = countNodes(root);
                printf("Total Number of Nodes: %d\n", totalNodes);
                break;
            case 5:
                printf("Leaf nodes: ");
                displayLeafNodes(root);
                printf("\n");
                break;
            case 6:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 6);

    return 0;
}