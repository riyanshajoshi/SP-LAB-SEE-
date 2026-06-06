#include <stdio.h>

int main() {
    int ref_string[50], frames[10];
    int n, f, i, j, k, faults = 0, hit;

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

    // Step 3: Core Optimal Logic
    for(i = 0; i < n; i++) {
        hit = 0;

        // Check if the page is already in the frames (Page Hit)
        for(j = 0; j < f; j++) {
            if(frames[j] == ref_string[i]) {
                hit = 1;
                break;
            }
        }

        // If it is a Page Fault, we must find the Optimal page to replace
        if(hit == 0) {
            int pos = -1; // This will store the index of the frame we decide to replace

            // First, check if there is an empty frame available
            for(j = 0; j < f; j++) {
                if(frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // If frames are full, look into the FUTURE
            if(pos == -1) {
                int farthest = -1;
                
                for(j = 0; j < f; j++) {
                    int next_use = -1;
                    
                    // Look ahead in the reference string starting from tomorrow (i + 1)
                    for(k = i + 1; k < n; k++) {
                        if(frames[j] == ref_string[k]) {
                            next_use = k; // Found when this page will be used next
                            break;
                        }
                    }
                    
                    // The Ultimate Target: If the page is NEVER used again, replace it immediately!
                    if(next_use == -1) {
                        pos = j;
                        break;
                    }
                    
                    // Otherwise, find the page that is used farthest away in the future
                    if(next_use > farthest) {
                        farthest = next_use;
                        pos = j;
                    }
                }
            }

            frames[pos] = ref_string[i]; // Replace the chosen page
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