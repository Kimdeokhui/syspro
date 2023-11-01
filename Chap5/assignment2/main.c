#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buffer;
    long size;
    FILE *fp = fopen("text.txt", "r");

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    buffer = (char *)malloc(size + 1);
    
    fread(buffer, size, 1, fp);
    fclose(fp);

    int i, j;
    int start = 0;
    for (i = size - 1; i >= 0; i--) {
        if (buffer[i] == '\n' || i == 0) {
            if (i == 0) {
                start = 0;
            } else {
                start = i + 1;
            }
            for (j = start; j < size && buffer[j] != '\n'; j++) {
                printf("%c", buffer[j]);
            }
            printf("\n");
        }
    }

    free(buffer);
    return 0;
}

