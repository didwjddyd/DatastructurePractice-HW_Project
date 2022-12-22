#include <iostream>
#include <list>

using namespace std;

int main() {
    double myDoubles[] = {12.15, 2.72,  73.0,  12.77, 3.14,
                          12.77, 73.55, 72.25, 15.3,  72.25};

    //  myDoubles[0] ~ myDoubles[9]를 원소로 하는 연결리스트 생성
    list<double> myList(myDoubles, myDoubles + 10);
    list<double>::iterator it; //  myList 반복자 생성

    cout << ">> nodes of myList: ";
    //  myList 원소 출력. 반복자 사용
    for (it = myList.begin(); it != myList.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "<< myList.push_front(1.4);" << endl;
    myList.push_front(1.4); // myList의 맨 앞에 1.4 추가

    cout << "<< myList.push_back(1.4);" << endl;
    myList.push_back(1.4); //  myList의 맨 뒤에 1.4 추가

    cout << ">> nodes of myList: ";
    for (it = myList.begin(); it != myList.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "<< myList.sort();" << endl;
    myList.sort(); //  myList 원소 오름차순 정렬

    cout << ">> nodes of myList: ";
    for (it = myList.begin(); it != myList.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    myList.unique(); //  중복 노드 삭제
    cout << ">> nodes of myList: ";
    for (it = myList.begin(); it != myList.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    return 0;
}
