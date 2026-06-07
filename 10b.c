#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, wrt;
int read_count = 0;
int data = 1; // The shared resource

void *reader(void *arg) {
    int id = *(int*)arg;

    sem_wait(&mutex); // Lock to update read_count safely
    read_count++;
    if (read_count == 1) {
        sem_wait(&wrt); // If I am the FIRST reader, lock out all writers
    }
    sem_post(&mutex);

    // Critical Section: Reading
    printf("Reader %d is reading data: %d\n", id, data);
    sleep(1);

    sem_wait(&mutex); // Lock to update read_count safely
    read_count--;
    if (read_count == 0) {
        sem_post(&wrt); // If I am the LAST reader leaving, unlock writers
    }
    sem_post(&mutex);
    
    return NULL;
}

void *writer(void *arg) {
    int id = *(int*)arg;

    sem_wait(&wrt); // Lock the resource for exclusive writing
    
    // Critical Section: Writing
    data *= 2; 
    printf("Writer %d modified data to: %d\n", id, data);
    sleep(1);
    
    sem_post(&wrt); // Unlock the resource
    
    return NULL;
}

int main() {
    pthread_t r[3], w[2];
    int id[3] = {1, 2, 3};
    int i;

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    // Create 2 Writers and 3 Readers
    for(i = 0; i < 2; i++) pthread_create(&w[i], NULL, writer, &id[i]);
    for(i = 0; i < 3; i++) pthread_create(&r[i], NULL, reader, &id[i]);

    // Wait for threads to finish
    for(i = 0; i < 2; i++) pthread_join(w[i], NULL);
    for(i = 0; i < 3; i++) pthread_join(r[i], NULL);

    return 0;
}