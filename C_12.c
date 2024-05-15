#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define structure for a threaded binary tree node
struct TreeNode {
    int data;
    struct TreeNode* left;
    bool isThreadedLeft; // Indicates if left pointer is threaded
    struct TreeNode* right;
    bool isThreadedRight; // Indicates if right pointer is threaded
};

// Function to create a new node
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->isThreadedLeft = false;
    newNode->right = NULL;
    newNode->isThreadedRight = false;
    return newNode;
}

// Function to perform inorder threading of the tree
struct TreeNode* createInorderThreadedTree(struct TreeNode* root) {
    if (root == NULL)
        return NULL;

    struct TreeNode* prev = NULL;
    struct TreeNode* current = root;

    // Perform inorder traversal
    while (current != NULL) {
        if (current->left == NULL) {
            // If left child is NULL, thread it to its inorder predecessor
            current->left = prev;
            current->isThreadedLeft = true;
        }

        if (prev != NULL && prev->right == NULL) {
            // If right child of predecessor is NULL, thread it to the current node
            prev->right = current;
            prev->isThreadedRight = true;
        }

        prev = current;
        if (current->isThreadedLeft)
            current = current->right; // Move to inorder successor
        else
            current = current->left; // Move to left child
    }

    return root;
}

// Function to traverse the threaded binary tree in preorder
void preorderTraversal(struct TreeNode* root) {
    if (root == NULL)
        return;

    struct TreeNode* current = root;
    while (current != NULL) {
        printf("%d ", current->data);

        // If left child is not threaded, move to the left child
        if (!current->isThreadedLeft)
            current = current->left;
        else {
            // Otherwise, move to the right child
            current = current->right;
            // If right child is threaded, move to its inorder successor
            while (current != NULL && current->isThreadedRight) {
                printf("%d ", current->data);
                current = current->right;
            }
        }
    }
}

int main() {
    // Create a sample threaded binary tree
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    // Perform inorder threading of the tree
    struct TreeNode* threadedRoot = createInorderThreadedTree(root);

    // Traverse the threaded binary tree in preorder
    printf("Preorder Traversal of the Threaded Binary Tree: ");
    preorderTraversal(threadedRoot);
    printf("\n");

    return 0;
}