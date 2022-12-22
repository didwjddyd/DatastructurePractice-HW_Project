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

    shmid = openShm(MY_SHM_KEY);          //  공유 메모리 주소 획득
    shmaddr = shmat(shmid, NULL, 0);      //  공우 메모리 접속
    semidServ = openSem(MY_SEM_SERV_KEY); //  서버 세마포어 식별자 획득
    semidClnt = openSem(MY_SEM_CLNT_KEY); //  클라이언트 세마포어 식별자 획득

    signal(SIGINT, signalHandler); //  SIGINT 핸들러 변경

    while (1) {
        // 서버로 값 전송
        printf("<< ");
        scanf("%d", &req);
        fflush(stdout);
        fflush(stdin);

        // 서버로 값 전송을 위한 연산
        lockSem(semidClnt); //  연산을 위해 세마포어 잠금
        memcpy(shmaddr, &req, sizeof(int)); //  공유 메모리에 값 전송
        unlockSem(semidServ); //  연산 후 세마포어 잠금 해제

        // 서버로부터 받은 값 확인을 위한 연산
        lockSem(semidClnt); //  연산을 위해 세마포어 잠금
        memcpy(&res, shmaddr, sizeof(int)); //  공유 메모리에서 값 수신
        unlockSem(semidClnt); //  연산 후 세마포어 잠금 해제

        printf(">> %d\n", res);
    }

    return 0;
}

void signalHandler(int signum) {
    if (signum == SIGINT) {
        shmdt(shmaddr); //  공유 메모리 접속 해제
        exit(0);
    }
}
