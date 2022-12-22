#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {
    vector<int> v(3); //  크기가 3인 정수형 벡터 생성 및 0으로 초기화
    vector<int>::iterator it; //  정수형 벡터의 반복자

    cout << "size of v: " << v.size() << endl; // 벡터의 크기 출력
    cout << "capacity of v: " << v.capacity() << endl; //  벡터의 용량 출력
    cout << "elements of v: ";
    //  벡터의 원소 출력. index 사용
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << endl << endl;

    //  벡터의 원소를 i + 1로 변경
    for (int i = 0; i < v.size(); ++i) {
        v[i] = i + 1;
    }

    //  벡터의 끝에 10~14 추가
    for (int i = 10; i < 15; ++i) {
        v.push_back(i);
    }

    cout << "--- After push back ---" << endl;
    cout << "size of v: " << v.size()
         << endl; //  push_back() 사용 후 벡터 크기 출력
    cout << "capacity of v: " << v.capacity()
         << endl; //  push_back() 사용 후 벡터 용량 출력
    cout << "elements of v: ";
    //  push_back() 사용 후 벡터 원소 출력. index 사용
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << endl << endl;

    //  벡터 뒤의 원소 2개 제거
    v.pop_back();
    v.pop_back();

    cout << "--- After pop back ---" << endl;
    cout << "size of v: " << v.size()
         << endl; //  pop_back() 사용 후 벡터 크기 출력
    cout << "capacity of v: " << v.capacity()
         << endl; //  pop_back() 사용 후 벡터 용량 출력
    cout << "elements of v: ";
    //  pop_back() 사용 후 벡터 원소 출력. index 사용
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << endl;

    return 0;
}
