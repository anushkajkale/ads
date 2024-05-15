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

struct TreeNode* findMinNode(struct TreeNode* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

struct TreeNode* deleteNode(struct TreeNode* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        struct TreeNode* temp = findMinNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }

    return root;
}

void postorderTraversal(struct TreeNode* root) {
    struct TreeNode* stack[100];
    int top = -1;

    if (root == NULL)
        return;

    struct TreeNode* current = root;
    do {
        while (current != NULL) {
            if (current->right != NULL)
                stack[++top] = current->right;
            stack[++top] = current;
            current = current->left;
        }

        current = stack[top--];
        if (current->right != NULL && stack[top] == current->right) {
            stack[top--];
            stack[++top] = current;
            current = current->right;
        } else {
            printf("%d ", current->key);
            current = NULL;
        }
    } while (top >= 0);
}

void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Insert\n");
    printf("2. Delete\n");
    printf("3. Display Tree (Postorder non-recursive)\n");
    printf("4. Exit\n");
}

int main() {
    struct TreeNode* root = NULL;
    int choice, key;

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
                printf("Enter the key to delete: ");
                scanf("%d", &key);
                root = deleteNode(root, key);
                break;
            case 3:
                printf("Postorder Traversal (non-recursive): ");
                postorderTraversal(root);
                printf("\n");
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