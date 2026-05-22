#include <stdio.h>
#include <stdbool.h>

struct Process {
    int id;
    int at; // Arrival Time
    int bt; // Burst Time
    int temp_bt; // Copy of burst time for preemptive tracking
    int ct; // Completion Time
    int tat; // Turnaround Time
    int wt; // Waiting Time
};

void calculateNonPreemptiveSJF(struct Process p[], int n) {
    int current_time = 0, completed = 0;
    bool is_completed[100] = {false};

    // Initialize metrics
    for(int i = 0; i < n; i++) p[i].ct = 0;

    while (completed != n) {
        int idx = -1;
        int min_bt = 1e9; // Initialize with a very large value

        // Find the process with the minimum burst time among arrived processes
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && !is_completed[i]) {
                if (p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    idx = i;
                }
                if (p[i].bt == min_bt) {
                    if (p[i].at < p[idx].at) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            current_time += p[idx].bt;
            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            is_completed[idx] = true;
            completed++;
        } else {
            current_time++; // CPU is idle
        }
    }
}

void calculatePreemptiveSJF(struct Process p[], int n) {
    int current_time = 0, completed = 0;
    int min_bt = 1e9;
    int shortest = 0;
    bool check = false;

    // Reset temporary burst times for preemptive logic
    for (int i = 0; i < n; i++) {
        p[i].temp_bt = p[i].bt;
    }

    while (completed != n) {
        // Find process with min remaining time at current millisecond
        for (int j = 0; j < n; j++) {
            if ((p[j].at <= current_time) && (p[j].temp_bt > 0) && (p[j].temp_bt < min_bt)) {
                min_bt = p[j].temp_bt;
                shortest = j;
                check = true;
            }
        }

        if (check == false) {
            current_time++;
            continue;
        }

        // Reduce remaining time by 1 unit
        p[shortest].temp_bt--;
        min_bt = p[shortest].temp_bt;
        if (min_bt == 0) min_bt = 1e9;

        // If a process finishes execution
        if (p[shortest].temp_bt == 0) {
            completed++;
            check = false;
            p[shortest].ct = current_time + 1;
            p[shortest].tat = p[shortest].ct - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;
            if (p[shortest].wt < 0) p[shortest].wt = 0;
        }
        current_time++;
    }
}

void printTable(struct Process p[], int n) {
    float total_tat = 0, total_wt = 0;
    printf("-------------------------------------------------------------\n");
    printf("| Process | Arrival Time | Burst Time | Completion | TAT | WT  |\n");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("|   P%-4d |      %-7d |     %-6d |     %-6d | %-3d | %-3d |\n",
               p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }
    printf("-------------------------------------------------------------\n");
    printf("Average Turnaround Time = %.2f\n", total_tat / n);
    printf("Average Waiting Time    = %.2f\n\n", total_wt / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    printf("\nEnter Arrival Time and Burst Time:\n");
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("P%d Arrival: ", i + 1);
        scanf("%d", &p[i].at);
        printf("P%d Burst: ", i + 1);
        scanf("%d", &p[i].bt);
    }

    printf("\n================ NON-PREEMPTIVE SJF ================\n");
    calculateNonPreemptiveSJF(p, n);
    printTable(p, n);

    printf("\n================== PREEMPTIVE SJF ==================\n");
    calculatePreemptiveSJF(p, n);
    printTable(p, n);

    return 0;
}
