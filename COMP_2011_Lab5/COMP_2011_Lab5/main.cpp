/*
 * File: lab5_skeleton.cpp
 *
 * Lab 5: Recursion - Same or Assimilation
 *
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

/* SIZE of the board */
const int BOARD_SIZE = 10;

// FUNCTION 1
/**
 TODO: Define the function, initialize_symbols(), with appropriate header and body
 1st parameter: the game board array
 2nd parameter: the number of symbols
 
 The function should initialize all array elements by randomly assigning a symbol from
 a set of characters. E.g. if 2nd parameter's value is 3, the 3 characters are 'A', 'B', 'C'.
 **/
// Add the function header and body here
void initialize_symbols(char sym[][BOARD_SIZE], int num_of_symbols)
{
    srand(time(0));
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            int sb = rand() % num_of_symbols + 1;
            sym[i][j] = static_cast<char>(sb + 64);
        }
}


// FUNCTION 2
/**
 TODO: Define the function, print_game_board(), with appropriate header and body
 1st parameter: the game board array
 
 The function should print the board (i.e. symbol_array).
 **/
// Add the function header and body here
void print_game_board(char sym[][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        cout << " --- --- --- --- --- --- --- --- --- --- " << endl;
        cout << "| ";
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            cout << sym[i][j] << " | ";
        }
        cout << endl;
    }
    cout << " --- --- --- --- --- --- --- --- --- --- " << endl << endl;
}



// FUNCTION 3
/**
 TODO: Define the function, update_symbol_array_recursive(), with appropriate header and body
 1st parameter: the array symbol_array
 2nd parameter: the old symbol to be replaced
 3rd parameter: the new symbol to be filled
 4th parameter: row index of the position to start the replacement
 5th parameter: col index of the position to start the replacement
 
 The function MUST update the game board with new symbol using RECURSION.
 It starts with a given position (4th & 5th parameters).
 - If its symbol is not the same as the old symbol, do nothing.
 - Otherwise, if the symbol is the same as the old symbol, it is replaced by the new symbol,
 and then recursively update the symbols of all array elements which are connected with it (i.e. the 4 elements
 which are north, south, west and east of it).
 
 **/
// Add the function header and body here
void update_symbol_array_recursive(char sym[][BOARD_SIZE], char old_sym, char new_sym, int row, int col)
{
    if (sym[row][col] == old_sym)
    {
        sym[row][col] = new_sym;
        if (row != BOARD_SIZE - 1)
            update_symbol_array_recursive(sym, old_sym, new_sym, row + 1, col);
        if (col != BOARD_SIZE - 1)
            update_symbol_array_recursive(sym, old_sym, new_sym, row, col + 1);
    }
}


// FUNCTION 4
/**
 TODO: Define the function, check_win(), with appropriate header and body
 1st parameter: the game board array
 
 The function returns true if the user wins the game, i.e. all elements are of the same symbol.
 Otherwise, returns false.
 **/
// Add the function header and body here
bool check_win(char sym[][BOARD_SIZE])
{
    char target = sym[0][0];
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            if (sym[i][j] != target)
                return false;
    return true;
}


/**
 Given: the funtion, input_validation(), will check whether the new symbol is
 a valid symbol, i.e. among the set of num_of_symbols characters.
 1st parameter: the game board array
 2nd parameter: the new sybmol
 3rd parameter: the number of symbols
 **/
bool input_validation(const char sym[][BOARD_SIZE], char new_symbol, int num_of_symbols)
{
    if(new_symbol == sym[0][0])
    {
        cout << "Please input a different symbol..." << endl;
        return false;
    }
    
    if(!(new_symbol - 'A' < num_of_symbols && new_symbol >= 'A'))
    {
        cout << "Please input a correct symbol..." << endl;
        return false;
    }
    
    return true;
}

/**
 Given: the main() function
 **/
int main()
{
    char symbol_array[BOARD_SIZE][BOARD_SIZE]; // a two-dimension array to store the symbols
    int num_of_symbols; // number of different symbols
    int max_step_num; // number of maximum steps for winning game
    
    cout << "*************************" << endl << "Same or Assimilation Game" << endl
    << "*************************" << endl << endl;
    cout << "Please input the number of symbols: ";
    cin >> num_of_symbols;
    cout << "Please input the maximum number of steps for winning the game: ";
    cin >> max_step_num;
    
    
    // CALLING FUNCTION 1
    /* The function initializes all array elements by randomly assigning a symbol from
     a set of max_step_num characters. E.g. if max_step_num is 3, the 3 characters are 'A', 'B', 'C'.
     */
    initialize_symbols(symbol_array, num_of_symbols);
    
    // CALLING FUNCTION 2
    /* The function prints the board (i.e. symbol_array).
     */
    print_game_board(symbol_array);
    
    // GAME STARTS
    cout << endl << "GAME STARTS..." << endl << "Input new symbol to expand your territory!" << endl << endl;
    
    bool winning_flag = false;
    
    for(int step = 0; step < max_step_num && !winning_flag; ++step)
    {
        cout << "\n\nSTEPS LEFT: " << max_step_num - step << endl;
        
        // input the new symbol
        cout << "Input the new symbol to unleash your \"symbol army\" from the top-left: ";
        char new_symbol;
        cin >> new_symbol;
        cout << endl;
        
        /* input validation:
         make sure the new input is different from the top-left symbol and are not out of the range.
         */
        if(!input_validation(symbol_array, new_symbol, num_of_symbols))
        {
            cout << "Please re-input..." << endl;
            continue;
        }
        
        // CALLING FUNCTION 3
        /* The function updates the game board with new symbol using recursion.
         It starts with the top-left array element, and changes all array elements which are connected with it and
         sharing the same symbol with it to the new symbol.
         1st parameter: the array symbol_array
         2nd parameter: the old symbol to be replaced
         3rd parameter: the new symbol to be filled
         4th parameter: row index of the position to start the replacement
         5th parameter: col index of the position to start the replacement
         */
        update_symbol_array_recursive(symbol_array, symbol_array[0][0], new_symbol, 0, 0);
        
        // print the updated game board
        print_game_board(symbol_array);
        
        // CALLING FUNCTION 4
        /* The function returns true if the user wins the game, i.e. all elements are of the same symbol.
         Otherwise, returns false.
         */
        winning_flag = check_win(symbol_array);
    }
    
    if(winning_flag)
        cout << "\nCongratuations! You win the game!" << endl;
    else
        cout << "\nSo close! You lose the game!" << endl;
    
    return 0;
}
