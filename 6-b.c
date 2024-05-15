// 6.	Write a program to implement following CPU scheduling algorithms:
// 1)	FCFS
// 2)	Round Robin – time slice=4ms


#include <stdio.h>
#include <stdbool.h>

#define MAX 100
#define TIME_SLICE 4

typedef struct {
    int pid;  // Process ID
    int at;   // Arrival Time
    int bt;   // Burst Time
    int ct;   // Completion Time
    int tat;  // Turnaround Time
    int wt;   // Waiting Time
    int rt;   // Remaining Time (for Round Robin)
} Process;

void fcfs(Process p[], int n) {
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].at) {
            currentTime = p[i].at;
        }
        p[i].ct = currentTime + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        currentTime += p[i].bt;
    }
}

void roundRobin(Process p[], int n) {
    int currentTime = 0;
    int completed = 0;
    int timeSlice = TIME_SLICE;
    bool inQueue[MAX] = { false };

    while (completed < n) {
        bool done = true;
        for (int i = 0; i < n; i++) {
            if (p[i].rt > 0) {
                if (p[i].at <= currentTime) {
                    done = false;
                    if (p[i].rt > timeSlice) {
                        currentTime += timeSlice;
                        p[i].rt -= timeSlice;
                    } else {
                        currentTime += p[i].rt;
                        p[i].ct = currentTime;
                        p[i].tat = p[i].ct - p[i].at;
                        p[i].wt = p[i].tat - p[i].bt;
                        p[i].rt = 0;
                        completed++;
                    }
                } else if (!inQueue[i]) {
                    inQueue[i] = true;
                }
            }
        }
        if (done) {
            currentTime++;
        }
    }
}

void printResults(Process p[], int n) {
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
}

int main() {
    int n;
    Process p[MAX];

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input arrival times and burst times
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;  // Initialize remaining time for Round Robin
    }

    printf("\nFCFS Scheduling:\n");
    fcfs(p, n);
    printResults(p, n);

    // Reinitialize remaining times for Round Robin
    for (int i = 0; i < n; i++) {
        p[i].rt = p[i].bt;
    }

    printf("\nRound Robin Scheduling (Time Slice = %d ms):\n", TIME_SLICE);
    roundRobin(p, n);
    printResults(p, n);

    return 0;
}

/*
Input Example: 

Enter the number of processes: 5
Enter arrival time and burst time for each process:
Process 1: 0 10
Process 2: 1 5
Process 3: 2 8
Process 4: 3 6
Process 5: 4 4
*/