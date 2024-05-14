#include <stdio.h>
#include <stdlib.h>

// Define a structure for tree nodes
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Function to create a new node
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node into the tree
void insertNode(Node* root, int value) {
    Node* newNode = createNode(value);
    Node* current = root;
    Node* parent = NULL;

    // Traverse the tree to find the appropriate position to insert the new node
    while (current != NULL) {
        parent = current;
        if (value > current->data)
            current = current->left;
        else
            current = current->right;
    }

    // Insert the new node
    if (value > parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;
}

// Function to count total number of nodes in the tree
int countNodes(Node* root) {
    if (root == NULL)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Function to count total number of edges in the tree
int countEdges(Node* root) {
    if (root == NULL)
        return 0;
    return countNodes(root) - 1;
}

// Function to calculate height of the tree
int height(Node* root) {
    if (root == NULL)
        return -1;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Function to display tree nodes level-wise
void levelwiseDisplay(Node* root, int level) {
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->data);
    else if (level > 1) {
        levelwiseDisplay(root->left, level - 1);
        levelwiseDisplay(root->right, level - 1);
    }
}

// Function to perform mirror image of the tree
void mirror(Node* root) {
    if (root == NULL)
        return;
    Node* temp = root->left;
    root->left = root->right;
    root->right = temp;
    mirror(root->left);
    mirror(root->right);
}

// Function to count leaf nodes in the tree
int countLeafNodes(Node* root) {
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

// Function to display leaf nodes in the tree
void displayLeafNodes(Node* root) {
    if (root == NULL)
        return;
    if (root->left == NULL && root->right == NULL)
        printf("%d ", root->data);
    displayLeafNodes(root->left);
    displayLeafNodes(root->right);
}

// Function to delete a node from the tree
Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;

        root->data = temp->data;

        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to search for a key in the tree
Node* searchNode(Node* root, int key) {
    if (root == NULL || root->data == key)
        return root;

    if (root->data < key)
        return searchNode(root->left, key);

    return searchNode(root->right, key);
}

// Recursive inorder traversal
void inorderTraversalRecursive(Node* root) {
    if (root != NULL) {
        inorderTraversalRecursive(root->left);
        printf("%d ", root->data);
        inorderTraversalRecursive(root->right);
    }
}

// Non-recursive inorder traversal using stack
void inorderTraversalNonRecursive(Node* root) {
    Node* stack[100]; // Assuming the maximum number of nodes in the tree is 100
    int top = -1;
    Node* current = root;

    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        printf("%d ", current->data);
        current = current->right;
    }
}

// Recursive preorder traversal
void preorderTraversalRecursive(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversalRecursive(root->left);
        preorderTraversalRecursive(root->right);
    }
}

// Non-recursive preorder traversal using stack
void preorderTraversalNonRecursive(Node* root) {
    Node* stack[100]; // Assuming the maximum number of nodes in the tree is 100
    int top = -1;
    stack[++top] = root;

    while (top != -1) {
        Node* current = stack[top--];
        printf("%d ", current->data);

        if (current->right != NULL)
            stack[++top] = current->right;
        if (current->left != NULL)
            stack[++top] = current->left;
    }
}

// Recursive postorder traversal
void postorderTraversalRecursive(Node* root) {
    if (root != NULL) {
        postorderTraversalRecursive(root->left);
        postorderTraversalRecursive(root->right);
        printf("%d ", root->data);
    }
}

// Non-recursive postorder traversal using two stacks
void postorderTraversalNonRecursive(Node* root) {
    Node* stack1[100]; // Assuming the maximum number of nodes in the tree is 100
    Node* stack2[100];
    int top1 = -1, top2 = -1;

    stack1[++top1] = root;

    while (top1 != -1) {
        Node* current = stack1[top1--];
        stack2[++top2] = current;

        if (current->left != NULL)
            stack1[++top1] = current->left;
        if (current->right != NULL)
            stack1[++top1] = current->right;
    }

    while (top2 != -1) {
        printf("%d ", stack2[top2--]->data);
    }
}

// Menu function
void menu() {
    printf("\n\nBinary Tree Operations:\n");
    printf("1. Insert Node\n");
    printf("2. Delete Node\n");
    printf("3. Search Node\n");
    printf("4. Display Inorder Traversal\n");
    printf("5. Display Preorder Traversal\n");
    printf("6. Display Postorder Traversal\n");
    printf("7. Count Total Number of Nodes\n");
    printf("8. Calculate Height of the Tree\n");
    printf("9. Count Total Number of Edges\n");
    printf("10. Display Level-wise\n");
    printf("11. Display Leaf Nodes\n");
    printf("12. Mirror Image of the Tree\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    Node* root = NULL;
    int choice, value;

    do {
        menu();
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                printf("Exiting...\n");
                break;
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                if (root == NULL)
                    root = createNode(value);
                else
                    insertNode(root, value);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;
            case 3:
                printf("Enter value to search: ");
                scanf("%d", &value);
                if (searchNode(root, value) != NULL)
                    printf("Node %d found in the tree.\n", value);
                else
                    printf("Node %d not found in the tree.\n", value);
                break;
            case 4:
                printf("Inorder Traversal: ");
                inorderTraversalRecursive(root);
                printf("\n");
                break;
            case 5:
                printf("Preorder Traversal: ");
                preorderTraversalRecursive(root);
                printf("\n");
                break;
            case 6:
                printf("Postorder Traversal: ");
                postorderTraversalRecursive(root);
                printf("\n");
                break;
            case 7:
                printf("Total Number of Nodes: %d\n", countNodes(root));
                break;
            case 8:
                printf("Height of the Tree: %d\n", height(root));
                break;
            case 9:
                printf("Total Number of Edges: %d\n", countEdges(root));
                break;
            case 10:
                printf("Level-wise Display:\n");
                for (int i = 1; i <= height(root) + 1; i++) {
                    printf("Level %d: ", i);
                    levelwiseDisplay(root, i);
                    printf("\n");
                }
                break;
            case 11:
                printf("Leaf Nodes: ");
                displayLeafNodes(root);
                printf("\n");
                break;
            case 12:
                printf("Mirroring the Tree...\n");
                mirror(root);
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 0);

    return 0;
}
