#include "Queue.h"
#include <iostream>

using namespace std;

int main() {
    Queue q1, q2;

    cout << "--- Before push -- " << endl;
    if (q1.empty()) {
        cout << "q1 is empty" << endl;
    }

    if (q2.empty()) {
        cout << "q2 is empty" << endl;
    }

    cout << "size of q1: " << q1.size() << endl;
    cout << "size of q2: " << q1.size() << endl << endl;

    for (int i = 0; i != 10; ++i) {
        q1.push(i);
        q2.push(100 + i);
    }

    cout << "--- After push ---" << endl;
    cout << "size of q1: " << q1.size() << endl;
    cout << "front of q1: " << q1.front() << endl;
    cout << "back of q1: " << q1.back() << endl << endl;

    cout << "size of q2: " << q2.size() << endl;
    cout << "front of q2: " << q2.front() << endl;
    cout << "back of q2: " << q2.back() << endl << endl;

    q1.pop();
    q1.pop();
    q1.pop();

    cout << "--- After pop q1 ---" << endl;
    cout << "size of q1: " << q1.size() << endl;
    cout << "front of q1: " << q1.front() << endl;
    cout << "back of q1: " << q1.back() << endl << endl;

    q1.swap(q2);

    cout << "--- After swap q1 and q2 ---" << endl;
    cout << "size of q1: " << q1.size() << endl;
    cout << "front of q1: " << q1.front() << endl;
    cout << "back of q1: " << q1.back() << endl << endl;

    cout << "size of q2: " << q2.size() << endl;
    cout << "front of q2: " << q2.front() << endl;
    cout << "back of q2: " << q2.back() << endl << endl;

    return 0;
}
