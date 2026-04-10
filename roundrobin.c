#include <stdio.h>

int main() {
    int n, i, time = 0, remain = 0, tq, done;
    float avg_wt = 0, avg_tat = 0, avg_rt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], rt[n], ct[n], tat[n], wt[n], response[n], first[n];

    for(i = 0; i < n; i++) {
        printf("Enter arrival time for P%d: ", i+1);
        scanf("%d", &at[i]);
        printf("Enter burst time for P%d: ", i+1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
        first[i] = -1;
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    remain = n;

    printf("\nGantt Chart:\n|");

    while(remain > 0) {
        done = 1;
        for(i = 0; i < n; i++) {
            if(rt[i] > 0 && at[i] <= time) {
                done = 0;

                if(first[i] == -1)
                    first[i] = time;

                if(rt[i] <= tq) {
                    time += rt[i];
                    printf(" P%d |", i+1);
                    rt[i] = 0;
                    ct[i] = time;
                    remain--;
                } else {
                    time += tq;
                    rt[i] -= tq;
                    printf(" P%d |", i+1);
                }
            }
        }

        if(done)
            time++;
    }

    for(i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        response[i] = first[i] - at[i];

        avg_wt += wt[i];
        avg_tat += tat[i];
        avg_rt += response[i];
    }

    avg_wt /= n;
    avg_tat /= n;
    avg_rt /= n;

    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], ct[i], tat[i], wt[i], response[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f", avg_tat);
    printf("\nAverage Response Time = %.2f\n", avg_rt);

    return 0;
}
