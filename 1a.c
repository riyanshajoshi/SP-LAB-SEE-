#include <stdio.h>

int main() {
    int disk[50] = {0}; // Represents 50 disk blocks, initialized to 0 (free)
    int start, len, i, choice;

    do {
        printf("\nEnter the starting block and length of the file: ");
        scanf("%d %d", &start, &len);

        int is_free = 1; // Flag to check if space is available

        // Step 1: Check if all contiguous blocks are free
        for (i = start; i < (start + len); i++) {
            if (disk[i] == 1) {
                is_free = 0; // Found an allocated block
                break;
            }
        }

        // Step 2: Allocate if space is free, otherwise reject
        if (is_free == 1) {
            for (i = start; i < (start + len); i++) {
                disk[i] = 1; // Mark block as allocated
                printf("Block %d -> Allocated\n", i);
            }
            printf("Success: File allocated contiguously.\n");
        } else {
            printf("Error: Contiguous blocks are not available. Allocation failed.\n");
        }

        // Step 3: Ask user if they want to continue
        printf("\nDo you want to allocate another file? (1 for Yes, 0 for Exit): ");
        scanf("%d", &choice);

    } while (choice == 1);

    return 0;
}