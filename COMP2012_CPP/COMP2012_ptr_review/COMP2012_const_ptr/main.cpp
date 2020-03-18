#include <iostream> /* File: const-char-ptrs2.cpp */
using namespace std;

int main() {
    char s[] = "COMP2012"; // Usual initialization in the past
    char p[] {"MATH1013"}; // C++11 style of uniform initialization
    
    char* pcc {s};
    cout << &pcc << endl;
    cout << pcc[3] << endl;
    
    pcc[3] = '4';
    cout << pcc << endl;
    cout << &pcc[3] << endl;
    
    
    pcc = p;
    cout << &pcc << endl;

    
    return 0;
}
