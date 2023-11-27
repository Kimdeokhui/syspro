#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXARG 10
#define MAXLINE 1024

void execute_command(char *args[], int background);

int main() {
    char input[MAXLINE];
    char *token;
    char *args[MAXARG];
    int background;

    while (1) {
        // 프롬프트 출력
        printf("pls input cmd : ");

        // 사용자 입력 받기
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error reading input\n");
            exit(EXIT_FAILURE);
        }

        // 개행 문자 제거
        if (input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
        }

        // 명령줄 인수 초기화
        for (int i = 0; i < MAXARG; i++) {
            args[i] = NULL;
        }

        // 명령어 및 옵션을 명령줄 인수로 분리
        token = strtok(input, " ");
        int arg_index = 0;

        while (token != NULL) {
            args[arg_index++] = token;
            token = strtok(NULL, " ");
        }

        // 마지막 명령줄 인수가 백그라운드 실행 여부 확인
        if (arg_index > 0 && strcmp(args[arg_index - 1], "&") == 0) {
            background = 1;
            args[arg_index - 1] = NULL; // 백그라운드 실행을 위해 '&' 삭제
        } else {
            background = 0;
        }

        // 명령어 실행
        execute_command(args, background);
    }

    return 0;
}

void execute_command(char *args[], int background) {
    pid_t pid;
    int status;

    // 새로운 프로세스 생성
    if ((pid = fork()) == 0) {
        // 자식 프로세스에서 명령어 실행
        execvp(args[0], args);

        // execvp가 실패한 경우
        perror("execvp");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // fork 실패한 경우
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // 부모 프로세스가 백그라운드가 아닌 경우 기다림
    if (background == 0) {
        waitpid(pid, &status, 0);
    }
}

