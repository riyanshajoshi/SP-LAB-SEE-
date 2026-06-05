#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX 20

int n; // Number of philosophers
sem_t forks[MAX];

void* philosopher(void* num) {
    int id = *(int*)num;
    int left = id;
    int right = (id + 1) % n;

    printf("Philosopher %d is thinking...\n", id);

    // Deadlock Avoidance: Even IDs pick left fork first, Odd IDs pick right fork first
    if (id % 2 == 0) {
        sem_wait(&forks[left]);
        sem_wait(&forks[right]);
    } else {
        sem_wait(&forks[right]);
        sem_wait(&forks[left]);
    }

    printf("-> Philosopher %d is EATING (using forks %d & %d).\n", id, left, right);
    sleep(1); // Simulate time taken to eat

    printf("Philosopher %d finished eating and put down forks.\n", id);
    
    // Release the forks
    sem_post(&forks[left]);
    sem_post(&forks[right]);

    return NULL;
}

int main() {
    pthread_t threads[MAX];
    int phil_ids[MAX];
    int i;

    printf("Enter the number of philosophers (e.g., 5): ");
    scanf("%d", &n);

    // Step 1: Initialize semaphores (forks) with a value of 1 (available)
    for (i = 0; i < n; i++) {
        sem_init(&forks[i], 0, 1);
        phil_ids[i] = i;
    }

    // Step 2: Create philosopher threads
    for (i = 0; i < n; i++) {
        pthread_create(&threads[i], NULL, philosopher, &phil_ids[i]);
    }

    // Step 3: Wait for all threads to finish executing
    for (i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    // Step 4: Destroy semaphores to free resources
    for (i = 0; i < n; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}