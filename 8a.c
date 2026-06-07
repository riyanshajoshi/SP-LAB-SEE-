#include <stdio.h>
#include <string.h>

int main() {
    char dir_name[20];
    char files[10][20]; // Array to hold up to 10 files
    int fcnt = 0, choice, i;
    char fname[20];

    printf("Enter the name of the Master Directory: ");
    scanf("%s", dir_name);

    do {
        printf("\n--- %s ---\n", dir_name);
        printf("1. Create File\n2. Delete File\n3. Display\n4. Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter file name: ");
            scanf("%s", files[fcnt]);
            fcnt++;
            printf("File created.\n");
        } 
        else if (choice == 2) {
            printf("Enter file name to delete: ");
            scanf("%s", fname);
            for (i = 0; i < fcnt; i++) {
                if (strcmp(fname, files[i]) == 0) { // Found the file
                    strcpy(files[i], files[fcnt - 1]); // Fast Delete: overwrite with last file
                    fcnt--;
                    printf("File deleted.\n");
                    break;
                }
            }
            if (i == fcnt) printf("Error: File not found.\n");
        } 
        else if (choice == 3) {
            printf("Directory: %s\nFiles: ", dir_name);
            for (i = 0; i < fcnt; i++) {
                printf("%s  ", files[i]);
            }
            printf("\n");
        }
    } while (choice != 4);

    return 0;
}