#include <iostream>
using namespace std;

int main()
{
    int x[] = {11, 22, 33, 44};
    int* y = x;
    
    for (int j = 0; j < sizeof(x)/sizeof(int); ++j)
        y[j] += 100;
    for (int j = 0; j < sizeof(x)/sizeof(int); ++j)
        cout << x[j] << endl;
    return 0;
}
