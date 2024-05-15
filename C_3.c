#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

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

void insertNode(struct TreeNode** root, int data) {
    struct TreeNode* newNode = createNode(data);
    if (*root == NULL) {
        *root = newNode;
    } else {
        struct TreeNode* current = *root;
        while (1) {
            if (data < current->data) {
                if (current->left == NULL) {
                    current->left = newNode;
                    break;
                } else {
                    current = current->left;
                }
            } else if (data > current->data) {
                if (current->right == NULL) {
                    current->right = newNode;
                    break;
                } else {
                    current = current->right;
                }
            } else {
                printf("Duplicate keys are not allowed\n");
                free(newNode);
                break;
            }
        }
    }
}

void levelwiseDisplay(struct TreeNode* root) {
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }

    struct TreeNode* queue[100];
    int front = -1, rear = -1;
    queue[++rear] = root;

    while (front != rear) {
        int nodesInLevel = rear - front;
        while (nodesInLevel > 0) {
            struct TreeNode* current = queue[++front];
            printf("%d ", current->data);

            if (current->left != NULL)
                queue[++rear] = current->left;
            if (current->right != NULL)
                queue[++rear] = current->right;

            nodesInLevel--;
        }
        printf("\n");
    }
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

int height(struct TreeNode* root) {
    if (root == NULL)
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

struct TreeNode* search(struct TreeNode* root, int key) {
    while (root != NULL && root->data != key) {
        if (key < root->data)
            root = root->left;
        else
            root = root->right;
    }
    return root;
}

int main() {
    struct TreeNode* root = NULL;
    int choice, data, key;

    do {
        printf("\n1. Insert\n2. Levelwise Display\n3. Mirror Image\n4. Display Height\n5. Search\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insertNode(&root, data);
                break;
            case 2:
                printf("Levelwise Display:\n");
                levelwiseDisplay(root);
                break;
            case 3:
                printf("Mirror Image:\n");
                mirrorImage(root);
                levelwiseDisplay(root);
                break;
            case 4:
                printf("Height of the tree: %d\n", height(root));
                break;
            case 5:
                printf("Enter key to search: ");
                scanf("%d", &key);
                if (search(root, key) != NULL)
                    printf("%d found in the tree.\n", key);
                else
                    printf("%d not found in the tree.\n", key);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 6);

    return 0;
}