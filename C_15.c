#include <stdio.h>
#include <stdlib.h>

// Define structure for a tree node
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
    int height; // Height of the subtree rooted at this node
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
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// Function to get the height of a node
int height(struct TreeNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to update the height of a node
void updateHeight(struct TreeNode* node) {
    if (node == NULL)
        return;
    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));
}

// Function to perform a right rotation
struct TreeNode* rightRotate(struct TreeNode* y) {
    struct TreeNode* x = y->left;
    struct TreeNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    return x;
}

// Function to perform a left rotation
struct TreeNode* leftRotate(struct TreeNode* x) {
    struct TreeNode* y = x->right;
    struct TreeNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    return y;
}

// Function to get the balance factor of a node
int balanceFactor(struct TreeNode* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Function to perform insertion into AVL tree
struct TreeNode* insertNode(struct TreeNode* root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insertNode(root->left, data);
    else if (data > root->data)
        root->right = insertNode(root->right, data);
    else // Duplicate keys are not allowed in AVL trees
        return root;

    // Update height of the current node
    updateHeight(root);

    // Get the balance factor of this node to check if it became unbalanced
    int balance = balanceFactor(root);

    // Perform rotations if necessary to balance the tree
    if (balance > 1 && data < root->left->data) // Left Left case
        return rightRotate(root);
    if (balance < -1 && data > root->right->data) // Right Right case
        return leftRotate(root);
    if (balance > 1 && data > root->left->data) { // Left Right case
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && data < root->right->data) { // Right Left case
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to find the inorder successor (minimum value node) in a subtree
struct TreeNode* minValueNode(struct TreeNode* node) {
    struct TreeNode* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Function to perform deletion in AVL tree
struct TreeNode* deleteNode(struct TreeNode* root, int data) {
    if (root == NULL)
        return root;

    // Perform standard BST delete
    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        // Node to delete found

        // Node with only one child or no child
        if (root->left == NULL || root->right == NULL) {
            struct TreeNode* temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else // One child case
                *root = *temp; // Copy the contents of the non-empty child

            free(temp);
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            struct TreeNode* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->data = temp->data;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->data);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
        return root;

    // Update height of the current node
    updateHeight(root);

    // Get the balance factor of this node to check if it became unbalanced
    int balance = balanceFactor(root);

    // Perform rotations if necessary to balance the tree
    if (balance > 1 && balanceFactor(root->left) >= 0) // Left Left case
        return rightRotate(root);
    if (balance > 1 && balanceFactor(root->left) < 0) { // Left Right case
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && balanceFactor(root->right) <= 0) // Right Right case
        return leftRotate(root);
    if (balance < -1 && balanceFactor(root->right) > 0) { // Right Left case
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to perform inorder traversal and display the tree in sorted order
void inorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int main() {
    struct TreeNode* root = NULL;
    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 40);
    root = insertNode(root, 50);

    // Display the AVL tree in sorted order after insertions
    printf("AVL Tree in sorted order after insertions: ");
    inorderTraversal(root);
    printf("\n");

    // Delete a node and display the AVL tree in sorted order after deletion
    root = deleteNode(root, 20);
    printf("AVL Tree in sorted order after deletion of 20: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}