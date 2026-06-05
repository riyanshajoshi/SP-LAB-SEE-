#include <stdio.h>

int main() {
    int ref_string[50], frames[10];
    int n, f, i, j, faults = 0, pointer = 0, hit;

    // Step 1: Get user inputs
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference string (separated by spaces): ");
    for(i = 0; i < n; i++) {
        scanf("%d", &ref_string[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &f);

    // Step 2: Initialize empty frames with -1 
    for(i = 0; i < f; i++) {
        frames[i] = -1;
    }

    printf("\nPage\tFrames\t\tStatus\n");
    printf("--------------------------------------\n");

    // Step 3: Core FIFO Logic
    for(i = 0; i < n; i++) {
        hit = 0;

        // Check if the page is already in one of the frames (Page Hit)
        for(j = 0; j < f; j++) {
            if(frames[j] == ref_string[i]) {
                hit = 1;
                break;
            }
        }

        // If it is not in the frames (Page Fault), we must replace
        if(hit == 0) {
            frames[pointer] = ref_string[i];     // Insert page at the current pointer
            pointer = (pointer + 1) % f;         // Move pointer to the next oldest frame
            faults++;
        }

        // Step 4: Print the current state of the frames
        printf("%d\t", ref_string[i]);
        for(j = 0; j < f; j++) {
            if(frames[j] != -1) {
                printf("%d ", frames[j]);
            } else {
                printf("- ");
            }
        }
        
        if(hit == 1) {
            printf("\t\tHit\n");
        } else {
            printf("\t\tFault\n");
        }
    }

    // Step 5: Final Result
    printf("\nTotal Page Faults: %d\n", faults);

    return 0;
}