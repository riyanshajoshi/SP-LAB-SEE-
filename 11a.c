#include <stdio.h>

int main() {
    int index_block, n, i;
    int blocks[50]; // To store the list of allocated data blocks

    printf("Enter the Index Block number: ");
    scanf("%d", &index_block);
    
    printf("Enter the number of data blocks needed for the file: ");
    scanf("%d", &n);
    
    printf("Enter the block numbers to allocate (separated by spaces): ");
    for(i = 0; i < n; i++) {
        scanf("%d", &blocks[i]);
    }
    
    printf("\n--- File Indexed Allocation Map ---\n");
    printf("Index Block: [ %d ]\n", index_block);
    
    // Simply print out the connections from the Index Block to the Data Blocks
    for(i = 0; i < n; i++) {
        printf("  |--> Points to Data Block: %d\n", blocks[i]);
    }
    
    printf("\nSuccess: File allocated using Indexed Technique.\n");
    return 0;
}