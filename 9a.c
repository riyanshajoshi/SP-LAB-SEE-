#include <stdio.h>

int main() {
    int b[10], p[10], alloc[10], b_cnt, p_cnt, i, j;

    printf("Enter number of memory blocks: ");
    scanf("%d", &b_cnt);
    printf("Enter sizes of the %d blocks: ", b_cnt);
    for(i = 0; i < b_cnt; i++) scanf("%d", &b[i]);

    printf("Enter number of processes: ");
    scanf("%d", &p_cnt);
    printf("Enter sizes of the %d processes: ", p_cnt);
    for(i = 0; i < p_cnt; i++) {
        scanf("%d", &p[i]);
        alloc[i] = -1; // Initialize all allocations to -1 (Not Allocated)
    }

    // Core First-Fit Logic
    for(i = 0; i < p_cnt; i++) { // For every process
        for(j = 0; j < b_cnt; j++) { // Check every block from the start
            if(b[j] >= p[i]) {       // If the block is big enough
                alloc[i] = j;        // Assign block to process
                b[j] -= p[i];        // Reduce the available size of the block
                break;               // Jump to the next process!
            }
        }
    }

    // Print Results
    printf("\nProcess\tSize\tBlock Allocated\n");
    for(i = 0; i < p_cnt; i++) {
        if(alloc[i] != -1) {
            printf("P%d\t%d\tBlock %d\n", i + 1, p[i], alloc[i] + 1);
        } else {
            printf("P%d\t%d\tNot Allocated\n", i + 1, p[i]);
        }
    }

    return 0;
}