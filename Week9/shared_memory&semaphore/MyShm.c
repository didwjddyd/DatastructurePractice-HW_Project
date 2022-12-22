#include "MyShm.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

int creatShm(int key) {
    int shmid = shmget((key_t)key, SHM_MAX_SIZE,
                       IPC_CREAT | IPC_EXCL | SHM_PERMS); //  공유 메모리 생성

    if (shmid == -1) {
        perror("creatShm() error!");
        exit(-1);
    }

    return shmid;
}

int openShm(int key) {
    int shmid = shmget((key_t)key, SHM_MAX_SIZE,
                       IPC_CREAT); //  공유 메모리 생성. 이 함수에서는
                                   //  공유메모리의 주소를 받는 용도로 사용

    return shmid;
}

int closeShm(int shmid) { //  공유 메모리 삭제
    return shmctl(shmid, IPC_RMID, 0);
}
