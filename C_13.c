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

// Function to traverse the threaded binary tree in inorder
void inorderTraversal(struct TreeNode* root) {
    if (root == NULL)
        return;

    struct TreeNode* current = root;
    while (current->left != NULL)
        current = current->left; // Move to the leftmost node

    while (current != NULL) {
        printf("%d ", current->data);

        // If right child is threaded, move to its inorder successor
        if (current->isThreadedRight)
            current = current->right;
        else {
            // Otherwise, move to the leftmost node of the right subtree
            current = current->right;
            while (current != NULL && !current->isThreadedLeft)
                current = current->left;
        }
    }
}

int main() {
    // Create a sample binary tree
    struct TreeNode* root = createNode(6);
    root->left = createNode(3);
    root->right = createNode(8);
    root->left->left = createNode(1);
    root->left->right = createNode(5);
    root->right->left = createNode(7);
    root->right->right = createNode(9);

    // Perform inorder threading of the tree
    struct TreeNode* threadedRoot = createInorderThreadedTree(root);

    // Traverse the threaded binary tree in inorder
    printf("Inorder Traversal of the Threaded Binary Tree: ");
    inorderTraversal(threadedRoot);
    printf("\n");

    return 0;
}