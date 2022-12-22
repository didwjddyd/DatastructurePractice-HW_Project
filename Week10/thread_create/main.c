#include <pthread.h>
#include <stdio.h>

void *myThread(void *arg);

int main() {
    pthread_t tid = 0; //  스레드 ID
    int count = 5;     //  스레드가 작동할 myThread()에 들어갈 변수
    int *status;       //  스레드 종료값 저장

    printf("Hello. I'm main thread: %ld\n", pthread_self());
    if (pthread_create(&tid, NULL, myThread,
                       (void *)&count)) { //  스레드 생성. 오류 발생 시 오류
                                          //  메세지 출력 후 종료
        perror("pthread_create() error!");
        return -1;
    }

    pthread_join(tid,
                 (void **)&status); //  생성한 스레드가 종료할 때까지 대기.
    printf("Thread %ld exit\n", tid);

    return 0;
}

void *myThread(void *arg) {
    int i = 0;
    int count = *(int *)arg;
    int status = 0;

    printf("Hello, I'm new thread: %ld\n",
           pthread_self()); //  현재 스레드 ID 출력

    for (i = count; i > 0; --i) {
        printf("%d ...\n", i);
    }

    pthread_exit((void *)&status); //  스레드 종료
}
