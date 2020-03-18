//
//  main.cpp
//  COMP2011_Lab3
//
//  Created by 林灝哲 on 22/9/2019.
//  Copyright © 2019 LAM Ho Chit. All rights reserved.
//

#include <iostream>
using namespace std;

void isoscelesTriangle (int height, int num)
{
    for (int i = 0; i < num; i++)
        for (int j = 0; j < height; j++)
        {
            char cr = j + 65;
            for (int k = 0; k < height - j; k++)
                cout << " ";
            for (int m = 0; m < j*2+1; m++)
                cout << cr;
            cout << endl;
        }
}

void reverseIsoscelesTriangle(int height, int num)
{
    for (int i = 0; i < num; i++)
        for (int j = 0; j < height; j++)
        {
            char cr = j + 65;
            for (int k = 0; k < j + 1; k++)
                cout << " ";
            for (int m = 0; m < height*2 - 1 - j*2; m++)
                cout << cr;
            cout << endl;
        }
}

void diamond(int height, int num)
{
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < height + 1; j++)
        {
            char cr = j + 65;
            for (int k = 0; k < height + 1 - j; k++)
                cout << " ";
            for (int m = 0; m < j*2+1; m++)
                if ((m == 0) || (m == j*2))
                    cout << cr;
                else
                    cout << " ";
            cout << endl;
        }
        for (int j = 0; j < height; j++)
        {
            char cr = (height - j - 1) + 65;
            for (int k = 0; k < j+2; k++)
                cout << " ";
            for (int m = 0; m < height*2 - 1 - j*2; m++)
                if ((m == 0) || (m == height*2 - j*2 - 2))
                    cout << cr;
                else
                    cout << " ";
            cout << endl;
        }
        
    }
}

void candies(int height, int num)
{
    for (int i = 0; i < num; i++)
    {
        reverseIsoscelesTriangle(height + 1, 1);
        diamond(height, 1);
        isoscelesTriangle(height + 1, 1);
        cout<<endl<<endl;
    }

}

int main()
{
    int choice;
    int x, y;
    
    cout << "Welcome to the Shape Printer!" << endl << endl;
    cout << "1: Draw letter isosceles triangle." << endl;
    cout << "2: Draw letter reverse isosceles triangle." << endl;
    cout << "3: Draw letter diamond." << endl;
    cout << "4: Draw letter candy." << endl;
    cout << "0: Exit Program" << endl;
    cout << "Input the type of shape you want to print, or exit program: ";
    cin  >>  choice;
    
    switch (choice)
    {
        case 1:
            cout << "Please input the height of the isosceles triangle: ";
            cin >> x;
            cout << "Please input the number of the isosceles triangles: ";
            cin >> y;
            isoscelesTriangle(x, y);
            break;
        case 2:
            cout << "Please input the height of the letter reverse isosceles triangle: ";
            cin >> x;
            cout << "Please input the number of the letter reverse isosceles triangles: ";
            cin >> y;
            reverseIsoscelesTriangle(x, y);
            break;
        case 3:
            cout << "Please input the height/2 of the letter diamond: ";
            cin >> x;
            cout << "Please input the number of letter diamonds: ";
            cin >> y;
            diamond(x, y);
            break;
        case 4:
            cout << "Please input the height of the candy: ";
            cin >> x;
            cout << "Please input the number of candies: ";
            cin >> y;
            candies(x, y);
            break;
        case 0:
            return 0;
            break;
    }
    
}
