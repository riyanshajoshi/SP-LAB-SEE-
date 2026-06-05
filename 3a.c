#include <stdio.h>
#include <string.h>

// Step 1: Define the Directory Structure
struct Directory {
    char dname[20];         // Directory Name
    char fname[10][20];     // Array of 10 files (strings) per directory
    int fcnt;               // File count for this directory
} dir[10];                  // Maximum 10 directories in the master file

int dcnt = 0;               // Master directory count

int main() {
    int i, j, choice;
    char d[20], f[20];

    while (1) {
        printf("\n--- Two Level Directory ---\n");
        printf("1. Create Directory\n2. Create File\n3. Delete File\n4. Display\n5. Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Create Directory
                printf("Enter directory name: ");
                scanf("%s", dir[dcnt].dname);
                dir[dcnt].fcnt = 0; // Initialize file count to 0
                dcnt++;
                printf("Directory created.\n");
                break;

            case 2: // Create File
                printf("Enter directory name to insert into: ");
                scanf("%s", d);
                for (i = 0; i < dcnt; i++) {
                    if (strcmp(d, dir[i].dname) == 0) { // If directory found
                        printf("Enter file name: ");
                        scanf("%s", dir[i].fname[dir[i].fcnt]);
                        dir[i].fcnt++;
                        printf("File created successfully.\n");
                        break;
                    }
                }
                if (i == dcnt) printf("Error: Directory not found!\n");
                break;

            case 3: // Delete File
                printf("Enter directory name: ");
                scanf("%s", d);
                for (i = 0; i < dcnt; i++) {
                    if (strcmp(d, dir[i].dname) == 0) { // If directory found
                        printf("Enter file name to delete: ");
                        scanf("%s", f);
                        for (j = 0; j < dir[i].fcnt; j++) {
                            if (strcmp(f, dir[i].fname[j]) == 0) { // If file found
                                // The "Fast Delete" trick: overwrite it with the last file
                                strcpy(dir[i].fname[j], dir[i].fname[dir[i].fcnt - 1]);
                                dir[i].fcnt--; 
                                printf("File deleted successfully.\n");
                                break;
                            }
                        }
                        if (j == dir[i].fcnt + 1) printf("Error: File not found!\n"); // Because fcnt was decremented
                        break;
                    }
                }
                if (i == dcnt) printf("Error: Directory not found!\n");
                break;

            case 4: // Display System
                printf("\nDirectory\tFiles\n");
                for (i = 0; i < dcnt; i++) {
                    printf("%s\t\t", dir[i].dname);
                    for (j = 0; j < dir[i].fcnt; j++) {
                        printf("%s  ", dir[i].fname[j]);
                    }
                    printf("\n");
                }
                if (dcnt == 0) printf("System is empty.\n");
                break;

            case 5: // Exit
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}