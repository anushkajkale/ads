//Binary Tree and perform following 
// nonrecursive operations on it.
//  a. Preorder Traversal, b. Postorder Traversal,
//   c. Count total no. of nodes, d. Display height of a tree.
#include <stdio.h>
#include <stdlib.h>

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

void preorderTraversal(struct TreeNode* current) {
    if (current != NULL) {
        printf("%d ", current->data);
        preorderTraversal(current->left);
        preorderTraversal(current->right);
    }
}

void postorderTraversal(struct TreeNode* current) {
    if (current != NULL) {
        postorderTraversal(current->left);
        postorderTraversal(current->right);
        printf("%d ", current->data);
    }
}

int countNodes(struct TreeNode* root) {
    if (root == NULL)
        return 0;

    return 1 + countNodes(root->left) + countNodes(root->right);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct TreeNode* root) {
    if (root == NULL)
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return 1 + max(leftHeight, rightHeight);
}

int main() {
    struct TreeNode* root = NULL;
    char choice;

    do {
        int data;
        struct TreeNode* newNode;

        printf("Enter the data for the new node: ");
        scanf("%d", &data);
        newNode = createNode(data);

        if (root == NULL) {
            root = newNode;
        } else {
            struct TreeNode* current = root;
            while (1) {
                printf("Do you want to insert '%d' to the left or right of '%d' (l/r): ", data, current->data);
                scanf(" %c", &choice);
                if (choice == 'l' || choice == 'L') {
                    if (current->left == NULL) {
                        current->left = newNode;
                        break;
                    } else {
                        current = current->left;
                    }
                } else if (choice == 'r' || choice == 'R') {
                    if (current->right == NULL) {
                        current->right = newNode;
                        break;
                    } else {
                        current = current->right;
                    }
                } else {
                    printf("Invalid choice! Please enter 'L' or 'R'.\n");
                }
            }
        }

        printf("Do you want to insert another node? (Y/N): ");
        scanf(" %c", &choice);
    } while (choice == 'Y' || choice == 'y');

    printf("\nPreorder Traversal: ");
    preorderTraversal(root);
    printf("\nPostorder Traversal: ");
    postorderTraversal(root);
    printf("\nTotal number of nodes: %d\n", countNodes(root));
    printf("Height of the tree: %d\n", height(root));

    return 0;
}