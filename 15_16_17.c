// #include <stdio.h>

// void bestFit(int blockSize[], int m, int processSize[], int n) {
//     int allocate[n];
//     for (int i = 0; i < n; i++) {
//         allocate[i] = -1;
//     }

//     for (int i = 0; i < n; i++) {
//         int bestIndex = -1;
//         for (int j = 0; j < m; j++) {
//             if (blockSize[j] >= processSize[i]) {
//                 if (bestIndex == -1 || blockSize[j] < blockSize[bestIndex]) {
//                     bestIndex = j;
//                 }
//             }
//         }
//         if (bestIndex != -1) {
//             allocate[i] = bestIndex;
//             blockSize[bestIndex] -= processSize[i];
//         }
//     }

//     printf("\nUsing Best Fit Algorithm\n");
//     printf(" Process No\t Process Size \t Block Number\n");
//     for (int i = 0; i < n; i++) {
//         printf(" P%d\t\t %d\t\t", i, processSize[i]);
//         if (allocate[i] != -1) {
//             printf("%d\n", allocate[i] + 1);
//         } else {
//             printf("Not Allocated\n");
//         }
//     }
// }

// void firstFit(int blockSize[], int m, int processSize[], int n) {
//     int allocate[n];
//     for (int i = 0; i < n; i++) {
//         allocate[i] = -1;
//     }

//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < m; j++) {
//             if (blockSize[j] >= processSize[i]) {
//                 allocate[i] = j;
//                 blockSize[j] -= processSize[i];
//                 break;
//             }
//         }
//     }

//     printf("\nUsing First Fit Algorithm\n");
//     printf(" Process No\t Process Size \t Block Number\n");
//     for (int i = 0; i < n; i++) {
//         printf(" P%d\t\t %d\t\t", i, processSize[i]);
//         if (allocate[i] != -1) {
//             printf("%d\n", allocate[i] + 1);
//         } else {
//             printf("Not Allocated\n");
//         }
//     }
// }

// void worstFit(int blockSize[], int m, int processSize[], int n) {
//     int allocate[n];
//     for (int i = 0; i < n; i++) {
//         allocate[i] = -1;
//     }

//     for (int i = 0; i < n; i++) {
//         int worstIndex = -1;
//         for (int j = 0; j < m; j++) {
//             if (blockSize[j] >= processSize[i]) {
//                 if (worstIndex == -1 || blockSize[j] > blockSize[worstIndex]) {
//                     worstIndex = j;
//                 }
//             }
//         }
//         if (worstIndex != -1) {
//             allocate[i] = worstIndex;
//             blockSize[worstIndex] -= processSize[i];
//         }
//     }

//     printf("\nUsing Worst Fit Algorithm\n");
//     printf(" Process No\t Process Size \t Block Number\n");
//     for (int i = 0; i < n; i++) {
//         printf(" P%d\t\t %d\t\t", i, processSize[i]);
//         if (allocate[i] != -1) {
//             printf("%d\n", allocate[i] + 1);
//         } else {
//             printf("Not Allocated\n");
//         }
//     }
// }

// int main() {
//     int m = 5; // Number of memory blocks
//     int n = 4; // Number of processes

//     // blockSize[] and processSize[] specific to this scenario
//     int blockSize[] = {100, 500, 200, 300, 600};
//     int processSize[] = {212, 417, 112, 426};

//     firstFit(blockSize, m, processSize, n);
//     worstFit(blockSize, m, processSize, n);
//     bestFit(blockSize, m, processSize, n);

//     return 0;
// }
//wrong op////////////////////////////////////////////////////////

//wf
#include <stdio.h>

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocate[n]; // Initializing allocate list
    for (int i = 0; i < n; i++) {
        allocate[i] = -1;
    }

    // select the worst memory block that can be allocated to a process
    for (int i = 0; i < n; i++) {
        int worstIndex = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIndex == -1) {
                    worstIndex = j;
                } else if (blockSize[worstIndex] < blockSize[j]) {
                    worstIndex = j;
                }
            }
        }
        if (worstIndex != -1) {
            allocate[i] = worstIndex;
            blockSize[worstIndex] -= processSize[i];
        }
    }

    // Display the processes with the blocks that are allocated to a respective process
    printf("\nFor Worst Fit Algorithm\n");
    printf(" Process No\t Process Size \t Block Number\n");
    for (int i = 0; i < n; i++) {
        printf(" %d\t\t %d\t\t", i + 1, processSize[i]);
        if (allocate[i] != -1) {
            printf("%d\n", allocate[i] + 1);
        } else {
            printf("Not Allocated\n");
        }
    }
}

int main() {
    int m, n;

    // get the number of blocks and processes
    printf("Enter the number of blocks: ");
    scanf("%d", &m);
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int blockSize[m], processSize[n];

    // get the size of each block
    printf("Enter the size of each block: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &blockSize[i]);
    }

    // get the size of each process
    printf("Enter the size of each process: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processSize[i]);
    }

    // Call the function
    worstFit(blockSize, m, processSize, n);

    return 0;
}


//bf

#include <stdio.h>

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n]; 
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int bestIndex = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIndex == -1) {
                    bestIndex = j;
                } else if (blockSize[bestIndex] > blockSize[j]) {
                    bestIndex = j;
                }
            }
        }
        if (bestIndex != -1) {
            allocation[i] = bestIndex;
            blockSize[bestIndex] -= processSize[i];
        }
    }

    printf("\nUsing Best Fit Algorithm\n");
    printf(" Process No\t Process Size \t Block Number\n");
    for (int i = 0; i < n; i++) {
        printf(" %d\t\t %d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i] + 1);
        } else {
            printf("Not Allocated\n");
        }
    }
}

int main() {
    int m, n;
    printf("no of memory blocks: ");
    scanf("%d", &m);
    printf("number of processes: ");
    scanf("%d", &n);

    int blockSize[m], processSize[n];
    printf("size of each memory block: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &blockSize[i]);
    }

    printf("size of each process: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processSize[i]);
    }

    bestFit(blockSize, m, processSize, n);

    return 0;
}


//ff

#include <stdio.h>

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocate[n]; // Initializing allocate list
    for (int i = 0; i < n; i++) {
        allocate[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocate[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    // Display the processes with the blocks that are allocated to a respective process
    printf(" Process No\t Process Size \t Block Number\n");
    for (int i = 0; i < n; i++) {
        printf(" %d\t\t %d\t\t", i + 1, processSize[i]);
        if (allocate[i] != -1) {
            printf("%d\n", allocate[i] + 1);
        } else {
            printf("Not Allocated\n");
        }
    }
}

int main() {
    int m, n;

    // get the number of blocks and processes
    printf("Enter the number of blocks: ");
    scanf("%d", &m);
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int blockSize[m], processSize[n];

    // get the size of each block
    printf("Enter the size of each block: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &blockSize[i]);
    }

    // get the size of each process
    printf("Enter the size of each process: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processSize[i]);
    }

    // Call the function
    firstFit(blockSize, m, processSize, n);

    return 0;
}

//nf

#include <stdio.h>

void nextFit(int blockSize[], int m, int processSize[], int n) {
    int allocate[n]; // Initializing allocate list
    for (int i = 0; i < n; i++) {
        allocate[i] = -1;
    }

    int lastIndex = 0; // Initialize the index of the last block allocated

    for (int i = 0; i < n; i++) {
        for (int j = lastIndex; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocate[i] = j;
                blockSize[j] -= processSize[i];
                lastIndex = j; // Update the index of the last block allocated
                break;
            }
        }
        // If no block is found in the remaining blocks, start searching from the beginning
        
            for (int j = 0; j < lastIndex; j++) {
                if (blockSize[j] >= processSize[i]) {
                    allocate[i] = j;
                    blockSize[j] -= processSize[i];
                    lastIndex = j; // Update the index of the last block allocated
                    break;
                }
            }
    }

    // Display the processes with the blocks that are allocated to a respective process
    printf(" Process No\t Process Size \t Block Number\n");
    for (int i = 0; i < n; i++) {
        printf(" %d\t\t %d\t\t", i + 1, processSize[i]);
        if (allocate[i] != -1) {
            printf("%d\n", allocate[i] + 1);
        } else {
            printf("Not Allocated\n");
        }
    }
}

int main() {
    int m, n;

    // get the number of blocks and processes
    printf("Enter the number of blocks: ");
    scanf("%d", &m);
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int blockSize[m], processSize[n];

    // get the size of each block
    printf("Enter the size of each block: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &blockSize[i]);
    }

    // get the size of each process
    printf("Enter the size of each process: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processSize[i]);
    }

    // Call the function
    nextFit(blockSize, m, processSize, n);

    return 0;
}
