#ifndef _DLINKEDLIST_H
#define _DLINKEDLIST_H

class ListNode {
  public:
    ListNode();

    void setData(int data);
    int getData();

    ListNode *nextNode();
    ListNode *prevNode();

    void setNext(ListNode *target);
    void setPrev(ListNode *target);

  private:
    int data;

    ListNode *next; // next node
    ListNode *prev; // previous node
};

class DLinkedList {
  public:
    DLinkedList();

    bool isEmpty();

    void addFront(int data);
    void addBack(int data);

    void add(ListNode *previous, int data);

    void removeFront();
    void removeBack();

    void printList();

    void clear();

    int getFornt();
    int getBack();
    int getCount();
    ListNode *getHead();
    ListNode *getTail();

  private:
    int nodeCount;

    ListNode *head; // head of list
    ListNode *tail; // tail of list
};

void copy(DLinkedList &source, DLinkedList &target);

#endif
