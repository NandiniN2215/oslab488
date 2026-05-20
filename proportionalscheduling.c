#include <stdio.h>

struct Process
{
    int pid;
    int burstTime;
    int weight;
    float proportion;
    float cpuTime;
};

int main()
{
    int n, totalWeight = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input process details
    for(int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        printf("\nEnter Burst Time for Process P%d: ", p[i].pid);
        scanf("%d", &p[i].burstTime);

        printf("Enter Weight/Priority for Process P%d: ", p[i].pid);
        scanf("%d", &p[i].weight);

        totalWeight += p[i].weight;
    }

    // Calculate proportional CPU share
    for(int i = 0; i < n; i++)
    {
        p[i].proportion = (float)p[i].weight / totalWeight;

        p[i].cpuTime = p[i].proportion * 100;
    }

    // Display result
    printf("\n===== Proportional Scheduling =====\n");

    printf("\nPID\tBurst Time\tWeight\tCPU Share(%%)\tAllocated CPU Time\n");

    for(int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t\t%d\t%.2f\t\t%.2f\n",
               p[i].pid,
               p[i].burstTime,
               p[i].weight,
               p[i].proportion * 100,
               p[i].cpuTime);
    }

    return 0;
}
