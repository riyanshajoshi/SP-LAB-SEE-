#include <stdio.h>

int main() {
    int n, m, i, j, k;
    int alloc[10][10], max[10][10], need[10][10], avail[10];
    int f[10] = {0}, ans[10], ind = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    // Step 1: Input Allocation Matrix
    printf("\nEnter Allocation Matrix row-by-row:\n");
    for (i = 0; i < n; i++) {
        printf("Process P%d: ", i);
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Step 2: Input Max Matrix
    printf("\nEnter Max Matrix row-by-row:\n");
    for (i = 0; i < n; i++) {
        printf("Process P%d: ", i);
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Step 3: Input Available Resources
    printf("\nEnter Available Resources (separated by spaces): ");
    for (j = 0; j < m; j++) {
        scanf("%d", &avail[j]);
    }

    // Step 4: Calculate NEED Matrix (Max - Allocation)
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Step 5: Core Safety Algorithm Logic
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            if (f[i] == 0) { // If process is not finished
                int flag = 0;
                
                // Check if Need <= Available
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1; // Cannot allocate
                        break;
                    }
                }

                // If resources can be safely allocated
                if (flag == 0) {
                    ans[ind++] = i; // Save process to sequence
                    for (j = 0; j < m; j++) {
                        avail[j] += alloc[i][j]; // Release allocated resources back
                    }
                    f[i] = 1; // Mark process as finished
                }
            }
        }
    }

    // Step 6: Verify if all processes successfully finished
    int safe = 1;
    for (i = 0; i < n; i++) {
        if (f[i] == 0) {
            safe = 0;
            printf("\nError: System is in a DEADLOCK state.\n");
            break;
        }
    }

    if (safe == 1) {
        printf("\nSuccess: System is in a SAFE state.\nSafe Sequence: ");
        for (i = 0; i < n - 1; i++) {
            printf("P%d -> ", ans[i]);
        }
        printf("P%d\n", ans[n - 1]);
    }

    return 0;
}