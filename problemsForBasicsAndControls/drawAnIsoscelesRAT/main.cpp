//
//  main.cpp
//  drawAnIsoscelesRAT
//
//  Created by 林灝哲 on 15/9/2019.
//  Copyright © 2019 LAM Ho Chit. All rights reserved.
//

#include <iostream>
using namespace std;

int main()
{
    int size;
    cout << "Enter the size of the RAT: ";
    cin >> size;
    
    for (int i = size; i >= 1; i--)
    {
        for (int j = 1; j <= i; j++)
        {
            cout << "*";
        }
        cout<<endl;
    }
}
