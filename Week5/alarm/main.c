#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void myAlarmHandler(int signum);

int main(int argc, const char *argv[]) {
    if (signal(SIGALRM, myAlarmHandler) == SIG_ERR) {
        perror("signal() error!");
    }
    alarm(5);

    puts("Sleep ... ");
    sleep(100);

    return 0;
}

void myAlarmHandler(int signum) { puts("Hello! I'm wake!"); }
