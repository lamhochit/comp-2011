//
//  main.cpp
//  COMP_2011_Quiz_1
//
//  Created by 林灝哲 on 15/9/2019.
//  Copyright © 2019 LAM Ho Chit. All rights reserved.
//

#include <iostream>
using namespace std;

int main()
{
    enum color {RED, GREEN, BLUE} x, y;
    int xint, yint;
    
    cin >> xint >> yint;
    x = static_cast<color>(xint);
    
    cout << x << endl;
}

