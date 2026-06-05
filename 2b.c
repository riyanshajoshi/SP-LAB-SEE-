#include <stdio.h>

int main() {
    int n, i;
    int at[10], bt[10], rt[10]; // Arrival Time, Burst Time, Remaining Time
    int time = 0, completed = 0, shortest = -1, min_rt;
    int ct, tat, wt, total_tat = 0, total_wt = 0;

    printf("Enter number of processes (max 10): ");
    scanf("%d", &n);

    // Step 1: Get inputs (Updated prompt to ask for ms)
    for (i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for P%d (in ms): ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i]; // Initially, Remaining Time == Burst Time
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    // Step 2: The Global Clock Loop
    while (completed != n) {
        shortest = -1;
        min_rt = 9999; // Reset to a very high number every second

        // Step 2a: Find the available process with the absolute shortest remaining time
        for (i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0 && rt[i] < min_rt) {
                min_rt = rt[i];
                shortest = i;
            }
        }

        // Step 2b: If no process has arrived yet, just advance the clock
        if (shortest == -1) {
            time++;
            continue;
        }

        // Step 2c: Process the chosen job for 1 ms
        rt[shortest]--;
        time++;

        // Step 2d: If the process finishes, calculate its metrics
        if (rt[shortest] == 0) {
            completed++;
            ct = time;                     // Completion Time is the current clock time
            tat = ct - at[shortest];       // Turnaround Time = CT - AT
            wt = tat - bt[shortest];       // Waiting Time = TAT - BT
            
            total_tat += tat;
            total_wt += wt;

            // Updated this line to print "ms" directly next to the calculated numbers
            printf("P%d\t%dms\t%dms\t%dms\t%dms\t%dms\n", shortest + 1, at[shortest], bt[shortest], ct, tat, wt);
        }
    }

    // Step 3: Print Averages (Updated to include ms)
    printf("\nAverage Turnaround Time: %.2f ms\n", (float)total_tat / n);
    printf("Average Waiting Time: %.2f ms\n", (float)total_wt / n);

    return 0;
}