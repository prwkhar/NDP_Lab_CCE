#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

int main() {
    FILE *fptr, *tempFile;
    char line[MAX_LINE];
    char filename[] = "file1.txt";
    char tempFilename[] = "temp.txt";
    char oldWord[50], newWord[50];
    int found = 0;

    // Open the file for reading
    fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("Unable to open file.\n");
        return 1;
    }

    // Open a temporary file for writing
    tempFile = fopen(tempFilename, "w");
    if (tempFile == NULL) {
        printf("Unable to create temporary file.\n");
        fclose(fptr);
        return 1;
    }

    // Get old and new words from the user
    printf("Enter the word to be replaced: ");
    scanf("%s", oldWord);
    printf("Enter the new word: ");
    scanf("%s", newWord);

    // Read each line, replace the word, and write to the temp file
    while (fgets(line, MAX_LINE, fptr) != NULL) {
        char *pos = strstr(line, oldWord);
        if (pos != NULL) {
            found = 1;
            // Replace the word
            char temp[MAX_LINE];
            strncpy(temp, line, pos - line); // Copy part before word
            temp[pos - line] = '\0';
            strcat(temp, newWord);          // Append new word
            strcat(temp, pos + strlen(oldWord)); // Append rest of line
            strcpy(line, temp);
        }
        fputs(line, tempFile);
    }

    fclose(fptr);
    fclose(tempFile);

    // If word was found, replace the original file
    if (found) {
        remove(filename);
        rename(tempFilename, filename);
        printf("Word replaced successfully!\n");
    } else {
        printf("Word not found.\n");
        remove(tempFilename);
    }

    return 0;
}
