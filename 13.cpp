
// 13.	Write a program to implement bankers algorithm 
//   Number of processes: 5 (P0 to P4)
// Resources:
// Resource A: Number of instances: 10
// Resource B: Number of instances: 5
// Resource C: Number of instances: 7


// #include <stdio.h>
// #include <stdbool.h>

// struct ProcessInfo
// {
//     int max[10];
//     int allocated[10];
//     int need[10];
// };

// int noOfProcesses, noOfResources;

// // Function to take input
// void getInput(struct ProcessInfo process[noOfProcesses], int available[noOfResources])
// {
//     // Fill array of Structures
//     for (int i = 0; i < noOfProcesses; i++)
//     {
//         printf("Enter details for Process[%d]\n", i);
//         printf("Enter Maximum Need: ");
//         for (int j = 0; j < noOfResources; j++)
//             scanf("%d", &process[i].max[j]);
//         printf("Enter Number of Allocated Resources for this process: ");
//         for (int j = 0; j < noOfResources; j++)
//         {
//             scanf("%d", &process[i].allocated[j]);
//             // Calculate need/future need
//             process[i].need[j] = process[i].max[j] - process[i].allocated[j];
//         }
//     }
//     printf("Enter Available Resources: ");
//     for (int i = 0; i < noOfResources; i++)
//     {
//         scanf("%d", &available[i]);
//     }
// }

// // Function to display process info in tabular form
// void displayInfo(struct ProcessInfo process[noOfProcesses])
// {
//     printf("\nP_ID\tMax\t\tAllocated\tNeed\n");
//     for (int i = 0; i < noOfProcesses; i++)
//     {
//         printf("P[%d]\t", i);
//         for (int j = 0; j < noOfResources; j++)
//             printf("%d ", process[i].max[j]);
//         printf("\t\t");
//         for (int j = 0; j < noOfResources; j++)
//             printf("%d ", process[i].allocated[j]);
//         printf("\t\t");
//         for (int j = 0; j < noOfResources; j++)
//             printf("%d ", process[i].need[j]);
//         printf("\n");
//     }
// }

// // Function to apply safety algorithm
// bool applySafetyAlgorithm(struct ProcessInfo process[noOfProcesses], int available[noOfResources], int safeSequence[noOfProcesses])
// {
//     bool finish[noOfProcesses];
//     int work[noOfResources];
//     for (int i = 0; i < noOfResources; i++)
//     {
//         work[i] = available[i];
//     }
//     for (int i = 0; i < noOfProcesses; i++)
//         finish[i] = false;
//     bool proceed = true;
//     int k = 0;
//     while (proceed)
//     {
//         proceed = false;
//         for (int i = 0; i < noOfProcesses; i++)
//         {
//             bool flag = true;
//             // Find Index i
//             if (finish[i] == false)
//             {
//                 for (int j = 0; j < noOfResources; j++)
//                 {
//                     // if Need <= Work
//                     if (process[i].need[j] <= work[j])
//                     {
//                         continue;
//                     }
//                     else
//                     {
//                         flag = false; // implies that the current process need > work
//                         break;
//                     }
//                 }
//                 if (flag == false)
//                     continue; // check for next process

//                 // If we get Index i (or process i), update work
//                 for (int j = 0; j < noOfResources; j++)
//                     work[j] = work[j] + process[i].allocated[j];
//                 finish[i] = true;
//                 safeSequence[k++] = i;
//                 proceed = true; // tells that we got at least one process in safe state, we can proceed
//             }
//         } // end of outer for loop
//     }     // end of while

//     // check finish array
//     int i;
//     for (i = 0; i < noOfProcesses && finish[i] == true; i++)
//     {
//         continue;
//     }
//     // If all processes are completed, then return true
//     if (i == noOfProcesses)
//         return true;
//     else
//         return false;
// }

// // Function to check if system is in a safe state
// bool isSafeState(struct ProcessInfo process[noOfProcesses], int available[noOfResources], int safeSequence[noOfProcesses])
// {
//     if (applySafetyAlgorithm(process, available, safeSequence) == true)
//         return true;
//     return false;
// }

// int main()
// {
//     printf(" No of Processes: ");
//     scanf("%d", &noOfProcesses);
//     printf(" No of Res. instances in the system: ");
//     scanf("%d", &noOfResources);
//     int available[noOfResources];
//     int safeSequence[noOfProcesses];
//     // Create Array of Structures to store Process Information
//     struct ProcessInfo process[noOfProcesses];

//     printf("         * Enter details of processes *       \n");

//     getInput(process, available);

//     displayInfo(process);
//     if (isSafeState(process, available, safeSequence))
//     {
//         printf("\nsafe State\n");
//         printf("Safe Sequence is: ");
//         for (int i = 0; i < noOfProcesses; i++)
//             printf("P[%d] ", safeSequence[i]);
//     }
//     else
//         printf("not in a safe state.");
//     return 0;
// }

// C++ program to illustrate Banker's Algorithm
#include<iostream>
using namespace std;

// Number of processes
const int P = 5;

// Number of resources
const int R = 3;

// Function to find the need of each process
void calculateNeed(int need[P][R], int maxm[P][R],
				int allot[P][R])
{
	// Calculating Need of each P
	for (int i = 0 ; i < P ; i++)
		for (int j = 0 ; j < R ; j++)

			// Need of instance = maxm instance -
			//				 allocated instance
			need[i][j] = maxm[i][j] - allot[i][j];
}

// Function to find the system is in safe state or not
bool isSafe(int processes[], int avail[], int maxm[][R],
			int allot[][R])
{
	int need[P][R];

	// Function to calculate need matrix
	calculateNeed(need, maxm, allot);

	// Mark all processes as infinish
	bool finish[P] = {0};

	// To store safe sequence
	int safeSeq[P];

	// Make a copy of available resources
	int work[R];
	for (int i = 0; i < R ; i++)
		work[i] = avail[i];

	// While all processes are not finished
	// or system is not in safe state.
	int count = 0;
	while (count < P)
	{
		// Find a process which is not finish and
		// whose needs can be satisfied with current
		// work[] resources.
		bool found = false;
		for (int p = 0; p < P; p++)
		{
			// First check if a process is finished,
			// if no, go for next condition
			if (finish[p] == 0)
			{
				// Check if for all resources of
				// current P need is less
				// than work
				int j;
				for (j = 0; j < R; j++)
					if (need[p][j] > work[j])
						break;

				// If all needs of p were satisfied.
				if (j == R)
				{
					// Add the allocated resources of
					// current P to the available/work
					// resources i.e.free the resources
					for (int k = 0 ; k < R ; k++)
						work[k] += allot[p][k];

					// Add this process to safe sequence.
					safeSeq[count++] = p;

					// Mark this p as finished
					finish[p] = 1;

					found = true;
				}
			}
		}

		// If we could not find a next process in safe
		// sequence.
		if (found == false)
		{
			cout << "System is not in safe state";
			return false;
		}
	}

	// If system is in safe state then
	// safe sequence will be as below
	cout << "System is in safe state.\nSafe"
		" sequence is: ";
	for (int i = 0; i < P ; i++)
		cout << safeSeq[i] << " ";

	return true;
}

// Driver code
int main()
{
	int processes[] = {0, 1, 2, 3, 4};

	// Available instances of resources
	int avail[] = {3, 3, 2};

	// Maximum R that can be allocated
	// to processes
	int maxm[][R] = {{7, 5, 3},
					{3, 2, 2},
					{9, 0, 2},
					{2, 2, 2},
					{4, 3, 3}};

	// Resources allocated to processes
	int allot[][R] = {{0, 1, 0},
					{2, 0, 0},
					{3, 0, 2},
					{2, 1, 1},
					{0, 0, 2}};

	// Check system is in safe state or not
	isSafe(processes, avail, maxm, allot);

	return 0;
}
