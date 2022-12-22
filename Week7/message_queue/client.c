#include "MyMsg.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

int main(int argc, char const *argv[]) {
    key_t mykey = ftok("mymsgkey", 1);    //  Message Queue를 위한 key 생성
    int msqid = msgget(mykey, IPC_CREAT); //  Message Queue 생성

    int x = 0;
    int y = 0;
    char op = 0;

    MsgCalc msgCalc;
    MsgRslt msgRslt;

    puts("Input: [x] [op] [y]");
    while (1) {
        printf("<<< ");
        scanf("%d %c %d", &x, &op, &y); //  Calc 값 입력
        fflush(stdout);                 //  stdout 초기화
        fflush(stdin);                  //  stdin 초기화

        memset(&msgCalc, 0x00,
               sizeof(MsgCalc)); //  MsgCalc을 저장하기 위한 메모리 초기화

        //  Calc 값 선언
        msgCalc.mtype = MSG_TYPE_CALC;
        msgCalc.calc.x = x;
        msgCalc.calc.y = y;
        msgCalc.calc.op = op;

        msgsnd(msqid, &msgCalc, MSG_SIZE_CALC, 0); //  MsgCalc 송신

        memset(
            &msgRslt, 0x00,
            sizeof(MsgRslt)); //  수신한 MsgRslt를 저장하기 위한 메모리 초기화

        msgrcv(msqid, &msgRslt, MSG_SIZE_RSLT, MSG_TYPE_RSLT,
               0); //  server로부터 MsgRslt 수신

        printf(">>> %d\n", msgRslt.rslt); //  MsgRslt 값 출력
    }

    return 0;
}
