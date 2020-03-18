//
//  main.cpp
//  problemsForBasicsAndControls
//
//  Created by 林灝哲 on 15/9/2019.
//  Copyright © 2019 LAM Ho Chit. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
    srand(time(0));
    int target = rand()%100 + 1;
    int guess;
    int player = 1;
    int high = 100, low = 1;
    
    do {
        cout << "Player " << player << ", please enter your guess:" << endl;
        cin >> guess;
        if (guess < high && guess > low)
        {
        if (guess == target)
        {
            cout << "Player " << player << ", you win!" << endl;
        }
        else
        {
            if (guess > target)
            {
                cout << "Sorry, the answer is smaller than " << guess << endl;
            }
            else
            {
                cout << "Sorry the answer is larger than " << guess << endl;
            }
            player = player%2 + 1;
        }
        }
        else
        {
            cout << "Your input is invalid" << endl;
        }
        
    } while (guess != target);
    
}
