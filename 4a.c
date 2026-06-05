#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int global_var = 10; // Global variable

int main() {
    int local_var = 20; // Local variable
    pid_t pid;

    printf("Before fork: Global = %d, Local = %d\n", global_var, local_var);

    // Create a new process
    pid = fork(); 

    if (pid < 0) {
        // Fork failed
        printf("Error: Fork failed.\n");
        return 1;
    } 
    else if (pid == 0) {
        // --- CHILD PROCESS ---
        printf("\n--- Inside Child Process ---\n");
        printf("Child PID: %d, Parent PID: %d\n", getpid(), getppid());
        
        // Modifying variables in the child process
        global_var += 5;
        local_var += 5;
        
        printf("Child Modified Values -> Global = %d, Local = %d\n", global_var, local_var);
    } 
    else {
        // --- PARENT PROCESS ---
        wait(NULL); // Wait for the child process to finish before continuing
        
        printf("\n--- Inside Parent Process ---\n");
        printf("Parent PID: %d, Child PID: %d\n", getpid(), pid);
        
        // Proving that parent's variables remain completely unchanged
        printf("Parent Original Values -> Global = %d, Local = %d\n", global_var, local_var);
    }

    return 0;
}