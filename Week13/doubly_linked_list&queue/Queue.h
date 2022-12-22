#ifndef _QUEUE_H
#define _QUEUE_H

#include "DLinkedList.h"

class Queue {
  public:
    Queue();

    bool empty();
    int size();
    int front();
    int back();
    void push(int data);
    void pop();
    void swap(Queue &x);

  private:
    DLinkedList queue;
};

#endif
