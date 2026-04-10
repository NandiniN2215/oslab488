#include <stdio.h>

struct Process {
    int pid, at, bt, pr, ct, tat, wt, rt, done;
};

int main() {
    int n, time = 0, completed = 0;
    float avg_tat = 0, avg_wt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    int gantt[100], gtime[100], k = 0;

    for(int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nProcess %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Priority: ");
        scanf("%d", &p[i].pr);
        p[i].done = 0;
    }

    while(completed < n) {
        int idx = -1, hp = 9999;

        for(int i = 0; i < n; i++) {
            if(p[i].at <= time && p[i].done == 0) {
                if(p[i].pr < hp || (p[i].pr == hp && p[i].at < p[idx].at)) {
                    hp = p[i].pr;
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            gtime[k] = time;
            gantt[k++] = p[idx].pid;

            p[idx].rt = time - p[idx].at;
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].done = 1;

            avg_tat += p[idx].tat;
            avg_wt += p[idx].wt;
            completed++;
        } else {
            time++;
        }
    }

    gtime[k] = time;

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].pid, p[i].at, p[i].bt, p[i].pr,
        p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("\nGantt Chart:\n");
    for(int i = 0; i < k; i++) {
        printf("| P%d ", gantt[i]);
    }
    printf("|\n");

    for(int i = 0; i <= k; i++) {
        printf("%d   ", gtime[i]);
    }

    printf("\n\nAverage TAT = %.2f", avg_tat/n);
    printf("\nAverage WT = %.2f\n", avg_wt/n);

    return 0;
}
