#include "DLinkedList.h"

#include <cstdlib>
#include <iostream>

// ListNode implementation
ListNode::ListNode() {
    data = -1;
    next = NULL;
    prev = NULL;
}

void ListNode::setData(int data) { this->data = data; }

int ListNode::getData() { return data; }

ListNode *ListNode::nextNode() { return next; }

ListNode *ListNode::prevNode() { return prev; }

void ListNode::setNext(ListNode *target) { next = target; }

void ListNode::setPrev(ListNode *target) { prev = target; }

// DLinkedList implementation
DLinkedList::DLinkedList() {
    nodeCount = 0;
    head = NULL;
    tail = NULL;
}

bool DLinkedList::isEmpty() {
    if (nodeCount == 0) {
        return true;
    } else {
        return false;
    }
}

void DLinkedList::addFront(int data) {
    ListNode *newNode = new ListNode();

    newNode->setData(data);

    if (nodeCount == 0) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->setNext(head);
        head->setPrev(newNode);
        head = head->prevNode();
    }

    nodeCount++;
}

void DLinkedList::addBack(int data) {
    ListNode *newNode = new ListNode();

    newNode->setData(data);

    if (nodeCount == 0) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->setPrev(tail);
        tail->setNext(newNode);
        tail = tail->nextNode();
    }

    nodeCount++;
}

void DLinkedList::add(ListNode *previous, int data) {
    ListNode *newNode = new ListNode();
    ListNode *nextNode = previous->nextNode();

    newNode->setData(data);

    newNode->setNext(nextNode);
    nextNode->setPrev(newNode);

    newNode->setPrev(previous);
    previous->setNext(newNode);

    nodeCount++;
}

void DLinkedList::removeFront() {
    ListNode *target = head;

    head = head->nextNode();
    nodeCount--;
    delete target;
}

void DLinkedList::removeBack() {
    ListNode *target = tail;

    tail = tail->prevNode();
    nodeCount--;
    delete target;
}

void DLinkedList::printList() {
    if (isEmpty()) {
        return;
    }

    ListNode *cursor = head;
    while (cursor != NULL) {
        std::cout << cursor->getData() << " ";
        cursor = cursor->nextNode();
    }
    std::cout << std::endl;
}

int DLinkedList::getFornt() { return head->getData(); }

int DLinkedList::getBack() { return tail->getData(); }

int DLinkedList::getCount() { return nodeCount; }

ListNode *DLinkedList::getHead() { return head; }

ListNode *DLinkedList::getTail() { return tail; }

void DLinkedList::clear() {
    while (head != NULL) {
        removeFront();
    }
}

// other function implementation
void copy(DLinkedList &source, DLinkedList &target) {
    ListNode *cursor = source.getHead();

    while (cursor != NULL) {
        target.addBack(cursor->getData());
        cursor = cursor->nextNode();
    }
}
