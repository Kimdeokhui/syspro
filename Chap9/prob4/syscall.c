#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int mysystem(const char *cmdstring);

int main()
{
    int status;

    // "date" 명령어 실행
    if ((status = system("date")) < 0)
        perror("system() 오류");
    printf("종료코드 %d\n", WEXITSTATUS(status));

    // "hello" 명령어 실행
    if ((status = system("hello")) < 0)
        perror("system() 오류");
    printf("종료코드 %d\n", WEXITSTATUS(status));

    // "who; exit 44" 명령어 실행
    if ((status = system("who; exit 44")) < 0)
        perror("system() 오류");
    printf("종료코드 %d\n", WEXITSTATUS(status));

    return 0;
}

int mysystem(const char *cmdstring) {
    int pid, status;

    // 명령어가 NULL인 경우
    if (cmdstring == NULL)
        return 1;

    // 새로운 프로세스 생성
    pid = fork();

    // 프로세스 생성 실패
    if (pid == -1)
        return -1;

    // 자식 프로세스에서 새로운 프로그램 실행
    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
        _exit(127); // 명령어 실행 오류
    }

    // 부모 프로세스가 자식 프로세스의 종료를 기다림
    do {
        if (waitpid(pid, &status, 0) == -1) {
            if (errno != EINTR) // waitpid()로부터 EINTR 오류 외
                return -1;
        } else {
            return status;
        }
    } while (1);
}

