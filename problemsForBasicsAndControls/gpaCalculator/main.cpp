//
//  main.cpp
//  gpaCalculator
//
//  Created by 林灝哲 on 16/9/2019.
//  Copyright © 2019 LAM Ho Chit. All rights reserved.
//

#include <iostream>
using namespace std;

int main()
{
    float gpaCumulator = 0.0;
    enum grade {A = 4, B = 3, C = 2, D = 1, F = 0};
    int creditCumulator = 0;
    int cred;
    char grad;
    cin >> grad;
    cout << grad;
    do {
        cout << "No. of credits of your course (0 to stop): ";
        cin >> cred;
        if (cred != 0)
        {
            cout << endl << "Your letter grade (A, B, C, D or F): ";
            cin >> grad;
            creditCumulator += cred;
            gpaCumulator += grad * cred;
            cout <<endl;
        }
        else
        {
            cout << "you have taken a total of " << creditCumulator << " ..." << endl;
            cout << "and your GPA is " << gpaCumulator/creditCumulator << endl;
        }
    } while (cred != 0);
}
