#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, "eugip")) != -1) {
        switch (opt) {
            case 'e':
                if (optind < argc) {
                    char *env_value = getenv(argv[optind]);
                    if (env_value != NULL) {
                        printf("%s=%s\n", argv[optind], env_value);
                    } else {
                        printf("%s is not set.\n", argv[optind]);
                    }
                } else {
                    extern char **environ;
                    for (char **env = environ; *env != NULL; env++) {
                        printf("%s\n", *env);
                    }
                }
                break;
            case 'u':
                printf("My Realistic User ID: %d\nMy Valid User ID: %d\n", getuid(), geteuid());
                break;
            case 'g':
                printf("My Realistic Group ID: %d\nMy Valid Group ID: %d\n", getgid(), getegid());
                break;
            case 'i':
                printf("my process number : [%d]\n", getpid());
                break;
            case 'p':
                printf("my parent's process number : [%d]\n", getppid());
                break;
            default:
                fprintf(stderr, "Unknown option: %c\n", opt);
                return 1;
        }
    }

    return 0;
}

