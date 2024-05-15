//	Consider the order of request for cylinder access of the disk is - (98, 183, 37, 122, 14, 124, 65, 67) and current position of Read/Write head is: 53. Find the total head movements to access the data on the cylinder using following disk scheduling algorithms:
// 1)	FCFS
// 2)	 C SCAN


//wrong op tho
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to simulate FCFS disk scheduling algorithm
int FCFS(int requests[], int n, int headPosition) {
    int totalHeadMovements = 0;
    int i;

    for (i = 0; i < n; i++) {
        totalHeadMovements += abs(headPosition - requests[i]);
        headPosition = requests[i];
    }

    return totalHeadMovements;
}

// Function to simulate SSTF disk scheduling algorithm
int SSTF(int requests[], int n, int headPosition) {
    int totalHeadMovements = 0;
    int i, j;

    int* visited = (int*)malloc(n * sizeof(int));
    for (i = 0; i < n; i++) {
        visited[i] = 0;
    }

    for (i = 0; i < n; i++) {
        int minDistance = INT_MAX;
        int minIndex = -1;

        for (j = 0; j < n; j++) {
            if (!visited[j] && abs(headPosition - requests[j]) < minDistance) {
                minDistance = abs(headPosition - requests[j]);
                minIndex = j;
            }
        }

        visited[minIndex] = 1;
        totalHeadMovements += minDistance;
        headPosition = requests[minIndex];
    }

    free(visited);
    return totalHeadMovements;
}

// Function to compare integers for qsort
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Function to simulate SCAN disk scheduling algorithm
int SCAN(int requests[], int n, int headPosition, int isCSCAN) {
    int totalHeadMovements = 0;
    int i;

    int* lowerRequests = (int*)malloc(n * sizeof(int));
    int* upperRequests = (int*)malloc(n * sizeof(int));
    int lowerCount = 0, upperCount = 0;

    for (i = 0; i < n; i++) {
        if (requests[i] < headPosition) {
            lowerRequests[lowerCount++] = requests[i];
        } else {
            upperRequests[upperCount++] = requests[i];
        }
    }

    qsort(lowerRequests, lowerCount, sizeof(int), compare);
    qsort(upperRequests, upperCount, sizeof(int), compare);

    if (!isCSCAN) {
        // SCAN
        for (i = lowerCount - 1; i >= 0; i--) {
            totalHeadMovements += abs(headPosition - lowerRequests[i]);
            headPosition = lowerRequests[i];
        }
        for (i = 0; i < upperCount; i++) {
            totalHeadMovements += abs(headPosition - upperRequests[i]);
            headPosition = upperRequests[i];
        }
    } else {
        // C-SCAN
        totalHeadMovements += abs(headPosition - 0); // Move to the beginning
        headPosition = 0;
        for (i = 0; i < upperCount; i++) {
            totalHeadMovements += abs(headPosition - upperRequests[i]);
            headPosition = upperRequests[i];
        }
        totalHeadMovements += abs(headPosition - 199); // Move to the end
    }

    free(lowerRequests);
    free(upperRequests);

    return totalHeadMovements;
}



int main() {
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int n = sizeof(requests) / sizeof(requests[0]);
    int headPosition = 53;

    // FCFS
    int totalHeadMovementsFCFS = FCFS(requests, n, headPosition);
    printf("Total head movements using FCFS: %d\n", totalHeadMovementsFCFS);

    // SSTF
    int totalHeadMovementsSSTF = SSTF(requests, n, headPosition);
    printf("Total head movements using SSTF: %d\n", totalHeadMovementsSSTF);

    // SCAN
    int totalHeadMovementsSCAN = SCAN(requests, n, headPosition, 0);
    printf("Total head movements using SCAN: %d\n", totalHeadMovementsSCAN);

    // C-SCAN
    int totalHeadMovementsCSCAN = SCAN(requests, n, headPosition, 1);
    printf("Total head movements using C-SCAN: %d\n", totalHeadMovementsCSCAN);

    return 0;
}
