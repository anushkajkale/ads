#include<stdio.h>
#include<stdlib.h>

// Structure to represent a process in Round Robin
typedef struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int turnaround_time;
    int waiting_time;
} Process;

// Function to implement Round Robin CPU scheduling algorithm
void roundRobin(Process *processes, int num_processes, int time_slice) {
    int remaining_processes = num_processes;
    int current_time = 0;
    int quantum_time = time_slice;
    int i, j;

    printf("Process\tTurnaround Time\tWaiting Time\n");

    while(remaining_processes > 0) {
        for(i = 0; i < num_processes; i++) {
            if(processes[i].remaining_time > 0) {
                if(processes[i].remaining_time <= quantum_time) {
                    current_time += processes[i].remaining_time;
                    quantum_time -= processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                } else {
                    current_time += quantum_time;
                    processes[i].remaining_time -= quantum_time;
                    quantum_time = 0;
                }

                if(processes[i].remaining_time == 0) {
                    remaining_processes--;
                    processes[i].turnaround_time = current_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    printf("%d\t%d\t\t%d\n", processes[i].process_id, processes[i].turnaround_time, processes[i].waiting_time);
                }
            }
        }

        // Reset quantum time for the next iteration
        quantum_time = time_slice;
    }

    float total_waiting_time = 0, total_turnaround_time = 0;
    for(i = 0; i < num_processes; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    float avg_waiting_time = total_waiting_time / num_processes;
    float avg_turnaround_time = total_turnaround_time / num_processes;
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

// Function to implement FIFO page replacement algorithm
void fifoPageReplacement(int *page_reference_string, int num_pages, int num_frames) {
    int frames[num_frames], page_faults = 0, i, j, k = 0;
    for(i = 0; i < num_frames; i++) {
        frames[i] = -1; // Initialize frames with -1 indicating empty frame
    }

    printf("Page\t  Frames\n");
    for(i = 0; i < num_pages; i++) {
        printf("%d\t", page_reference_string[i]);
        if(!findPage(page_reference_string[i], frames, num_frames)) {
            frames[k] = page_reference_string[i];
            k = (k + 1) % num_frames;
            page_faults++;
            for(j = 0; j < num_frames; j++) {
                printf("%d\t", frames[j]);
            }
            printf("PF\n");
        } else {
            for(j = 0; j < num_frames; j++) {
                printf("%d\t", frames[j]);
            }
            printf("\n");
        }
    }
    printf("Total Page Faults: %d\n", page_faults);
}

// Function to find if page is present in frames
int findPage(int page, int *frames, int num_frames) {
    for(int i = 0; i < num_frames; i++) {
        if(frames[i] == page)
            return 1;
    }
    return 0;
}

int main() {
    // Round Robin Scheduling
    int num_processes;
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);
    Process processes[num_processes];
    printf("Enter arrival time and burst time for each process:\n");
    for(int i = 0; i < num_processes; i++) {
        printf("Process %d: ", i+1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].process_id = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }
    int time_slice = 4;
    roundRobin(processes, num_processes, time_slice);

    // FIFO Page Replacement
    int num_pages = 20; // number of pages in reference string
    int page_reference_string[] = {7, 1, 0, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int num_frames = 3; // number of frames
    fifoPageReplacement(page_reference_string, num_pages, num_frames);

    return 0;
}
