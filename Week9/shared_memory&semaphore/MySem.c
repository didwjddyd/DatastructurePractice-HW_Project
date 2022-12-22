#include "MySem.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

int creatSem(int key) {
    int semid =
        semget((key_t)key, SEM_MAX_NUM, IPC_CREAT | SEM_ERMS); //  세마포어 생성

    if (semid == -1) {
        perror("creatSem() error!");
        exit(-1);
    }

    return semid;
}

int openSem(int key) {
    int semid = semget((key_t)key, 0,
                       IPC_CREAT); //  세마포어 생성. 이 함수에서는 세마포어
                                   //  식별자를 반환하기 위해 사용
    return semid;
}

int lockSem(int semid) { //  세마포어 잠금
    struct sembuf buf = {
        0, -1, SEM_UNDO}; //  세마포어 연산 정보를 저장하는 구조체 생성
    return semop(semid, &buf, SEM_MAX_NUM); //  세마포어 값 변경
}

int unlockSem(int semid) { //  세마포어 잠금 해제
    struct sembuf buf = {
        0, 1, SEM_UNDO}; //  세마포어 연산 정보를 저장하는 구조체 생성
    return semop(semid, &buf, SEM_MAX_NUM); //  세마포어 값 변경
}

int closeSem(int semid) { //  세마포어 제거
    return semctl(semid, 0, IPC_RMID, 0);
}
