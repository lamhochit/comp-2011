#include <iostream> /* File: const-char-pointer.cpp */
using namespace std;

int main()
{
    int array_size;
    cin >> array_size;
    
    char* x = 'hello';
        
    for (int i = 0; i < array_size; ++i)
        cout << x[i] << endl;
}

