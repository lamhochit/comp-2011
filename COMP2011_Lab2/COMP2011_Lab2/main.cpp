//
//  main.cpp
//  COMP2011_Lab2
//
//  Created by 林灝哲 on 15/9/2019.
//  Copyright © 2019 LAM Ho Chit. All rights reserved.
//

#include <iostream>
using namespace std;

int main()
{
    bool wolfR, sheepR, cabbageR, boatR; // indicates position of WSC
    wolfR = sheepR = cabbageR = boatR = 0; //0 = on the left, 1 = on the right
    char target;
    
    cout << "****************************\n" << "Wolf, Sheep and Cabbage Game\n" << "****************************\n" << endl;
    cout << "Left  --------------------  Right\n" << "w s c\n" << "boat\n" << endl;
    cout << "Game Start!" << endl;
    
    do {
        cout << "Item to carry (w: wolf, s: sheep, c: cabbage, n: nothing): " << endl;
        cin >> target;
        switch (target)
        {
            case 'w':
            {
                if (boatR == wolfR)
                {
                    boatR = !boatR;
                    wolfR = !wolfR;
                } else
                {
                    cout << "They are not on the same side!" << endl;
                }
                break;
            }
            case 's':
            {
                if (boatR == sheepR)
                {
                    boatR = !boatR;
                    sheepR = !sheepR;
                } else
                {
                    cout << "They are not on the same side!" << endl;
                }
                break;
            }
            case 'c':
            {
                if (boatR == cabbageR)
                {
                    boatR = !boatR;
                    cabbageR = !cabbageR;
                } else
                {
                    cout << "They are not on the same side!" << endl;
                }
                break;
            }
            case 'n' : boatR = !boatR; break;
        }
        cout << "Left  --------------------  Right\n";
        if (!wolfR)
            cout << "w ";
        else
            cout << "  ";
        if (!sheepR)
            cout << "s ";
        else
            cout << "  ";
        if (!cabbageR)
            cout << "c ";
        else
            cout << "  ";
        cout << "                      ";
        if (wolfR)
            cout << "w ";
        else
            cout << "  ";
        if (sheepR)
            cout << "s ";
        else
            cout << "  ";
        if (cabbageR)
            cout << "c ";
        else
            cout << "  ";
        if (!boatR)
            cout << endl << "boat\n\n";
        else
            cout << endl << "                            boat\n\n";
        
        if ((boatR && wolfR && !cabbageR && !sheepR) || (!boatR && !wolfR && cabbageR && sheepR))
        {
            cout << "Sheep eats cabbage!" << endl;
            break;
        }
        if ((boatR && !wolfR && cabbageR && !sheepR) || (!boatR && wolfR && !cabbageR && sheepR))
        {
            cout << "Wolf eats sheep" << endl;
            break;
        }
    
    } while (!wolfR || !sheepR || !cabbageR);
    if (wolfR && sheepR && cabbageR) {
    cout << "Wolf, sheep and cabbage are all on right side!\n"
    << "Congratulations! You win!" << endl;
    }
    return 0;
}
