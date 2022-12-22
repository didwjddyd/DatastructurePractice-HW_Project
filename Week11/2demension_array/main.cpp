#include <array>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    array<array<int, 8>, 4> arr = {0}; //  8*4 2차원 배열 선언 및 초기화
    array<array<int, 8>, 4>::iterator row; //  2차원 배열 열 반복자
    array<int, 8>::iterator col;           //  2차원 배열 행 반복자

    cout << "elements of arr" << endl;
    //  2중 for문 사용. 열-행 순으로 각 원소 하나씩 출력
    for (row = arr.begin(); row != arr.end(); ++row) {
        for (col = (*row).begin(); col != (*row).end(); ++col) {
            cout << *col << " ";
        }
        cout << endl;
    }
    cout << endl;

    int i = 1;

    //  배열의 각 원소를 1~32로 변경
    for (row = arr.begin(); row != arr.end(); ++row) {
        (*row).fill(i++);
    }

    cout << "value of arr[0][2]: ";
    cout << (arr.front())[2] << endl; //  2차원 배열의 첫 열의 세 번째 원소 지정

    cout << "value of arr[1][3]: ";
    cout << (arr.at(1))[3]
         << endl; //  2차원 배열의 두 번째 열의 네 번째 원소 지정

    cout << "value of arr[2][2]: ";
    cout << (arr.at(2))[2]
         << endl; //  2차원 배열의 세 번째 열의 세 번째 원소 지정

    return 0;
}
