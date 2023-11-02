#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    DIR *dp;
    char *dir;
    struct dirent *d;
    struct stat st;
    char path[BUFSIZ + 1];

    // 명령어 라인 인자로 디렉터리 경로를 받음
    if (argc == 1)
        dir = "."; // 기본적으로 현재 디렉터리를 대상으로 함
    else
        dir = argv[1];

    // 디렉터리 열기
    if ((dp = opendir(dir)) == NULL) {
        perror(dir); // 에러가 발생하면 에러 메시지 출력 후 종료
        exit(EXIT_FAILURE);
    }

    // 각 디렉터리 엔트리에 대해 파일 이름과 i-노드 번호 출력
    while ((d = readdir(dp)) != NULL) {
        snprintf(path, sizeof(path), "%s/%s", dir, d->d_name); // 파일 경로 생성
        if (stat(path, &st) == -1) {
            perror("stat"); // 파일 정보 얻기 실패 시 에러 메시지 출력
            continue;
        }
        printf("%s %lu\n", d->d_name, (unsigned long)st.st_ino); // 파일 이름과 i-노드 번호 출력
    }

    closedir(dp); // 디렉터리 닫기
    exit(EXIT_SUCCESS); // 프로그램 종료
}

