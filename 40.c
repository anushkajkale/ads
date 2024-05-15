// 40.	Write a program to implement following CPU scheduling algorithms:
// 1)	SJF
// 2)	SRTF


//sjf
// struct Process {  
// int arrival_time;  
// int burst_time;  
// int waiting_time;  
// };  
  
// int compare(const void *a, const void *b) {  
// struct Process *p1 = (struct Process *)a;  
// struct Process *p2 = (struct Process *)b;  
// return p1->burst_time - p2->burst_time;  
// }  
  
// int main() {  
// int n, i, j;  
// float avg_waiting_time = 0, avg_turnaround_time = 0;  
// printf("Enter the number of processes: ");  
// scanf("%d", &n);  
// struct Process processes[n];  
// for (i = 0; i< n; i++) {  
// printf("Enter arrival time and burst time of process %d: ", i+1);  
// scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);  
// }  
// qsort(processes, n, sizeof(struct Process), compare);  
// processes[0].waiting_time = 0;  
// for (i = 1; i< n; i++) {  
// processes[i].waiting_time = 0;  
// for (j = 0; j <i; j++)   
// {   
  
// processes[i].waiting_time += processes[j].burst_time;   
  
// }   
  
// avg_waiting_time += processes[i].waiting_time;   
  
// }   
  
// avg_waiting_time /= n;   
  
// for (i = 0; i< n; i++) {   
  
// avg_turnaround_time += processes[i].burst_time + processes[i].waiting_time;   
  
// }   
  
// avg_turnaround_time /= n;   
  
// printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");   
  
// for (i = 0; i< n; i++) {   
  
// printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i+1, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].burst_time+processes[i].waiting_time);   
  
// }   
  
// printf("\nAverage Waiting Time: %f\n", avg_waiting_time);   
  
// printf("Average Turnaround Time: %f\n", avg_turnaround_time);   
  
// return 0;   
  
// }  


//srtf

// C program to implement Shortest Remaining Time First
// Shortest Remaining Time First (SRTF)

#include <stdio.h>
#include <limits.h>

struct Process {
    int pid; // Process ID
    int bt; // Burst Time
    int art; // Arrival Time
};

// Function to find the waiting time for all
// processes
void findWaitingTime(struct Process proc[], int n, int wt[]) {
    int rt[n];

    // Copy the burst time into rt[]
    for (int i = 0; i < n; i++)
        rt[i] = proc[i].bt;

    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    int check = 0; // changed boolean to integer

    // Process until all processes gets
    // completed
    while (complete != n) {

        // Find process with minimum
        // remaining time among the
        // processes that arrives till the
        // current time
        for (int j = 0; j < n; j++) {
            if ((proc[j].art <= t) &&
            (rt[j] < minm) && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
                check = 1; // changed boolean to integer
            }
        }

        if (check == 0) {
            t++;
            continue;
        }

        // Reduce remaining time by one
        rt[shortest]--;

        // Update minimum
        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;

        // If a process gets completely
        // executed
        if (rt[shortest] == 0) {

            // Increment complete
            complete++;
            check = 0; // changed boolean to integer

            // Find finish time of current
            // process
            finish_time = t + 1;

            // Calculate waiting time
            wt[shortest] = finish_time -
                        proc[shortest].bt -
                        proc[shortest].art;

            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        // Increment time
        t++;
    }
}

// Function to calculate turn around time
void findTurnAroundTime(struct Process proc[], int n, int wt[], int tat[]) {
    // calculating turnaround time by adding
    // bt[i] + wt[i]
    for (int i = 0; i < n; i++)
        tat[i] = proc[i].bt + wt[i];
}

// Function to calculate average time
void findavgTime(struct Process proc[], int n) {
    int wt[n], tat[n], total_wt = 0,
                    total_tat = 0;

    // Function to find waiting time of all
    // processes
    findWaitingTime(proc, n, wt);

    // Function to find turn around time for
    // all processes
    findTurnAroundTime(proc, n, wt, tat);

    // Display processes along with all
    // details
    printf(" P\t\t"
        "BT\t\t"
        "WT\t\t"
        "TAT\t\t\n");

    // Calculate total waiting time and
    // total turnaround time
    for (int i = 0; i < n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf(" %d\t\t"
            "%d\t\t %d"
            "\t\t %d\n", proc[i].pid,
            proc[i].bt, wt[i], tat[i]);
    }

    printf("\nAverage waiting time = "
        "%f", (float)total_wt / (float)n);
    printf("\nAverage turn around time = "
        "%f", (float)total_tat / (float)n);
}

// Driver code
int main() {
    struct Process proc[] = { { 1, 6, 2 }, { 2, 2, 5 },
                    { 3, 8, 1 }, { 4, 3, 0}, {5, 4, 4} };
    int n = sizeof(proc) / sizeof(proc[0]);

    findavgTime(proc, n);
    return 0;
}