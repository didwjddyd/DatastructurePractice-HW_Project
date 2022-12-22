#ifndef __MYSHM_H__
#define __MYSHM_H__

#define SHM_MAX_SIZE 512 //  공유 메모리 크기 상수
#define SHM_PERMS 0600   //  공유 메모리 권한 상수

#define MY_SHM_KEY 1234 //  공유 메모리 키 함수

int creatShm(int key);
int openShm(int key);
int closeShm(int shmid);

#endif
