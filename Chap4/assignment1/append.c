#include <stdio.h>

int main() {
    FILE *file1, *file2;
    char ch;

    file1 = fopen("file1.txt", "r");
    if (file1 == NULL) {
        printf("Cannot open file1.txt\n");
        return 1;
    }

    file2 = fopen("file2.txt", "a");
    if (file2 == NULL) {
        fclose(file1);
        return 1;
    }

    while ((ch = fgetc(file1)) != EOF) {
        fputc(ch, file2);
    }

    fclose(file1);
    fclose(file2);

    return 0;
}

