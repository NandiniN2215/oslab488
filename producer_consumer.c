#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 5 // Total capacity of the buffer
#define MAX_ITEMS 10  // Number of items each thread will produce/consume

int buffer[BUFFER_SIZE];
int in = 0;  // Index where the producer inserts the next item
int out = 0; // Index from which the consumer removes the next item

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

// Producer thread function
void* producer(void* pno) {
    int item;
    for(int i = 0; i < MAX_ITEMS; i++) {
        item = rand() % 100; // Produce a random item

        // Wait for an empty slot
        sem_wait(&empty);
        // Lock the buffer to ensure exclusive access
        pthread_mutex_lock(&mutex);

        // Critical Section: Insert item into buffer
        buffer[in] = item;
        printf("Producer %d: Inserted Item %d at index %d\n", *((int *)pno), item, in);
        in = (in + 1) % BUFFER_SIZE; // Circular buffer increment

        // Unlock the buffer
        pthread_mutex_unlock(&mutex);
        // Signal that a slot has been filled
        sem_post(&full);

        sleep(1); // Sleep to simulate processing time
    }
    return NULL;
}

// Consumer thread function
void* consumer(void* cno) {
    for(int i = 0; i < MAX_ITEMS; i++) {
        // Wait for a full slot
        sem_wait(&full);
        // Lock the buffer to ensure exclusive access
        pthread_mutex_lock(&mutex);

        // Critical Section: Remove item from buffer
        int item = buffer[out];
        printf("Consumer %d: Removed Item %d from index %d\n", *((int *)cno), item, out);
        out = (out + 1) % BUFFER_SIZE; // Circular buffer increment

        // Unlock the buffer
        pthread_mutex_unlock(&mutex);
        // Signal that a slot is now empty
        sem_post(&empty);

        sleep(2); // Sleep to simulate processing time
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;
    int a[1] = {1}; // Thread IDs for identification

    // Initialize Semaphores
    // sem_init(&semaphore, shared_between_threads, initial_value)
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create Producer and Consumer threads
    pthread_create(&prod_thread, NULL, producer, (void *)&a[0]);
    pthread_create(&cons_thread, NULL, consumer, (void *)&a[0]);

    // Wait for threads to finish execution
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Cleanup and destroy semaphores/mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
