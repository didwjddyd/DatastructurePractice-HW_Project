#include "MyMsg.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

void signalHandler(int signum);
int calculate(Calc calc);

key_t mykey = 0;
int msqid = 0;

int main(int argc, char const *argv[]) {
    MsgCalc msgCalc;
    MsgRslt msgRslt;

    mykey = ftok("mymsgkey", 1); //  Message Queue를 위한 key 생성
    msqid = msgget(mykey, IPC_CREAT | 0600); //  Message Queue 생성

    signal(SIGINT, signalHandler);

    while (1) {
        puts("Wait ...");

        memset(
            &msgCalc, 0x00,
            sizeof(MsgCalc)); //  수신한 MsgCalc을 저장하기 위한 메모리 초기화

        msgrcv(msqid, &msgCalc, MSG_SIZE_CALC, MSG_TYPE_CALC,
               0); //  client로부터 MsgCalc 수신

        printf("Receive: %d %c %d\n", msgCalc.calc.x, msgCalc.calc.op,
               msgCalc.calc.y); //  MsgCalc의 내용 출력

        memset(&msgRslt, 0x00,
               sizeof(MsgRslt)); //  MsgRslt를 저장하기 위한 메모리 초기화

        //  MsgRslt 값 선언
        msgRslt.mtype = MSG_TYPE_RSLT;
        msgRslt.rslt = calculate(msgCalc.calc);

        msgsnd(msqid, &msgRslt, MSG_SIZE_RSLT, 0); //  MsgRslt 송신
        printf("Send: %d\n", msgRslt.rslt);        //  송신한 값 출력

        fflush(stdout); //  stdout 초기화
    }

    return 0;
}

void signalHandler(int signum) { //  SIGINT 수신 시 Message Queue 삭제 후 종료
    if (signum == SIGINT) {
        msgctl(msqid, IPC_RMID, NULL);
        exit(0);
    }
}

int calculate(Calc calc) { // Calc의 내용을 사용한 연산
    switch (calc.op) {
    case '+':
        return calc.x + calc.y;
    case '-':
        return calc.x - calc.y;
    case '*':
        return calc.x * calc.y;
    case '/':
        return (int)(calc.x / calc.y);
    default:
        return 0;
    }
}
