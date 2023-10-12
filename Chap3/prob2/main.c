#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return strlen((const char *)b) - strlen((const char *)a);
}

int main() {
    const int MAX_LINES = 100;
    char lines[MAX_LINES][100];

    int lineCount = 0;

    while (lineCount < MAX_LINES && fgets(lines[lineCount], sizeof(lines[0]), stdin) != NULL) {
        if (lines[lineCount][0] == '\n') {
            break;
        }
        lineCount++;
    }

    qsort(lines, lineCount, sizeof(lines[0]), compare);

    for (int i = 0; i < lineCount; ++i) {
        printf("%s", lines[i]);
    }

    return 0;
}

