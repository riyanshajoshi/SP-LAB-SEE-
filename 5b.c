#include <stdio.h>

int main() {
    int ref_string[50], frames[10], time[10];
    int n, f, i, j, faults = 0, counter = 0, hit;

    // Step 1: Get user inputs
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference string (separated by spaces): ");
    for(i = 0; i < n; i++) {
        scanf("%d", &ref_string[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &f);

    // Step 2: Initialize frames and their last used time
    for(i = 0; i < f; i++) {
        frames[i] = -1;
        time[i] = 0; // 0 means it has never been used
    }

    printf("\nPage\tFrames\t\tStatus\n");
    printf("--------------------------------------\n");

    // Step 3: Core LRU Logic
    for(i = 0; i < n; i++) {
        hit = 0;

        // Check if the page is already in the frames (Page Hit)
        for(j = 0; j < f; j++) {
            if(frames[j] == ref_string[i]) {
                hit = 1;
                counter++;            // Global clock ticks forward
                time[j] = counter;    // Update this frame's time to show it was JUST used
                break;
            }
        }

        // If it is not in the frames (Page Fault), we must replace the LRU
        if(hit == 0) {
            int pos = 0;
            int min_time = time[0];

            // Find the frame with the absolute smallest time (the oldest/least recently used)
            for(j = 1; j < f; j++) {
                if(time[j] < min_time) {
                    min_time = time[j];
                    pos = j;
                }
            }

            frames[pos] = ref_string[i]; // Replace the oldest page
            counter++;                   // Global clock ticks forward
            time[pos] = counter;         // Update its time to the present
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