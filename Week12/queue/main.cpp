#include <iostream>
#include <list>
#include <queue>

using namespace std;

int main(int argc, char const *argv[]) {
    list<int> myList(2, 100);
    queue<int> myQueue1; //  정수를 담을 수 있는 큐 생성

    //  myList의 원소를 원소로 가지고 컨테이너 형식이 list<int>인 큐 생성
    queue<int, list<int>> myQueue2(myList);

    cout << "Size of myQueue1: " << myQueue1.size() << endl;
    if (myQueue1.empty() == 1) {
        cout << "myQueue1 is empty" << endl << endl;
    }

    cout << "Size of myQueue2: " << myQueue2.size() << endl;
    cout << "Front of myQueue2: " << myQueue2.front() << endl;
    cout << "Back of myQueue2: " << myQueue2.back() << endl;
    cout << endl;

    //  myQueue1, myQueue2에 원소 추가
    myQueue1.push(1);
    myQueue1.push(2);
    myQueue1.push(3);
    myQueue2.push(200);

    cout << "--- After push ---" << endl;
    cout << "Size of myQueue1: " << myQueue1.size() << endl;
    cout << "Front of myQueue1: " << myQueue1.front() << endl;
    cout << "Back of myQueue1: " << myQueue1.back() << endl;

    cout << "Size of myQueue2: " << myQueue2.size() << endl;
    cout << "Front of myQueue2: " << myQueue2.front() << endl;
    cout << "Back of myQueue2: " << myQueue2.back() << endl;
    cout << endl;

    //  myQueue1, myQueue2의 front에서 원소 제거
    myQueue1.pop();
    myQueue2.pop();
    myQueue2.pop();

    cout << "--- After pop ---" << endl;
    cout << "Size of myQueue1: " << myQueue1.size() << endl;
    cout << "Front of myQueue1: " << myQueue1.front() << endl;
    cout << "Back of myQueue1: " << myQueue1.back() << endl;

    cout << "Size of myQueue2: " << myQueue2.size() << endl;
    cout << "Front of myQueue2: " << myQueue2.front() << endl;
    cout << "Back of myQueue2: " << myQueue2.back() << endl;

    return 0;
}
