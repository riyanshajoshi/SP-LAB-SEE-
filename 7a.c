#include <stdio.h>

// Step 1: Define the structure for a Segment Table entry
struct Segment {
    int limit;
    int base;
} seg_table[10]; // Maximum 10 segments

int main() {
    int n, i, seg_num, offset, physical_addr, choice;

    printf("Enter the number of segments: ");
    scanf("%d", &n);

    // Step 2: Input Base and Limit for each segment
    for(i = 0; i < n; i++) {
        printf("Enter Base Address and Limit for Segment %d: ", i);
        scanf("%d %d", &seg_table[i].base, &seg_table[i].limit);
    }

    do {
        // Step 3: Request logical address from the user
        printf("\nEnter Logical Address (Segment_Number Offset): ");
        scanf("%d %d", &seg_num, &offset);

        // Step 4: Address Translation and Error Checking
        if (seg_num >= n || seg_num < 0) {
            printf("Error: Invalid Segment Number!\n");
        } 
        else if (offset >= seg_table[seg_num].limit) {
            // CRITICAL CHECK: Offset must strictly be less than the limit size
            printf("Error: Segmentation Fault! Offset exceeds segment limit.\n");
        } 
        else {
            // Formula: Physical Address = Base Address + Offset
            physical_addr = seg_table[seg_num].base + offset;
            printf("Success: Physical Address is %d\n", physical_addr);
        }

        printf("\nDo you want to check another address? (1 for Yes, 0 for Exit): ");
        scanf("%d", &choice);

    } while(choice == 1);

    return 0;
}