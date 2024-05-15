#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a Student
struct Student {
    char student_name[50];
    int student_roll_no;
    int total_marks;
};

// Function to merge two subarrays arr[l..m] and arr[m+1..r]
// and count the number of swaps performed
void merge(struct Student arr[], int l, int m, int r, int *swapCount) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    struct Student L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temporary arrays back into arr[l..r]
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].student_roll_no <= R[j].student_roll_no) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
            // Count the number of swaps performed
            *swapCount += n1 - i;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Main function to implement merge sort on the student array
void mergeSort(struct Student arr[], int l, int r, int *swapCount) {
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for large l and r
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m, swapCount);
        mergeSort(arr, m + 1, r, swapCount);

        // Merge the sorted halves
        merge(arr, l, m, r, swapCount);
    }
}

int main() {
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);

    struct Student *students = (struct Student *)malloc(n * sizeof(struct Student));

    // Accept student details from the user
    printf("Enter student details:\n");
    for (int i = 0; i < n; i++) {
        printf("Enter details for student %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", students[i].student_name);
        printf("Roll No.: ");
        scanf("%d", &students[i].student_roll_no);
        printf("Total Marks: ");
        scanf("%d", &students[i].total_marks);
    }

    // Perform merge sort on the student array based on student_roll_no
    int swapCount = 0;
    mergeSort(students, 0, n - 1, &swapCount);

    // Display the sorted array
    printf("\nSorted student details based on roll number:\n");
    printf("Name\tRoll No.\tTotal Marks\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t\t%d\n", students[i].student_name, students[i].student_roll_no, students[i].total_marks);
    }

    // Display the number of swaps performed
    printf("\nNumber of swaps performed: %d\n", swapCount);

    free(students);
    return 0;
}  21