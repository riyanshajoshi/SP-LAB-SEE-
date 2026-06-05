#include <stdio.h>
#include <stdlib.h>

int main() {
    int disk[50] = {0}; // 0 means free, 1 means allocated
    int start, len, choice, i;

    do {
        printf("\nEnter starting block and length of the file: ");
        scanf("%d %d", &start, &len);

        // Step 1: Check if the requested starting block is free
        if (disk[start] == 1) {
            printf("Error: Starting block %d is already in use.\n", start);
        } else {
            int current = start;
            disk[current] = 1; // Mark start block as allocated
            printf("Block %d -> Allocated (Start)\n", current);
            
            int allocated_blocks = 1;
            
            // Step 2: Find remaining blocks anywhere on the disk and link them
            for (i = 0; i < 50 && allocated_blocks < len; i++) {
                if (disk[i] == 0) { // Found a free block
                    disk[i] = 1;    // Allocate it
                    printf("Block %d -> Linked to Block %d\n", current, i);
                    current = i;    // The new block becomes our current block
                    allocated_blocks++;
                }
            }

            // Step 3: Verify if we found enough space
            if (allocated_blocks == len) {
                printf("Success: File allocated using Linked Allocation.\n");
            } else {
                printf("Error: Disk is full. Could not allocate the entire file.\n");
            }
        }

        printf("\nDo you want to allocate another file? (1 for Yes, 0 for Exit): ");
        scanf("%d", &choice);

    } while (choice == 1);

    return 0;
}