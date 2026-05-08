#include <stdio.h>

#define MAX_TASKS 10
#define MAX_TIME 100

typedef struct {
    int id;
    int execution;
    int period;
    int remaining;
    int deadline;
} Task;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int main() {
    Task tasks[MAX_TASKS];
    int n, hyperPeriod = 1;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;

        printf("\nTask T%d\n", i + 1);

        printf("Execution Time: ");
        scanf("%d", &tasks[i].execution);

        printf("Period: ");
        scanf("%d", &tasks[i].period);

        tasks[i].remaining = 0;
        tasks[i].deadline = tasks[i].period;

        hyperPeriod = lcm(hyperPeriod, tasks[i].period);
    }

    printf("\nHyper Period = %d\n", hyperPeriod);

    printf("\nGantt Chart:\n");
    printf("--------------------------------------------------\n");

    for (int time = 0; time < hyperPeriod; time++) {

        for (int i = 0; i < n; i++) {
            if (time % tasks[i].period == 0) {
                tasks[i].remaining = tasks[i].execution;
                tasks[i].deadline = time + tasks[i].period;
            }
        }

        int selected = -1;
        int minPeriod = 9999;

        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining > 0 &&
                tasks[i].period < minPeriod) {

                minPeriod = tasks[i].period;
                selected = i;
            }
        }

        if (selected != -1) {
            printf("| T%d ", tasks[selected].id);
            tasks[selected].remaining--;
        } else {
            printf("| IDLE ");
        }
    }

    printf("|\n");
    printf("--------------------------------------------------\n");

    printf("0");
    for (int i = 1; i <= hyperPeriod; i++) {
        printf("    %d", i);
    }

    printf("\n");

    return 0;
}

