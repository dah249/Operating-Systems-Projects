#include <stdio.h>

#define MAX_NAME_LENGTH 100
#define MAX_STUDENTS 100

int main() {
    char names[MAX_STUDENTS][MAX_NAME_LENGTH];
    float gpa;
    int num = 0;

    printf("Enter student names and GPAs. Followed by (control + d) to exit\n");

    while(scanf("%s %f", names[num], &gpa) != EOF) {
        if(gpa > 3.0) {
            num++;
        }
    }

    printf("Students with GPAs above 3.0:\n");
    for(int i = 0; i < num; i++) {
        printf("%s\n", names[i]);
    }

    return 0;
}


