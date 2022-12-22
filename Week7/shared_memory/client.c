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

key_t mykey = 0;
int shmid = 0;
int *shmaddr = NULL;

int main(int argc, char const *argv[]) {
    struct shmid_ds buf;
    int data = 0;

    mykey = ftok("myshmkey", 2); //  Shared Memory 생성을 위한 key 생성
    shmid = shmget(mykey, MAX_SHM_SIZE, IPC_CREAT); //  Shared Memory 생성
    shmaddr = shmat(shmid, NULL, 0);                //  Shared Memory 접속

    //  server로부터 SIGUSR1 수신받으면 signalHandler 실행
    signal(SIGUSR1, signalHandler);

    while (1) {
        printf("<< ");
        scanf("%d", &data); //  data 입력

        fflush(stdout); //  stdout 초기화
        fflush(stdin);  //  stdin 초기화

        memcpy(shmaddr, &data,
               sizeof(int)); //  Shared Memory에 data를 저장

        shmctl(shmid, IPC_STAT, &buf); //  Shared Memory의 정보를 buf에 저장
        kill(buf.shm_cpid, SIGUSR1); //  server에 SIGUSR1 전송

        pause();
    }

    return 0;
}

void signalHandler(int signum) {
    int data = 0;

    //  SIGUSR1 수신 시 Shared Memory에서 data를 복사 후 출력
    if (signum == SIGUSR1) {
        memcpy(&data, shmaddr, sizeof(int));
        printf(">> %d\n", data);
    }
}
