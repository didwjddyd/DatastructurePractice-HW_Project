#include "Queue.h"
#include "DLinkedList.h"

Queue::Queue() { queue = DLinkedList(); }

bool Queue::empty() { return queue.isEmpty(); }

int Queue::size() { return queue.getCount(); }

int Queue::front() { return queue.getFornt(); }

int Queue::back() { return queue.getBack(); }

void Queue::push(int data) { queue.addBack(data); }

void Queue::pop() { queue.removeFront(); }

void Queue::swap(Queue &x) {
    DLinkedList temp;
    copy(x.queue, temp);

    x.queue.clear();
    copy(queue, x.queue);

    queue.clear();
    queue = temp;
}
