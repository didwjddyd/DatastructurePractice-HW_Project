#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_SHM_SIZE 512

void signalHandler(int signum);
void myfunc(void);

key_t mykey = 0;
int shmid = 0;
int *shmaddr = NULL;

int main(int argc, char const *argv[]) {
    mykey = ftok("myshmkey", 2); //  Shared Memory 생성을 위한 key 생성
    shmid =
        shmget(mykey, MAX_SHM_SIZE, IPC_CREAT | 0600); //  Shared Memory 생성

    shmaddr = shmat(shmid, NULL, 0); //  Shared Memory 접속

    //  SIGINT, SIGUSR1수신 시 signalHandler 실행
    signal(SIGINT, signalHandler);
    signal(SIGUSR1, signalHandler); //  client로부터 수신

    while (1) {
        puts("Wait ...");
        pause();
    }

    return 0;
}

void signalHandler(int signum) {
    struct shmid_ds buf;
    if (signum == SIGINT) { //  SIGINT수신 시 Shared Memory 접속 해제 후 삭제
        shmdt(shmaddr);
        shmctl(shmid, IPC_RMID, NULL);
        exit(0);
    } else if (signum == SIGUSR1) {
        myfunc();
    }
}

void myfunc(void) { //  if(SIGUSR1 수신)
    struct shmid_ds buf;
    int data = 0;

    //  수신한 데이터 내용 복사 후 출력
    memcpy(&data, shmaddr, sizeof(int));
    printf("Receive: %d\n", data);

    data += 1; //  Shared Memory에서 가져온 data에 1 더함
    memcpy(shmaddr, &data, sizeof(int)); //  Shared Memory에 data 저장
    printf("Send: %d\n", data);          //  저장한 내용 출력

    shmctl(shmid, IPC_STAT, &buf); //  shmid의 정보를 buf에 저장
    kill(buf.shm_lpid,
         SIGUSR1); //  client에 SIGUSR1 전송
}
