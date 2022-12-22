#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    pid_t pid = 0;
    int status = 0;
    char *args[] = {"ls", "-l", "-a", NULL};
    char *envp[] = {"USER=gildong", "HOME=/home/gildong", NULL};

    pid = fork();
    switch (pid) {
    case -1:
        perror("fork() error!");
    case 0:
        execve("/bin/ls", args, envp);
        break;
    }

    if (pid > 0) {
        wait(&status);
    }

    return 0;
}
