//
//  precision.cpp
//  COMP2011_Lecture
//
//  Created by 林灝哲 on 12/9/2019.
//  Copyright © 2019 LAM Ho Chit. All rights reserved.
//

#include <iostream>
using namespace std;

int main()
{
    float x = 0.1;
    float product = 10.0 * x;
    
    float sum = 0.0;
    for (int i = 0; i < 10; ++i)
        sum += x;
    cout << boolalpha;
    cout << precision(10);
    cout << "sum = " << sum << endl;
    cout << "product = " << product << endl;
    cout << (sum == product) << endl;
    
    return 0;
}

