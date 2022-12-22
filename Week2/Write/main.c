#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PERMS 0644

int main() {
    int fd = 0;
    char *pathname = "./mymsg.txt";

    char *msg = "Hello, World!";
    ssize_t wsize = 0;

    fd = open(pathname, O_CREAT | O_TRUNC | O_RDWR, PERMS);

    if (fd == -1) {
        perror("open() error!");
        exit(-1);
    }

    wsize = write(fd, (char *)msg, strlen(msg));
    if (wsize == -1) {
        perror("write() error!");
        exit(-2);
    }

    printf("fd: %d, wsize: %ld \n", fd, wsize);

    close(fd);

    return 0;
}
