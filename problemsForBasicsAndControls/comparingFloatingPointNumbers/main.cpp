//
//  main.cpp
//  comparingFloatingPointNumbers
//
//  Created by 林灝哲 on 16/9/2019.
//  Copyright © 2019 LAM Ho Chit. All rights reserved.
//

#include <iostream>
using namespace std;

int main()
{
    float x = 0.1;
    float y = 0.1;
    float product = 10.0 * x;
    
    float sum = 0.0;
    for (int i = 0; i < 10; ++i)
        sum += x;
    
    cout.precision(10);
    cout << boolalpha;
    
    cout << "sum = " << sum << endl;
    cout << "product = " << product << endl;
    cout << "10.0 * x = " << 10.0 * x << endl;
    cout << (sum == product) << endl;
    cout << (x == y) << endl;
}
