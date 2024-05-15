// 11.	Write a program to implement following CPU scheduling algorithms:
// 1)	Priority –Non preemptive
// 2)	Round Robin – time slice=4ms


#include <iostream>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <string.h>
using namespace std;

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority; // For Priority Scheduling
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

bool compare_arrival_time(process p1, process p2) {
    return p1.arrival_time < p2.arrival_time;
}

bool compare_pid(process p1, process p2) {
    return p1.pid < p2.pid;
}

int main() {
    int choice;
    cout << "Choose the scheduling algorithm:" << endl;
    cout << "1. Priority Scheduling" << endl;
    cout << "2. Round Robin Scheduling" << endl;
    cin >> choice;

    int n, tq;
    struct process p[100];
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    float cpu_utilisation;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    int total_idle_time = 0;
    int burst_remaining[100];
    int idx;

    cout << setprecision(2) << fixed;

    cout << "Enter the number of processes: ";
    cin >> n;

    if (choice == 2) {
        cout << "Enter time quantum: ";
        cin >> tq;
    }

    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time of process " << i + 1 << ": ";
        cin >> p[i].arrival_time;
        cout << "Enter burst time of process " << i + 1 << ": ";
        cin >> p[i].burst_time;
        if (choice == 1) {
            cout << "Enter priority of the process " << i + 1 << ": ";
            cin >> p[i].priority;
        }
        burst_remaining[i] = p[i].burst_time;
        p[i].pid = i + 1;
        cout << endl;
    }

    if (choice == 1) {
        sort(p, p + n, compare_arrival_time);

        int current_time = 0;
        int completed = 0;

        while (completed != n) {
            int idx = -1;
            int mx = -1;
            for (int i = 0; i < n; i++) {
                if (p[i].arrival_time <= current_time && burst_remaining[i] > 0) {
                    if (p[i].priority > mx) {
                        mx = p[i].priority;
                        idx = i;
                    }
                }
            }
            if (idx != -1) {
                p[idx].start_time = current_time;
                p[idx].completion_time = p[idx].start_time + burst_remaining[idx];
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

                total_turnaround_time += p[idx].turnaround_time;
                total_waiting_time += p[idx].waiting_time;
                total_response_time += p[idx].response_time;

                current_time = p[idx].completion_time;
                burst_remaining[idx] = 0;
                completed++;
            } else {
                current_time++;
            }
        }
    } else if (choice == 2) {
        sort(p, p + n, compare_arrival_time);

        queue<int> q;
        int current_time = 0;
        q.push(0);
        int completed = 0;
        int mark[100];
        memset(mark, 0, sizeof(mark));
        mark[0] = 1;

        while (completed != n) {
            idx = q.front();
            q.pop();

            if (burst_remaining[idx] == p[idx].burst_time) {
                p[idx].start_time = max(current_time, p[idx].arrival_time);
                total_idle_time += p[idx].start_time - current_time;
                current_time = p[idx].start_time;
            }

            if (burst_remaining[idx] - tq > 0) {
                burst_remaining[idx] -= tq;
                current_time += tq;
            } else {
                current_time += burst_remaining[idx];
                burst_remaining[idx] = 0;
                completed++;

                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

                total_turnaround_time += p[idx].turnaround_time;
                total_waiting_time += p[idx].waiting_time;
                total_response_time += p[idx].response_time;
            }

            for (int i = 0; i < n; i++) {
                if (burst_remaining[i] > 0 && p[i].arrival_time <= current_time && mark[i] == 0) {
                    q.push(i);
                    mark[i] = 1;
                }
            }
            if (burst_remaining[idx] > 0) {
                q.push(idx);
            }

            if (q.empty()) {
                for (int i = 0; i < n; i++) {
                    if (burst_remaining[i] > 0) {
                        q.push(i);
                        mark[i] = 1;
                        break;
                    }
                }
            }
        }
    }

    avg_turnaround_time = (float)total_turnaround_time / n;
    avg_waiting_time = (float)total_waiting_time / n;
    avg_response_time = (float)total_response_time / n;
    cpu_utilisation = ((p[n - 1].completion_time - total_idle_time) / (float)p[n - 1].completion_time) * 100;

    sort(p, p + n, compare_pid);

    cout << endl;
    cout << "#P\t" << "AT\t" << "BT\t" << "PRI\t" << "ST\t" << "CT\t" << "TAT\t" << "WT\t" << "RT\t" << "\n" << endl;

    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t" << p[i].priority << "\t" << p[i].start_time << "\t" << p[i].completion_time << "\t" << p[i].turnaround_time << "\t" << p[i].waiting_time << "\t" << p[i].response_time << "\t" << "\n" << endl;
    }
    cout << "Average Turnaround Time = " << avg_turnaround_time << endl;
    cout << "Average Waiting Time = " << avg_waiting_time << endl;
    cout << "Average Response Time = " << avg_response_time << endl;
    cout << "CPU Utilization = " << cpu_utilisation << "%" << endl;
}
