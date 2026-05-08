#include <stdio.h>

struct Task {
    int id, exe, period, deadline, rem;
};

int gcd(int a, int b) {
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int main() {
    struct Task t[10];
    int n, hp = 1;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        t[i].id = i + 1;

        printf("\nTask T%d\n", i + 1);

        printf("Execution Time: ");
        scanf("%d", &t[i].exe);

        printf("Period: ");
        scanf("%d", &t[i].period);

        printf("Deadline: ");
        scanf("%d", &t[i].deadline);

        t[i].rem = 0;

        hp = lcm(hp, t[i].period);
    }

    printf("\nGantt Chart:\n");

    for (int time = 0; time < hp; time++) {

        for (int i = 0; i < n; i++)
            if (time % t[i].period == 0)
                t[i].rem = t[i].exe;

        int sel = -1, min = 9999;

        for (int i = 0; i < n; i++) {
            if (t[i].rem > 0 && t[i].deadline < min) {
                min = t[i].deadline;
                sel = i;
            }
        }

        if (sel != -1) {
            printf("| T%d ", t[sel].id);
            t[sel].rem--;
        } else {
            printf("| IDLE ");
        }
    }

    printf("|\n");

    return 0;
}
