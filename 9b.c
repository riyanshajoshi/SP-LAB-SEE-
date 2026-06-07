#include <stdio.h>
#include <stdlib.h> // Required for the abs() math function

int main() {
    int req[50], n, head, i, total_moves = 0;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the request sequence (separated by spaces): ");
    for(i = 0; i < n; i++) {
        scanf("%d", &req[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\nHead Movement Sequence:\n%d", head);
    
    // Core FCFS Logic
    for(i = 0; i < n; i++) {
        // Calculate absolute distance between current head and next request
        total_moves += abs(req[i] - head);
        
        // Move the head to the new request
        head = req[i];
        
        printf(" -> %d", head);
    }

    printf("\n\nTotal Head Movement: %d cylinders\n", total_moves);

    return 0;
}