#include <stdio.h>

int main() {
    int n, i, quantum, time = 0, remain;
    int bt[10], rt[10]; // Burst Time and Remaining Time arrays
    int total_wt = 0, total_tat = 0;

    printf("Enter number of processes (max 10): ");
    scanf("%d", &n);
    remain = n; // Keep track of how many processes are left to finish

    // Step 1: Get Burst Times and initialize Remaining Times
    for(i = 0; i < n; i++) {
        printf("Enter Burst Time for P%d (in ms): ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i]; // Initially, Remaining Time == Burst Time
    }

    printf("Enter Time Quantum (in ms): ");
    scanf("%d", &quantum);

    printf("\nProcess\tBT\tTAT\tWT\n");
    printf("----------------------------------\n");

    // Step 2: The Core Round-Robin Loop
    while(remain != 0) {
        for(i = 0; i < n; i++) {
            if(rt[i] > 0) { // If the process is not finished yet
                
                // Condition A: The process can finish in this round
                if(rt[i] <= quantum) {
                    time += rt[i];        // Advance global clock by the remaining time
                    rt[i] = 0;            // Process is now finished
                    remain--;             // One less process to worry about

                    // Calculate metrics since the process just finished
                    int tat = time;       // Turnaround Time = Completion Time (since Arrival = 0)
                    int wt = time - bt[i]; // Waiting Time = TAT - Burst Time

                    total_tat += tat;
                    total_wt += wt;

                    printf("P%d\t%dms\t%dms\t%dms\n", i + 1, bt[i], tat, wt);
                } 
                // Condition B: The process needs more time than the quantum allows
                else {
                    time += quantum;      // Advance global clock by the full quantum
                    rt[i] -= quantum;     // Subtract the quantum from the remaining time
                }
            }
        }
    }

    // Step 3: Print Averages
    printf("\nAverage Turnaround Time: %.2f ms\n", (float)total_tat / n);
    printf("Average Waiting Time: %.2f ms\n", (float)total_wt / n);

    return 0;
}