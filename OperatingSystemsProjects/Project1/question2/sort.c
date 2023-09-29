#include <stdio.h>
#include <string.h>

#define MAX_NAMES 1000
#define MAX_NAME_LENGTH 50

int main() {
    char names[MAX_NAMES][MAX_NAME_LENGTH];
    int count = 0;

//    printf("Enter student names. Press Ctrl-D to finish input.\n");

    while (scanf("%s", names[count]) != EOF && count < MAX_NAMES) {
        count++;
    }

    // Simple bubble sort
    for (int i = 0; i < count-1; i++) {
        for (int j = i+1; j < count; j++) {
            if (strcmp(names[i], names[j]) > 0) {
                char temp[MAX_NAME_LENGTH];
                strcpy(temp, names[i]);
                strcpy(names[i], names[j]);
                strcpy(names[j], temp);
            }
        }
    }

//    printf("\nSorted names:\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", names[i]);
    }

    return 0;
}

