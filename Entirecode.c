#include <stdio.h>
#include <stdlib.h>

#define STACK_MAX 100

struct node {
    int val;
    struct node* left;
    struct node* right;
};

struct node* root = NULL;
struct node* stack[STACK_MAX];
int top = -1;

// Forward declaration
struct node* minValueNode(struct node* node);

// Function to create a new node
struct node* createNode(int val) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a value into the binary tree
void insert(int val) {
    int flag = 0;
    struct node* newnode = createNode(val);
    if (root == NULL) {
        root = newnode;
        return;
    } else {
        struct node* temp = root;
        do {
            char dir;
            printf("%d left or right? ", temp->val);
            scanf(" %c", &dir);
            if (dir == 'l') {
                if (temp->left == NULL) {
                    temp->left = newnode;
                    flag = 1;
                } else {
                    temp = temp->left;
                }
            } else {
                if (temp->right == NULL) {
                    temp->right = newnode;
                    flag = 1;
                } else {
                    temp = temp->right;
                }
            }
        } while (flag != 1);
    }
}

// Function to check if the stack is full
int isStackFull() {
    return top == STACK_MAX - 1;
}

// Function to check if the stack is empty
int isStackEmpty() {
    return top == -1;
}

// Function to push a node onto the stack
void push(struct node* item) {
    if (!isStackFull()) {
        top++;
        stack[top] = item;
    } else {
        printf("Stack Overflow\n");
    }
}

// Function to pop a node from the stack
struct node* pop() {
    if (!isStackEmpty()) {
        struct node* item = stack[top];
        top--;
        return item;
    } else {
        printf("Stack Underflow\n");
        return NULL;
    }
}

// Function to perform inorder traversal recursively
void inorder_recursive(struct node* root) {
    if (root != NULL) {
        inorder_recursive(root->left);
        printf("%d ", root->val);
        inorder_recursive(root->right);
    }
}

// Function to perform preorder traversal recursively
void preorder_recursive(struct node* root) {
    if (root != NULL) {
        printf("%d ", root->val);
        preorder_recursive(root->left);
        preorder_recursive(root->right);
    }
}

// Function to perform postorder traversal recursively
void postorder_recursive(struct node* root) {
    if (root != NULL) {
        postorder_recursive(root->left);
        postorder_recursive(root->right);
        printf("%d ", root->val);
    }
}

// Function to perform inorder traversal non-recursively
void inorder_nonrec() {
    struct node* current = root;
    while (current != NULL || !isStackEmpty()) {
        while (current != NULL) {
            push(current);
            current = current->left;
        }
        current = pop();
        printf("%d ", current->val);
        current = current->right;
    }
}

// Function to perform preorder traversal non-recursively
void preorder_nonrec() {
    if (root == NULL)
        return;
    push(root);
    while (!isStackEmpty()) {
        struct node* current = pop();
        printf("%d ", current->val);
        if (current->right != NULL)
            push(current->right);
        if (current->left != NULL)
            push(current->left);
    }
}

// Function to perform postorder traversal non-recursively
void postorder_nonrec() {
    if (root == NULL)
        return;
    struct node* current = root;
    struct node* lastVisited = NULL;
    while (current != NULL || !isStackEmpty()) {
        while (current != NULL) {
            push(current);
            current = current->left;
        }
        current = stack[top];
        if (current->right == NULL || current->right == lastVisited) {
            printf("%d ", current->val);
            lastVisited = current;
            pop();
            current = NULL;
        } else {
            current = current->right;
        }
    }
}

// Function to calculate the height of the tree
int height(struct node* root) {
    if (root == NULL)
        return 0;
    else {
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
    }
}

// Function to print nodes at a given level
void printLevel(struct node* root, int level) {
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->val);
    else if (level > 1) {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

// Function to perform level order traversal
void levelOrderTraversal(struct node* root) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        printf("Level %d: ", i);
        printLevel(root, i);
        printf("\n");
    }
}

// Function to search for a key in the tree
struct node* search(struct node* root, int key) {
    if (root == NULL || root->val == key)
        return root;
    if (root->val < key)
        return search(root->right, key);
    return search(root->left, key);
}

// Function to count the total number of nodes in the tree
int countNodes(struct node* root) {
    if (root == NULL)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Function to count the total number of leaf nodes in the tree
int countLeafNodes(struct node* root) {
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

// Function to delete a node with a given key from the tree
struct node* deleteNode(struct node* root, int key) {
    if (root == NULL)
        return root;
    if (key < root->val)
        root->left = deleteNode(root->left, key);
    else if (key > root->val)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }
        struct node* temp = minValueNode(root->right);
        root->val = temp->val;
        root->right = deleteNode(root->right, temp->val);
    }
    return root;
}

// Function to find the node with the minimum value in a subtree
struct node* minValueNode(struct node* node) {
    struct node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Function to create the mirror image of a tree
struct node* mirrorImage(struct node* root) {
    if (root == NULL)
        return NULL;
    struct node* mirror = createNode(root->val);
    mirror->left = mirrorImage(root->right);
    mirror->right = mirrorImage(root->left);
    return mirror;
}

int main() {
    int val, c, a = 1;
    while (a != 0) {
        printf("\n1. Insert\n2. Inorder Traversal\n3. Preorder Traversal\n4. Postorder Traversal\n5. Breadth First Traversal\n");
        printf("6. Height of the Tree\n7. Level-wise Display\n8. Search Key\n9. Total Number of Nodes\n10. Total Number of Leaf Nodes\n");
        printf("11. Delete Node\n12. Mirror Image\n13. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &c);
        switch (c) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                insert(val);
                break;
            case 2:
                printf("\nInorder Traversal (recursive): ");
                inorder_recursive(root);
                printf("\nInorder Traversal (non-recursive): ");
                inorder_nonrec();
                break;
            case 3:
                printf("\nPreorder Traversal (recursive): ");
                preorder_recursive(root);
                printf("\nPreorder Traversal (non-recursive): ");
                preorder_nonrec();
                break;
            case 4:
                printf("\nPostorder Traversal (recursive): ");
                postorder_recursive(root);
                printf("\nPostorder Traversal (non-recursive): ");
                postorder_nonrec();
                break;
            case 5:
                printf("Breadth First Traversal: ");
                levelOrderTraversal(root);
                break;
            case 6:
                printf("Height of the Tree: %d\n", height(root));
                break;
            case 7:
                printf("Level-wise Display:\n");
                levelOrderTraversal(root);
                break;
            case 8:
                printf("Enter key to search: ");
                scanf("%d", &val);
                if (search(root, val) != NULL)
                    printf("Key found in the tree\n");
                else
                    printf("Key not found in the tree\n");
                break;
            case 9:
                printf("Total Number of Nodes: %d\n", countNodes(root));
                break;
            case 10:
                printf("Total Number of Leaf Nodes: %d\n", countLeafNodes(root));
                break;
            case 11:
                printf("Enter value to delete: ");
                scanf("%d", &val);
                root = deleteNode(root, val);
                printf("Node deleted successfully\n");
                break;
            case 12:
                printf("Mirror Image of the Tree:\n");
                root = mirrorImage(root);
                inorder_recursive(root);
                break;
            case 13:
                printf("Exiting...\n");
                a = 0;
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    }
    return 0;
}
