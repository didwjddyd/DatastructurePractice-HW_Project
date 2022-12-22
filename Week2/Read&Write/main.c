#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PERMS 0644
#define MAX_NAME_SIZE 32

struct __User {
    char name[MAX_NAME_SIZE + 1];
    int age;
};
typedef struct __User User;

/*int main() {
    int fd = 0;
    char *pathName = "./user.dat";

    ssize_t wSize = 0;

    char userName[MAX_NAME_SIZE + 1] = {
        '\0',
    };
    int userAge = 0;

    User *user = (User *)malloc(sizeof(User));
    memset(user->name, '\0', MAX_NAME_SIZE + 1);
    user->age = 0;

    printf("Name: ");
    scanf("%[^\n]", userName);
    strcpy(user->name, userName);

    printf("Age: ");
    scanf("%d", &userAge);
    user->age = userAge;

    fd = open(pathName, O_CREAT | O_TRUNC | O_RDWR, PERMS);

    if (fd == -1) {
        perror("open() error!");
        exit(-1);
    }

    wSize = write(fd, (User *)user, sizeof(User));
    if (wSize == -1) {
        perror("write() error!");
        exit(-2);
    }

    printf("fd: %d, wSize: %ld", fd, wSize);

    close(fd);
    free(user);

    return 0;
}*/

void main() {
    int fd = 0;
    char *pathName = "./user.dat";
    ssize_t rSize = 0;

    User *user = (User *)malloc(sizeof(User));
    memset(user->name, '\0', MAX_NAME_SIZE + 1);
    user->age = 0;

    fd = open(pathName, O_RDONLY, PERMS);
    if (fd == -1) {
        perror("open() error!");
        exit(-1);
    }

    rSize = read(fd, (User *)user, sizeof(User));
    if (rSize == -1) {
        perror("read() error!");
        exit(-2);
    }
    printf("fd: %d, rSize: %ld \n", fd, rSize);

    printf("User Name: %s, Age: %d \n", user->name, user->age);

    close(fd);
    free(user);

    return 0;
}
