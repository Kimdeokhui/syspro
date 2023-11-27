#include <stdio.h>
#include <unistd.h>

int main() {
    int pid, gid;

    // 부모 프로세스 정보 출력
    printf("PARENT: PID = %d  GID = %d \n", getpid(), getpgrp());

    // 새로운 프로세스 생성
    pid = fork();

    // 자식 프로세스인 경우
    if (pid == 0) {
        // 자식 프로세스의 프로세스 그룹 ID를 설정
        setpgid(0, 0);

        // 자식 프로세스 정보 출력
        printf("CHILD: PID = %d  GID = %d \n", getpid(), getpgrp());
    }

    return 0;
}

