//============================================================================
// Name        : pa1_skeleton.cpp
// Author      : liuhao
// Version     : PA1 COMP2011 Fall 2019
// Copyright   : COMP2011 teaching team
// Description : Ping-pong number
//============================================================================

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

/**
 * Task 2
 * This function prints all the ping-pong number in range [m, n] five in a row in ascending order
 * Inputs m and n are non-negative integers, and m < n
 * m and n are included in the range
 * Use cout for print
 * The numbers printed within a row is separated by a space (" ")
 * Additional spaces are allowed at the beginning or end of each row, but not allowed between numbers printed
 * Additional newlines are allowed at the beginning or end of all the output, but not allowed in the middle
 * Make sure nothing else is printed out
 */
void print_pingpong(int m, int n) {
    // TODO: start your coding here
    int count = 0;
    for (int i = m; i <= n; i++)
    {
        if (is_pingpong(i))
        {
        count += 1;
        cout << i << " ";
        if ((count%5 == 0) && (i != n))
            cout << endl;
        }
        
    }
}

/**
 * Task 3
 * This function prints the ping-pong number counting histogram in range [m, n]
 * Inputs m and n are non-negative integers, num_bins is a positive integer, m < n
 * First split the range [m, n] into (num_bins) bins
 * E.g. [0, 10002] into 5 bins: [0, 1999], [2000, 3999], [4000, 5999], [6000, 7999], [8000, 10002]
 * Except for the last bin, each bin contains floor((n - m + 1)/num_bins) numbers
 * Last bin must end at n, and it might have more elements
 * For each bin range, first count the number of ping-pong numbers, denoted by count
 * if count == 0, bin is empty, print a blank row
 * else print a row of ceiling(count / 10) bar_chars (e.g. '*')
 * After each print of a bin, a newline should be inserted
 * Additional newlines are allowed after the last bin
 */
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
            if (is_pingpong(m + i*conBinRange + j))
                count += 1;
        }
        int histCount = (count%10 == 0)?(count/10):(count/10 + 1);
        for (int i = 0; i < histCount; i++)
            cout << bar_char;
        if (i < num_bins - 1) cout << endl;
    }
}

/**
 * Task 4
 * This function returns k-th digit of a non-negative integer n from right
 * The rightmost digit has index 1
 * k can be any integer
 * Returns -1 if given index k is out of bound (i.e. k <= 0 or k is larger than the total number of digits of n)
 */
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

/**
 * Task 5
 * Check whether n is a generalized ping-pong number with given step and digit-diff
 * n >= 0, diff >= 0, and step > 0
 */
bool is_generalized_pingpong(int n, int step, int diff) {
    // TODO: start your coding here
    int num = n;
    int digitCount = 0;
    while (num>0)
    {
        num = num/10;
        digitCount++;
    }
    for (int i = 1; i < digitCount - step; i++)
    {
        int diffTest = abs(kth_digit_from_right(n, i+step) - kth_digit_from_right(n, i));
        if (diffTest != diff)
            return false;
    }
    return true;
}

int main() {
    cout << "----------------------------------------------------------------------" << endl;
    cout << "Welcome to the Main program of Assignment 1" << endl;
    cout << "You can check whether your code works properly with our below examples" << endl;
    cout << "----------------------------------------------------------------------" << endl;
    
    cout << boolalpha;
    cout << endl;
    cout << "1. Check whether a given number is a ping-pong number" << endl;
    cout << "Is 3 a ping-pong number: " << is_pingpong(3) << endl;
    cout << "Is 10 a ping-pong number: " << is_pingpong(10) << endl;
    cout << "Is 14 a ping-pong number: " << is_pingpong(14) << endl;
    cout << "Is 100 a ping-pong number: " << is_pingpong(100) << endl;
    cout << "Is 101 a ping-pong number: " << is_pingpong(101) << endl;
    cout << "Is 656787 a ping-pong number: " << is_pingpong(656787) << endl;
    cout << "----------------------------------------------------------------------" << endl;
    
    cout << endl;
    cout << "2. Print all the ping-pong numbers from 0 to 100" << endl;
    print_pingpong(0, 100);
    cout << endl;
    cout << "----------------------------------------------------------------------" << endl;
    
    cout << endl;
    cout << "3.1 Print the ping-pong histogram from 0 to 10000 with 5 bins" << endl;
    print_pingpong_histogram(0, 10000, 5, '*');
    cout << endl;
    
    cout << "3.2 Print the ping-pong histogram from 20 to 52 with 6 bins" << endl;
    print_pingpong_histogram(20, 52, 6, '#');
    cout << endl;
    cout << "----------------------------------------------------------------------" << endl;
    
    cout << endl;
    cout << "4. Find the k-th digit" << endl;
    cout << "The first digit of 76: " << kth_digit_from_right(76, 1) << endl;
    cout << "The 4-th digit of 654321: " << kth_digit_from_right(654321, 4) << endl;
    cout << "The 8-th digit of 30283: " << kth_digit_from_right(30283, 8) << endl;
    cout << "The (-2)-th digit of 30283: " << kth_digit_from_right(30283, -2) << endl;
    cout << "----------------------------------------------------------------------" << endl;
    
    cout << endl;
    cout << "5. Check whether a given number is a (step, diff)-ping-pong number" << endl;
    cout << boolalpha;
    cout << "Is 3 a (2, 2)-ping-pong number: " << is_generalized_pingpong(3, 2, 2) << endl;
    cout << "Is 4455463 a (2, 1)-ping-pong number: " << is_generalized_pingpong(4455463, 2, 1) << endl;
    cout << "Is 4061806 a (2, 2)-ping-pong number: " << is_generalized_pingpong(4061806, 2, 2) << endl;
    cout << "----------------------------------------------------------------------" << endl;
}
