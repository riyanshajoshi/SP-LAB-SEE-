#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main() {
    // Step 1: Create Shared Memory Segment
    // IPC_PRIVATE creates a unique key automatically. 1024 is the size in bytes. 
    // 0666 gives read/write permissions.
    int shmid = shmget(IPC_PRIVATE, 1024, 0666 | IPC_CREAT);

    if (shmid < 0) {
        printf("Error: Failed to create shared memory.\n");
        return 1;
    }

    // Step 2: Fork to create Producer and Consumer processes
    pid_t pid = fork();

    if (pid < 0) {
        printf("Error: Fork failed.\n");
        return 1;
    } 
    else if (pid == 0) {
        // --- CHILD PROCESS (PRODUCER) ---
        
        // Attach to the shared memory segment
        char *str = (char*) shmat(shmid, NULL, 0);
        
        printf("PRODUCER (Child): Generating data...\n");
        strcpy(str, "Hello! This is a message from the Producer.");
        printf("PRODUCER (Child): Data successfully written to shared memory.\n");

        // Detach from shared memory (does not destroy it)
        shmdt(str);
    } 
    else {
        // --- PARENT PROCESS (CONSUMER) ---
        
        // Wait for the Producer (Child) to finish writing first
        wait(NULL); 
        
        // Attach to the same shared memory segment
        char *str = (char*) shmat(shmid, NULL, 0);
        
        printf("\nCONSUMER (Parent): Reading from shared memory...\n");
        printf("CONSUMER (Parent): Data read -> \"%s\"\n", str);

        // Detach from shared memory
        shmdt(str);
        
        // Destroy the shared memory completely
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}