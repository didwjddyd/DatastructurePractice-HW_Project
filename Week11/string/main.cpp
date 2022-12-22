#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {
    string str1 = "Hello World!";
    cout << "str1: " << str1 << endl;

    string::reverse_iterator rit; //  str1의 역방향 반복자
    cout << "str1 (reverse): ";
    //  str1을 뒤집어서 출력. !dlroW olleH
    for (rit = str1.rbegin(); rit != str1.rend(); ++rit) {
        cout << *rit;
    }
    cout << endl << endl;

    string str2 = "Bonjour!";
    cout << "str2: " << str2 << endl << endl;

    str1.swap(str2); //  str1과 str2의 문자열 교환

    //  swap을 사용해 서로 문자열이 반대로 출력되는 것을 볼 수 있음
    cout << "--- After swap ---" << endl;
    cout << "str1: " << str1 << endl; //  Bonjour!
    cout << "str2: " << str2 << endl; //  Hello World!

    return 0;
}
