#include <stdio.h>

// Structure to hold process details
struct Process {
    int id;  // Process ID
    int at;  // Arrival Time
    int bt;  // Burst Time
    int ct;  // Completion Time
    int tat; // Turnaround Time
    int wt;  // Waiting Time
    int rt;  // Response Time
};

int main() {
    int n, i, j;
    float total_tat = 0, total_wt = 0, total_rt = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n], temp;

    // 1. Get User Input
    printf("\nEnter Arrival Time and Burst Time for each process:\n");
    for (i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Process P%d - Arrival Time: ", p[i].id);
        scanf("%d", &p[i].at);
        printf("Process P%d - Burst Time: ", p[i].id);
        scanf("%d", &p[i].bt);
        printf("\n");
    }

    // 2. Sort processes by Arrival Time (FCFS order)
    // Using a simple Bubble Sort
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // 3. FCFS Scheduling Calculations
    int current_time = 0;
    for (i = 0; i < n; i++) {
        // If the CPU is idle because the next process hasn't arrived yet
        if (current_time < p[i].at) {
            current_time = p[i].at;
        }

        // Response Time = Time when execution starts - Arrival Time
        p[i].rt = current_time - p[i].at;

        // Completion Time = Start time + Burst Time
        p[i].ct = current_time + p[i].bt;

        // Advance current time clock
        current_time = p[i].ct;

        // Turnaround Time = Completion Time - Arrival Time
        p[i].tat = p[i].ct - p[i].at;

        // Waiting Time = Turnaround Time - Burst Time
        p[i].wt = p[i].tat - p[i].bt;

        // Accumulate totals for averages
        total_tat += p[i].tat;
        total_wt += p[i].wt;
        total_rt += p[i].rt;
    }

    // 4. Display the results in a table
    printf("---------------------------------------------------------------------------------\n");
    printf("| Process | Arrival Time | Burst Time | Completion | Turnaround | Waiting | Response |\n");
    printf("---------------------------------------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("|   P%-4d |      %-7d |     %-6d |     %-6d |     %-6d |    %-4d |    %-5d |\n",
               p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }
    printf("---------------------------------------------------------------------------------\n");

    // 5. Display Averages
    printf("\nAverage Turnaround Time = %.2f", total_tat / n);
    printf("\nAverage Waiting Time    = %.2f", total_wt / n);
    printf("\nAverage Response Time   = %.2f\n", total_rt / n);

    return 0;
}
