#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp = fopen("text.txt", "r");

    if (fp == NULL) {
        printf("File open failed\n");
        return 1;
    }

    char lines[100][100];
    int lineCount = 0;
    while (fgets(lines[lineCount], sizeof(lines[lineCount]), fp) != NULL) {
        lineCount++;
    }

    fclose(fp);

    printf("File read success\n");
    printf("Total Line: %d\n", lineCount);

    char userInput[100];
    printf("Please enter your choice: ");
    fgets(userInput, sizeof(userInput), stdin);

    if (userInput[0] == '*') {
        for (int i = 0; i < lineCount; ++i) {
            printf("%s", lines[i]);
        }
    } else if (strstr(userInput, "~") != NULL) {
        int start, end;
        sscanf(userInput, "%d~%d", &start, &end);

        if (start >= 1 && start <= end && end <= lineCount) {
            for (int i = start - 1; i <= end - 1; ++i) {
                printf("%s", lines[i]);
            }
        } else {
            printf("Invalid range\n");
        }
    } else if (strstr(userInput, ",") != NULL) {
        int nums[2];
        sscanf(userInput, "%d,%d", &nums[0], &nums[1]);

        for (int i = 0; i < 2; ++i) {
            if (nums[i] >= 1 && nums[i] <= lineCount) {
                printf("%s", lines[nums[i] - 1]);
            } else {
                printf("Invalid line number: %d\n", nums[i]);
            }
        }
    } else {
        int lineNumber;
        sscanf(userInput, "%d", &lineNumber);

        if (lineNumber >= 1 && lineNumber <= lineCount) {
            printf("%s", lines[lineNumber - 1]);
        } else {
            printf("Invalid line number\n");
        }
    }

    return 0;
}

