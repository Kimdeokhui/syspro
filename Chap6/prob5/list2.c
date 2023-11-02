#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>

char type(mode_t);
char *perm(mode_t);
void printStat(char *, char *, struct stat *);

/* 디렉터리 내용을 자세히 리스트한다. */
int main(int argc, char **argv) {
    DIR *dp;
    char *dir;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ + 1];

    if (argc == 1)
        dir = ".";
    else
        dir = argv[1];

    if ((dp = opendir(dir)) == NULL) {
        perror(dir); // 디렉터리 열기 실패 시 에러 메시지 출력 후 종료
        exit(EXIT_FAILURE);
    }

    // 디렉터리의 각 파일에 대해 자세한 정보 출력
    while ((d = readdir(dp)) != NULL) {
        // 파일 경로 생성
        snprintf(path, sizeof(path), "%s/%s", dir, d->d_name);
        // 파일 상태 정보 가져오기
        if (lstat(path, &st) < 0) {
            perror(path); // 파일 상태 정보 가져오기 실패 시 에러 메시지 출력
        } else {
            printStat(path, d->d_name, &st); // 상세한 파일 정보 출력
        }
    }

    closedir(dp); // 디렉터리 닫기
    exit(EXIT_SUCCESS); // 프로그램 종료
}

/* 파일 상태 정보를 출력 */
void printStat(char *pathname, char *file, struct stat *st) {
    printf("%5d ", st->st_blocks);
    printf("%c%s ", type(st->st_mode), perm(st->st_mode));
    printf("%3d ", st->st_nlink);
    printf("%s %s ", getpwuid(st->st_uid)->pw_name, getgrgid(st->st_gid)->gr_name);
    printf("%9d ", st->st_size);
    printf("%.12s ", ctime(&st->st_mtime) + 4);
    printf("%s\n", file);
}

/* 파일 타입을 반환 */
char type(mode_t mode) {
    if (S_ISREG(mode))
        return('-');
    if (S_ISDIR(mode))
        return('d');
    if (S_ISCHR(mode))
        return('c');
    if (S_ISBLK(mode))
        return('b');
    if (S_ISLNK(mode))
        return('l');
    if (S_ISFIFO(mode))
        return('p');
    if (S_ISSOCK(mode))
        return('s');
}

/* 파일 접근권한을 반환 */
char *perm(mode_t mode) {
    static char perms[10];
    strcpy(perms, "---------");

    for (int i = 0; i < 3; i++) {
        if (mode & (S_IRUSR >> i * 3))
            perms[i * 3] = 'r';
        if (mode & (S_IWUSR >> i * 3))
            perms[i * 3 + 1] = 'w';
        if (mode & (S_IXUSR >> i * 3))
            perms[i * 3 + 2] = 'x';
    }
    return (perms);
}

