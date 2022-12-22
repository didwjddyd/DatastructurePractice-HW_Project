#include <pthread.h>
#include <stdio.h>

void *myThread1(void *arg);
void *myThread2(void *arg);
void cleanupHandler(void *arg);

pthread_mutex_t mutex;
int sharedNum = 0;

int main(int argc, char const *argv[]) {
    //  스레드 ID
    pthread_t tid1 = 0;
    pthread_t tid2 = 0;

    // 스레드 종료값을 저장할 변수
    int *status;

    pthread_mutex_init(&mutex, NULL); //  뮤텍스 초기화.

    //  스레드 2개 생성. 오류 발생 시 오류 메세지 출력 후 뮤텍스 해제
    if (pthread_create(&tid1, NULL, myThread1, NULL)) {
        perror("pthread_create() error!");
        goto END;
    }

    if (pthread_create(&tid2, NULL, myThread2, NULL)) {
        perror("pthread_create() error!");
        goto END;
    }

    //  스레드 2개가 종료할 때까지 기다림
    pthread_join(tid1, (void **)&status);
    pthread_join(tid1, (void **)&status);

END:
    pthread_mutex_destroy(&mutex);

    return 0;
}

void *myThread1(void *arg) {
    int i = 0;
    int status = 0;

    pthread_cleanup_push(cleanupHandler,
                         "Thread 1"); //  cleanupHandler를 스택에 저장

    pthread_mutex_lock(&mutex); //  뮤텍스 잠금
    puts("Thread1");
    for (i = 0; i < 5; ++i) {
        sharedNum += i; //  sharedNum은 0부터 시작
        printf("%d ", sharedNum);
    }
    puts("");

    pthread_cleanup_pop(1); //  저장해둔 핸들러 실행 후 삭제
    pthread_exit((void *)&status);
}

void *myThread2(void *arg) {
    int i = 0;
    int status = 0;

    pthread_cleanup_push(cleanupHandler,
                         "Thread 2"); //  cleanupHandler를 스택에 저장

    pthread_mutex_lock(&mutex); //  뮤텍스 잠금
    puts("Thread2");
    for (i = 0; i < 5; ++i) {
        sharedNum += i; //  1번 스레드에서 사용했으므로 10부터 시작
        printf("%d ", sharedNum);
    }
    puts("");

    pthread_cleanup_pop(1); //  저장해둔 핸들러 실행 후 삭제
    pthread_exit((void *)&status);
}

void cleanupHandler(void *arg) {
    pthread_mutex_unlock(&mutex); //  뮤텍스 해제
    printf("Cleanup: %s\n", (char *)arg);
}
