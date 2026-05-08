#include <stdio.h>

#define N 5

int state[N]; // 0 = Thinking, 1 = Hungry, 2 = Eating

void test(int i) {
    if (state[i] == 1 &&
        state[(i + 4) % N] != 2 &&
        state[(i + 1) % N] != 2) {

        state[i] = 2;
        printf("Philosopher %d is Eating\n", i + 1);
    }
}

void take_fork(int i) {
    state[i] = 1;

    printf("Philosopher %d is Hungry\n", i + 1);

    test(i);
}

void put_fork(int i) {
    state[i] = 0;

    printf("Philosopher %d is Thinking\n", i + 1);

    test((i + 4) % N);
    test((i + 1) % N);
}

int main() {

    for (int i = 0; i < N; i++)
        state[i] = 0;

    for (int i = 0; i < N; i++) {
        take_fork(i);
        put_fork(i);
    }

    return 0;
}
