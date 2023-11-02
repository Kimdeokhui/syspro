#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

char type(mode_t);
char *perm(mode_t);
void printStat(char *, char *, struct stat *, int);

int main(int argc, char **argv) {
    DIR *dp;
    char *dir;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ + 1];
    int option = 0; // Default: no option

    // Check for command line options
    if (argc > 1) {
        if (strcmp(argv[1], "-p") == 0) {
            option = 1; // -p option: print only path
            dir = (argc > 2) ? argv[2] : ".";
        } else if (strcmp(argv[1], "-Q") == 0) {
            option = 2; // -Q option: print in quotes
            dir = (argc > 2) ? argv[2] : ".";
        } else if (strcmp(argv[1], "-i") == 0) {
            option = 3; // -i option: print only inode number
            dir = (argc > 2) ? argv[2] : ".";
        } else {
            dir = argv[1]; // No option: default behavior
        }
    } else {
        dir = ".";
    }

    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
        exit(EXIT_FAILURE);
    }

    while ((d = readdir(dp)) != NULL) {
        snprintf(path, sizeof(path), "%s/%s", dir, d->d_name);
        if (lstat(path, &st) < 0) {
            perror(path);
        } else {
            printStat(path, d->d_name, &st, option);
        }
    }

    closedir(dp);
    exit(EXIT_SUCCESS);
}

void printStat(char *pathname, char *file, struct stat *st, int option) {
    switch (option) {
        case 1: // -p option: print only path
            printf("%s\n", pathname);
            break;
        case 2: // -Q option: print in quotes
            printf("\"%s\"\n", file);
            break;
        case 3: // -i option: print only inode number
            printf("%lu\n", st->st_ino);
            break;
        default: // No option: default behavior
            printf("%5d %c%s %3d %s %s %9d %.12s %s\n", st->st_blocks, type(st->st_mode),
                perm(st->st_mode), st->st_nlink, getpwuid(st->st_uid)->pw_name,
                getgrgid(st->st_gid)->gr_name, st->st_size, ctime(&st->st_mtime) + 4, file);
            break;
    }
}

char type(mode_t mode) {
    // Function implementation remains the same
}

char *perm(mode_t mode) {
    // Function implementation remains the same
}

