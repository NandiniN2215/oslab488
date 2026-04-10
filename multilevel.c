 #include <stdio.h>

struct process {
    int pid;
    int type; // 0 = System, 1 = User
    int at, bt;
    int ct, wt, tat, rt;
    int started;
};

int main() {
    int n, i, j;

    printf("Enter total number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    // Input
    for(i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        p[i].pid = i + 1;

        printf("Enter type (0 = System, 1 = User): ");
        scanf("%d", &p[i].type);

        printf("Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        p[i].started = 0;
    }

    // Sort by type (System first), then by arrival time
    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(p[j].type > p[j+1].type ||
              (p[j].type == p[j+1].type && p[j].at > p[j+1].at)) {

                struct process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    int time = 0;

    for(i = 0; i < n; i++) {

        // If CPU is idle, jump to arrival time
        if(time < p[i].at)
            time = p[i].at;

        // Response time (first execution)
        p[i].rt = time - p[i].at;

        // Execute process
        time += p[i].bt;

        // Completion time
        p[i].ct = time;

        // Turnaround time
        p[i].tat = p[i].ct - p[i].at;

        // Waiting time
        p[i].wt = p[i].tat - p[i].bt;
    }
    printf("\nGantt Chart:\n\n");

// Top bar
printf(" ");
for(i = 0; i < n; i++) {
    printf("--------");
}
printf("\n|");

// Process IDs
for(i = 0; i < n; i++) {
    printf("  P%d   |", p[i].pid);
}

// Bottom bar
printf("\n ");
for(i = 0; i < n; i++) {
    printf("--------");
}

// Time line
printf("\n%d", (p[0].at > 0) ? p[0].at : 0);

for(i = 0; i < n; i++) {
    printf("      %d", p[i].ct);
}
printf("\n");

    // Output
    float total_wt = 0, total_tat = 0;

    printf("\nPID\tType\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(i = 0; i < n; i++) {
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               (p[i].type == 0) ? "SYS" : "USR",
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].tat,
               p[i].wt,
               p[i].rt);

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
