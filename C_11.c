#include <stdio.h>
#include <stdlib.h>

// Define structure for an employee record
struct Employee {
    int emp_id;
    char name[50];
    // Add other fields as needed
    struct Employee* left;
    struct Employee* right;
};

// Function to create a new employee record
struct Employee* createEmployee(int emp_id, char name[]) {
    struct Employee* newEmployee = (struct Employee*)malloc(sizeof(struct Employee));
    if (newEmployee == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newEmployee->emp_id = emp_id;
    strcpy(newEmployee->name, name);
    newEmployee->left = NULL;
    newEmployee->right = NULL;
    return newEmployee;
}

// Function to insert an employee record into BST
struct Employee* insertEmployee(struct Employee* root, int emp_id, char name[]) {
    if (root == NULL)
        return createEmployee(emp_id, name);

    if (emp_id < root->emp_id)
        root->left = insertEmployee(root->left, emp_id, name);
    else if (emp_id > root->emp_id)
        root->right = insertEmployee(root->right, emp_id, name);

    return root;
}

// Function to search for an employee record by emp_id
struct Employee* searchEmployee(struct Employee* root, int emp_id) {
    if (root == NULL || root->emp_id == emp_id)
        return root;

    if (emp_id < root->emp_id)
        return searchEmployee(root->left, emp_id);

    return searchEmployee(root->right, emp_id);
}

// Function to perform inorder traversal and display employee records
void inorderTraversal(struct Employee* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("Employee ID: %d, Name: %s\n", root->emp_id, root->name);
        inorderTraversal(root->right);
    }
}

int main() {
    // Create a sample employee records BST
    struct Employee* root = NULL;
    root = insertEmployee(root, 101, "John");
    insertEmployee(root, 102, "Alice");
    insertEmployee(root, 105, "Bob");
    insertEmployee(root, 103, "Emma");
    insertEmployee(root, 104, "Michael");

    // Search for an employee record
    int emp_id_to_search = 103;
    struct Employee* result = searchEmployee(root, emp_id_to_search);
    if (result != NULL) {
        printf("Employee found - ID: %d, Name: %s\n", result->emp_id, result->name);
    } else {
        printf("Employee with ID %d not found\n", emp_id_to_search);
    }

    // Display employee records in ascending order of emp_id
    printf("\nEmployee Records (Sorted by Employee ID):\n");
    inorderTraversal(root);

    return 0;
}