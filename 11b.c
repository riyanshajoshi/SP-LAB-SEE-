#include <stdio.h>
#include <stdlib.h> // For abs() function

int main() {
    int req[50], visited[50] = {0}; // visited array tracks completed requests
    int n, head, i, j, total_moves = 0;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the request sequence: ");
    for(i = 0; i < n; i++) {
        scanf("%d", &req[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\nHead Movement Sequence:\n%d", head);

    // Loop n times, because we must process n requests
    for(i = 0; i < n; i++) {
        int min_dist = 9999;
        int target_index = -1;

        // Scan all requests to find the closest unvisited one
        for(j = 0; j < n; j++) {
            if(visited[j] == 0) { // Only check if we haven't visited it yet
                int dist = abs(req[j] - head);
                if(dist < min_dist) {
                    min_dist = dist;
                    target_index = j;
                }
            }
        }

        // Move head to the closest request we found
        visited[target_index] = 1;       // Mark as visited
        total_moves += min_dist;         // Add to our total distance
        head = req[target_index];        // Update head position
        
        printf(" -> %d", head);
    }

    printf("\n\nTotal Head Movement: %d cylinders\n", total_moves);

    return 0;
}