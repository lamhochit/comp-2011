//
//  main.cpp
//  jacksonLabw
//
//  Created by 林灝哲 on 15/9/2019.
//  Copyright © 2019 LAM Ho Chit. All rights reserved.
//

#include <iostream>
using namespace std;

int main() {
    cout<<"**********"<<endl;
    cout<<"Wolf, Sheep and Cabbage Game"<<endl;
    cout<<"**********"<<endl<<endl;
    cout<<"Left ------------------ Right"<<endl;
    cout<<"w s c"<<endl<<"boat"<<endl<<endl;
    cout<<"Game Start!"<<endl;
    bool wolf = true;
    bool sheep = true;
    bool cabbage = true;
    bool boat = true;
    char input;
    do {
        cout<<"Item to carry (w: wolf, s: sheep, c: cabbage, n: nothing): "<<endl;
        cin>>input;
        switch(input){
            case 'w': if(wolf == false){wolf = true;}else {wolf = false;}break;
            case 's': if(sheep == false){sheep = true;}else {sheep = false;}break;
            case 'c': if(cabbage == false){cabbage = true;}else {cabbage = false;}break;}
        if (boat == true){boat = false;}else{boat = true;}
        cout<<"Left ------------------ Right"<<endl;
        if (wolf == true){cout<<"w";cout<<" ";}
        else cout<<"  ";
        if (sheep == true){cout<<"s";cout<<" ";}
        else cout<<"  ";
        if (cabbage == true){cout<<"c";cout<<" ";}
        else cout<<"  ";
        cout<<"                  ";
        if (wolf == false){cout<<"w";cout<<" ";}
        else cout<<"  ";
        if (sheep == false){cout<<"s";cout<<" ";}
        else cout<<"  ";
        if (cabbage == false){cout<<"c";cout<<" ";}
        else cout<<"  ";
        cout<<endl;
        if (boat == true){cout<<"boat";}
        else {cout<<"                        boat";}
        cout<<endl;
    }while (wolf == true || sheep == true || cabbage == true || boat == true);
    cout<<"Wolf, sheep and cabbage are on right side!"<<endl<<"Congratulations! You win!";
    return 0;
}
