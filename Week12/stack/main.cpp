#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {
    vector<int> myVector(2, 100);
    stack<int> myStack1; //  정수를 담을 수 있는 stack 선언

    //  myVector의 원소를 원소로 가지고 컨테이너 형식이 vector<int>인 stack 생성
    stack<int, vector<int>> myStack2(myVector);

    cout << "Size of myStack1: " << myStack1.size() << endl;
    if (myStack1.empty() == 1) {
        cout << "myStack1 is empty" << endl;
    }

    cout << "size of myStack2: " << myStack2.size() << endl;
    cout << "Top of myStack2: " << myStack2.top() << endl;
    cout << endl;

    //  myStack1에 원소 추가
    myStack1.push(1);
    myStack1.push(2);
    myStack1.push(3);

    cout << "--- After push ---" << endl;
    cout << "size of myStack1: " << myStack1.size() << endl;
    cout << "Top of myStack1: " << myStack1.top() << endl;
    cout << endl;

    //  myStack1, myStack2의 상단 원소 제거
    myStack1.pop();
    myStack2.pop();

    cout << "--- After push ---" << endl;
    cout << "size of myStack1: " << myStack1.size() << endl;
    cout << "Top of myStack1: " << myStack1.top() << endl;

    cout << "size of myStack2: " << myStack2.size() << endl;
    cout << "Top of myStack2: " << myStack2.top() << endl;

    return 0;
}
