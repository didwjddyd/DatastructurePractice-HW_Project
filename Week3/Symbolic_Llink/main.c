#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int r = 0;
    char *pathname = "/bin/vim";

    struct stat buf1;
    struct stat buf2;

    r = stat(pathname, &buf1);
    if (r == -1) {
        perror("stat() error!");
        exit(-1);
    }

    r = lstat(pathname, &buf2);
    if (r == -1) {
        perror("lstat() error!");
        exit(-1);
    }

    printf("Original file size: %ld\n", buf1.st_size);
    printf("Symbolic link file size: %ld\n", buf2.st_size);

    return 0;
}
