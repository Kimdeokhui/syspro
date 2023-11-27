#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 1024

void execute_command(char *command);

int main() {
    char input[MAX_COMMAND_LENGTH];
    char *token;
    
    while (1) {
        // 프롬프트 출력
        printf("[shell] ");
        
        // 사용자 입력 받기
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error reading input\n");
            exit(EXIT_FAILURE);
        }

        // 개행 문자 제거
        if (input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
        }

        // 명령어 토큰 분리
        token = strtok(input, ";");
        
        while (token != NULL) {
            // 명령어 실행
            execute_command(token);
            
            // 다음 토큰으로 이동
            token = strtok(NULL, ";");
        }
    }

    return 0;
}

void execute_command(char *command) {
    pid_t pid;
    int status;

    // 백그라운드 실행 여부 확인
    int background = 0;
    if (command[strlen(command) - 1] == '&') {
        background = 1;
        command[strlen(command) - 1] = '\0';
    }

    // 입출력 리디렉션 여부 확인
    char *input_file = NULL;
    char *output_file = NULL;

    // 입력 리디렉션 확인
    if (strstr(command, "<") != NULL) {
        input_file = strtok(command, "< ");
        command = strtok(NULL, "< ");
    }

    // 출력 리디렉션 확인
    if (strstr(command, ">") != NULL) {
        output_file = strtok(command, "> ");
        command = strtok(NULL, "> ");
    }

    // 새로운 프로세스 생성
    if ((pid = fork()) == 0) {
        // 자식 프로세스에서 명령어 실행
        if (input_file != NULL) {
            freopen(input_file, "r", stdin);
        }

        if (output_file != NULL) {
            freopen(output_file, "w", stdout);
        }

        // 명령어 실행
        execlp(command, command, (char *)NULL);

        // execlp가 실패한 경우
        perror("execlp");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // fork 실패한 경우
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // 부모 프로세스가 기다림
    if (background == 0) {
        waitpid(pid, &status, 0);
    }
}

