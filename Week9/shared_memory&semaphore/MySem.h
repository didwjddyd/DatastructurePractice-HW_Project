#ifndef __MYSEM_H__
#define __MYSE_H__

#define SEM_MAX_NUM 1 //  세마포어 개수 및 연산에 사용되는 상수
#define SEM_ERMS 0600 //  세마포어 권한 상수

#define MY_SEM_SERV_KEY 1357 //  세마포어 서버 키 상수
#define MY_SEM_CLNT_KEY 2468 //  세마포어 클라이언트 키 상수

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
};

int creatSem(int key);
int openSem(int key);
int lockSem(int semid);
int unlockSem(int semid);
int closeSem(int semid);

#endif
