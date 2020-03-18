//
//  main.cpp
//  COMP_2012_L1
//
//  Created by 林灝哲 on 27/2/2020.
//  Copyright © 2020 LAM Ho Chit. All rights reserved.
//

#include <iostream>
using namespace std;
int x = 5;
int& xref = x;
int* xptr = &x;
void xprint()
{
/* File: confusion.cpp */
// An int variable
// A reference variable: xref is an alias of x
// A pointer variable: xptr points to x
    cout << hex << endl; // Print numbers in hexadecimal format
    cout << "x =     " << x     << "\t\tx address     = " << &x    << endl;
    cout << "xref =  " << xref  << "\t\txref address  = " << &xref << endl;
    cout << "xptr =  " << xptr  << "\txptr address  = "   << &xptr << endl;
    cout << "*xptr = " << *xptr << endl;
}
int main() {
    x += 1; xprint();
    xref += 1; xprint();
    xptr = &xref; xprint(); // Now xptr points to xref
return 0; }
