#include "MySem.h"
#include "MyShm.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>

void signalHandler(int signum);

int shmid = 0;
int *shmaddr = NULL;

int semidServ = 0;
int semidClnt = 0;

int main(int argc, char const *argv[]) {
    int req = 0;
    int res = 0;

    union semun semunBuf;

    shmid = creatShm(MY_SHM_KEY);    //  공유 메모리 생성
    shmaddr = shmat(shmid, NULL, 0); //  공유 메모리 접속

    semidServ = creatSem(MY_SEM_SERV_KEY); //  서버 세마포어 생성
    semunBuf.val = 0;
    semctl(semidServ, 0, SETVAL,
           semunBuf); //  서버 세마포어의 값을 semunBuf.val로 변경

    semidClnt = creatSem(MY_SEM_CLNT_KEY); //  클라이언트 세마포어 생성
    semunBuf.val = 1;
    semctl(semidClnt, 0, SETVAL,
           semunBuf); //  클라이언트 세마포어의 값을 semunBuf.val로 변경

    signal(SIGINT, signalHandler); //  SIGINT 핸들러 변경

    while (1) {
        puts("Wait ...");

        //  세마포어 잠금 후 연산
        lockSem(semidServ);
        memcpy(&req, shmaddr, sizeof(int)); //  공유 메모리에서 값 수신
        res = req + 1; //  다시 전송할 값 = 전송받은 값 + 1
        memcpy(shmaddr, &res, sizeof(int)); //  공유 메모리에 값 전송
        unlockSem(semidClnt); //  연신 후 세마포어 잠금 해제

        printf("Request: %d\n", req);
        printf("Responses: %d\n", res);
        fflush(stdout);
    }

    return 0;
}

void signalHandler(int signum) {
    if (signum == SIGINT) {
        closeSem(semidClnt); //  서버 세마포어 제거
        closeSem(semidServ); //  클라이언트 세마포어 제거

        shmdt(shmaddr);  //  공유 메모리 접속 해제
        closeShm(shmid); //  공유 메모리 삭제

        exit(0);
    }
}
