#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 80

void printFileWithLineNumbers(FILE *fp) {
    int line = 0;
    char buffer[MAXLINE];

    while (fgets(buffer, MAXLINE, fp) != NULL) {
        line++;
        printf("%3d %s", line, buffer);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-n] file1 [file2 ...]\n", argv[0]);
        exit(1);
    }

    int lineNumberFlag = 0;
    int fileIndex = 1;
    
    if (strcmp(argv[1], "-n") == 0) {
        lineNumberFlag = 1;
        fileIndex++;
    }

    for (int i = fileIndex; i < argc; i++) {
        FILE *fp;
        if ((fp = fopen(argv[i], "r")) == NULL) {
            fprintf(stderr, "Error: Cannot open file %s\n", argv[i]);
            continue;
        }

        if (lineNumberFlag) {
            printFileWithLineNumbers(fp);
        } else {
            char c;
            while ((c = getc(fp)) != EOF) {
                putc(c, stdout);
            }
        }

        fclose(fp);
    }

    return 0;
}

