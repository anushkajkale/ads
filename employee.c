#include <stdio.h>
#include <stdlib.h>

// Define the structure for an employee record
typedef struct Employee {
    int emp_id;
    // Add other employee details here as needed
    // For simplicity, let's just include emp_id
} Employee;

// Define the structure for a node in the binary search tree
typedef struct Node {
    Employee data;
    struct Node *left;
    struct Node *right;
} Node;

// Function to create a new node
Node* createNode(Employee emp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = emp;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a new node into the binary search tree
Node* insert(Node* root, Employee emp) {
    if (root == NULL) {
        return createNode(emp);
    }
    if (emp.emp_id < root->data.emp_id) {
        root->left = insert(root->left, emp);
    } else if (emp.emp_id > root->data.emp_id) {
        root->right = insert(root->right, emp);
    }
    return root;
}

// Function to search for an employee record by emp_id
Node* search(Node* root, int emp_id) {
    if (root == NULL || root->data.emp_id == emp_id) {
        return root;
    }
    if (emp_id < root->data.emp_id) {
        return search(root->left, emp_id);
    }
    return search(root->right, emp_id);
}

// Function to perform inorder traversal of the binary search tree
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("Employee ID: %d\n", root->data.emp_id);
        // Print other employee details if needed
        inorderTraversal(root->right);
    }
}

int main() {
    Node* root = NULL;

    int choice, emp_id_to_search;
    Employee emp;

    do {
        printf("\n1. Add an employee record\n");
        printf("2. Search for an employee record\n");
        printf("3. Print all employee records sorted by emp_id\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter employee ID: ");
                scanf("%d", &emp.emp_id);
                root = insert(root, emp);
                printf("Employee record added successfully!\n");
                break;
            case 2:
                printf("Enter employee ID to search: ");
                scanf("%d", &emp_id_to_search);
                if (search(root, emp_id_to_search) != NULL) {
                    printf("Employee ID %d found!\n", emp_id_to_search);
                } else {
                    printf("Employee ID %d not found!\n", emp_id_to_search);
                }
                break;
            case 3:
                printf("Employee records sorted by emp_id:\n");
                inorderTraversal(root);
                break;
            case 4:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    // Free memory
    // (In a real-world scenario, you'd want to implement a proper memory management strategy)
    return 0;
}
