#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void mySigHandler(int signum);

int main(int argc, char const *argv[]) {
    int cnt = 10;

    sigset_t set;

    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);

    sigprocmask(SIG_BLOCK, &set, NULL);
    signal(SIGUSR1, mySigHandler);
    printf("My PID is: %d\n", getpid());
    while (cnt > 0) {
        printf("%d\n", cnt);
        fflush(stdout);
        cnt -= 1;
        sleep(1);
    }

    return 0;
}

void mySigHandler(int signum) {
    if (signum == SIGUSR1) {
        puts("Hello!");
    }
}
