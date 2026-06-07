#include <stdio.h>

int main() {
    int page_table[50]; // Maps page numbers to frame numbers
    int n, page_size, p_num, offset, p_addr, i;

    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page size (in bytes): ");
    scanf("%d", &page_size);

    // Step 1: Build the Page Table
    printf("\nEnter the frame number for each page:\n");
    for(i = 0; i < n; i++) {
        printf("Page %d is stored in Frame: ", i);
        scanf("%d", &page_table[i]);
    }

    // Step 2: Perform the Translation
    printf("\nEnter Logical Address (Page_Number Offset): ");
    scanf("%d %d", &p_num, &offset);

    // Step 3: Error Checking and Calculation
    if(p_num >= n || p_num < 0) {
        printf("Error: Invalid Page Number!\n");
    } 
    else if(offset >= page_size) {
        printf("Error: Offset exceeds page size!\n");
    } 
    else {
        // Core Formula: Physical Address = (Frame Number * Page Size) + Offset
        p_addr = (page_table[p_num] * page_size) + offset;
        printf("Success: Physical Address is %d\n", p_addr);
    }

    return 0;
}