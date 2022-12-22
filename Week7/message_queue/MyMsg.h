#ifndef __MYMSG_H__
#define __MYMSG_H__

#define MSG_TYPE_CALC 1
#define MSG_TYPE_RSLT 2

#define MSG_SIZE_CALC (sizeof(MsgCalc) - sizeof(long))
#define MSG_SIZE_RSLT (sizeof(MsgRslt) - sizeof(long))

struct __Calc { //  server에게 연산을 요청하기 위한 정보가 담겨있는 구조체
    int x;
    int y;
    char op; //  연산자
};
typedef struct __Calc Calc;

struct __MsgCalc { //  Message Queue를 사용해 Calc의 내용을 전달하기 위한 구조체
    long mtype;
    struct __Calc calc;
};
typedef struct __MsgCalc MsgCalc;

struct __MsgRslt { //  Message Queue를 사용해 Calc의 연산결과를 전달하는 구조체
    long mtype;
    int rslt;
};
typedef struct __MsgRslt MsgRslt;

#endif
