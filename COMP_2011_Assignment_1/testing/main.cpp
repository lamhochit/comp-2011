//
//  main.cpp
//  testing
//
//  Created by 林灝哲 on 1/10/2019.
//  Copyright © 2019 LAM Ho Chit. All rights reserved.
//
#include <iostream>
using namespace std;

int power(int a, int b) {
    int out = a;
    if (b==0)
        return 1;
    for (int i = 1; i < b; i++)
        out *= a;
    return out;
}

/**
 * Task 1
 * This function returns a boolean value indicating whether the input n is a ping-pong number
 * The input n is a non-negative integer
 * Single digits are ping-pong numbers
 */
bool is_pingpong(int n) {
    // TODO: start your coding here
    int digitCount = 0;
    int num = n;
    
    while (num>0)
    {
        num = num/10;
        digitCount++;
    }
    
    if (n/10 < 1)
        return true;
    else
        for (int i = 1; i < digitCount; i++)
        {
            //Find two integers and compare
            int front, end;
            front = n%power(10,i+1)/power(10, i);
            end = n%power(10,i)/power(10, i-1);
            if (abs(front-end) != 1)
                return false;
        }
    return true;
}

void print_pingpong(int m, int n) {
    // TODO: start your coding here
    int count = 0;
    for (int i = m; i <= n; i++)
    {
        count += 1;
        cout << i << " ";
        if ((count%5 == 0) || (i == n))
            cout << endl;
    }
    cout << "--------------------------------------------------------------------------------" << endl;
}






void print_pingpong_histogram(int m, int n, int num_bins, char bar_char) {
    // TODO: start your coding here
    int binRange;
    const int conBinRange = (n - m + 1)/num_bins;
    for (int i = 0; i < num_bins; i++)
    {
        int count = 0;
        if (i < num_bins - 1)
            binRange = (n - m + 1)/num_bins;
        else
            binRange = (n - m + 1)/num_bins + (n - m + 1)%num_bins;
        for (int j = 0; j < binRange; j++)
        {
            if (is_pingpong(i*conBinRange + j))
                count += 1;
        }
        int histCount = (count%10 == 0)?(count/10):(count/10 + 1);
        for (int i = 0; i < histCount; i++)
            cout << bar_char;
        cout << endl;
        
    }
    cout << "--------------------------------------------------------------------------------" << endl;
}
int kth_digit_from_right(int n, int k) {
    // TODO: start your coding here
    int target;
    int num = n;
    int digitCount = 0;
    while (num>0)
    {
        num = num/10;
        digitCount++;
    }
    
    if ((k < 0) || (k > digitCount))
        return -1;
    else
        target = n%power(10,k)/power(10, k-1);
    return target;
}


int main() {
  
    
    cout << kth_digit_from_right(12345567,9);
    
    return 0;
}
