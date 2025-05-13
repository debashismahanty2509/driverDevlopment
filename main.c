#include <stdio.h>
#include <string.h>

int main() {
    FILE* fptr;

    // Declare the character array 
    // for the data to be read from file
    char data[8];
    fptr = fopen("/proc/debashis", "r");

    if (fptr == NULL) {
        printf("file.txt file failed to open.");
    }
    else {

        printf("The file is now opened.\n");

        // Read the data from the file
        // using fgets() method
        while (fgets(data, 2, fptr)
               != NULL) {

            // Print the data
            printf("%s ", data);
        }

        // Closing the file using fclose()
        fclose(fptr);
    }
    return 0;
}