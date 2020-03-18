/*
 * main.cpp
 *
 *  Created on: Sep 19, 2019
 *      Author: kevinw
 */

#include <iostream>
#include <cstring>
using namespace std;

const int ARRAY_SIZE = 12;
const char POTION = 'o';
const char RIM = 'T';
const char WALL = '*';
const char EMPTY = ' ';

enum TASK {CLEANUP, WARMUP_FILL, SIMPLE_FILL, ADVANCED_FILL};
void print_array(const char array[][ARRAY_SIZE+1]) {
    cout << "  ";
    for (int j = 0; j < ARRAY_SIZE; j++)
    cout << j % 10;
    cout << endl;
    for (int i = 0; i < ARRAY_SIZE; i++) {
    cout << i % 10 << " ";
    cout << array[i] << endl;
    }
}

int cleanup(char array[ARRAY_SIZE][ARRAY_SIZE+1], int row = 0, int col = 0) {
// Don't forget to return!
    if (row < 0 || row > ARRAY_SIZE - 1 || col < 0 || col > ARRAY_SIZE - 2) return 0;
    int count = 0;
    if (array[row][col] == POTION)
    {
        array[row][col] = EMPTY;
        count += 1;
    }
    return (count + cleanup(array, row + 1, col) + cleanup(array, row, col + 1));
}

void warmup_fill(char array[][ARRAY_SIZE+1], int row, int col, int level) {
    if (row < 0 || row > ARRAY_SIZE - 1 || col < 0 || col > ARRAY_SIZE - 2) return;
    if (array[row][col] == WALL || array[row][col] == POTION || array[row][col] == RIM) return;
    if (array[row][col] == EMPTY && row >= level)
        array[row][col] = POTION;
    warmup_fill(array, row + 1, col, level); //down
    if (row > level)
    {
        warmup_fill(array, row, col - 1, level); //left
        warmup_fill(array, row, col + 1, level); //right
        warmup_fill(array, row - 1, col, level); //up
    }
}

void explode_fill(char array[][ARRAY_SIZE+1], int row, int col) {
    if (row < 0 || row > ARRAY_SIZE - 1 || col < 0 || col > ARRAY_SIZE - 2) return;
    if (array[row][col - 1] == RIM && array[row][col + 1] == RIM && array[row][col] == EMPTY)
    {
        array[row][col] = POTION;
        return;
    }
    if (array[row][col] == WALL || array[row][col] == POTION || array[row][col] == RIM) return;
    if (array[row][col] == EMPTY)
        array[row][col] = POTION;
    explode_fill(array, row - 1, col);
    explode_fill(array, row + 1, col);
    explode_fill(array, row, col - 1);
    explode_fill(array, row, col + 1);
}

void simple_fill(char array[][ARRAY_SIZE+1], int row, int col) {
    if (array[row + 1][col] == WALL || row == ARRAY_SIZE - 1)
    {
        explode_fill(array, row, col);
        return;
    }
    simple_fill(array, row + 1, col);
}

bool rim_level(char array[][ARRAY_SIZE+1], int row = 0, int col = 0) {
    if (row < 0 || row > ARRAY_SIZE - 1 || col < 0 || col > ARRAY_SIZE - 2) return false;
    if (array[row][col] == RIM)
        return true;
    return (false || rim_level(array, row, col + 1));
}

bool check_spill(char array[][ARRAY_SIZE+1], int row = 0, int col = 0) {
    bool spill;
    if (row < 0 || row > ARRAY_SIZE - 1 || col < 0 || col > ARRAY_SIZE - 2) return false;
    if (array[row][col] == POTION && (row == 0 || row == ARRAY_SIZE - 1 || col == 0 || col == ARRAY_SIZE - 1))
        spill = true;
    else
        spill = false;
    return (spill || check_spill(array, row + 1, col) || check_spill(array, row, col + 1));
}

void advanced_explode_fill(char array[][ARRAY_SIZE+1], int row, int col) {
    if (row < 0 || row > ARRAY_SIZE - 1 || col < 0 || col > ARRAY_SIZE - 2) return;
    if (rim_level(array, row, col) && array[row][col] == EMPTY)
    {
        array[row][col] = POTION;
        return;
    }
    if (array[row][col] == WALL || array[row][col] == POTION || array[row][col] == RIM) return;
    if (array[row][col] == EMPTY)
        array[row][col] = POTION;
    advanced_explode_fill(array, row - 1, col);
    advanced_explode_fill(array, row + 1, col);
    advanced_explode_fill(array, row, col - 1);
    advanced_explode_fill(array, row, col + 1);
}

int advanced_fill(char array[][ARRAY_SIZE+1], int row, int col) {
// Don't forget to return!
    if (array[row + 1][col] == WALL || row == ARRAY_SIZE - 1)
    {
        advanced_explode_fill(array, row, col);
        return -1;
    }
    int endStage = advanced_fill(array, row + 1, col);
    if (endStage == -1)
    {
        if (check_spill(array))
            cleanup(array);
    }
    return 0;
}

void fill(int algorithm, char array[][ARRAY_SIZE+1], int row, int col) {
    cout << "Before Water is filled" << endl;
    print_array(array);
    int level;
    switch (algorithm) {
    case CLEANUP:
    cleanup(array);
    break;
    case WARMUP_FILL:
    cout << "Please help me mark the level:" << endl;
    cin >> level;
    warmup_fill(array, row, col, level);
    cout << "Warmup Fill" << endl;
    break;
    case SIMPLE_FILL:
    simple_fill(array, row, col);
    cout << "Simple Fill" << endl;
    break;
    case ADVANCED_FILL:
    advanced_fill(array,row,col);
    cout << "Advanced Fill" << endl;
    break;
    }
    print_array(array);
}


int main() {
    char test_tube[ARRAY_SIZE][ARRAY_SIZE+1] = {
        "            ",
        "            ",
        "            ",
        "            ",
        "   T T T T  ",
        "    *   *   ",
        "            ",
        "     T T    ",
        "     * *    ",
        "      *     ",
        "            ",
        "            "
    };


    char two_tubes[ARRAY_SIZE][ARRAY_SIZE+1] = {
        "            ",
        "     T T    ",
        "     ***    ",
        "            ",
        "     T T    ",
        "     * *    ",
        "     * *    ",
        "     * *    ",
        "     * *    ",
        "     ***    ",
        "            ",
        "            "
    };


    char conical_flask[ARRAY_SIZE][ARRAY_SIZE+1] = {
        "            ",
        "            ",
        "            ",
        "            ",
        "     T T    ",
        "     * *    ",
        "     * *    ",
        "    *   *   ",
        "   *     *  ",
        "  ********* ",
        "            ",
        "            "
    };


    char broken_tube[ARRAY_SIZE][ARRAY_SIZE+1] = {
        "            ",
        "            ",
        "            ",
        "            ",
        "     T T    ",
        "     * *    ",
        "     * *    ",
        "     * *    ",
        "     * *    ",
        "            ",
        "            ",
        "            "
    };

    char broken_flask[ARRAY_SIZE][ARRAY_SIZE+1] = {
        "            ",
        "            ",
        "            ",
        "            ",
        "     T T    ",
        "     * *    ",
        "     * *    ",
        "    *   *   ",
        "         *  ",
        "  ********* ",
        "            ",
        "            "
    };
    char beaker[ARRAY_SIZE][ARRAY_SIZE+1] = {
        "            ",
        "            ",
        "            ",
        "            ",
        "  T    T    ",
        "  *    *    ",
        "  *    *    ",
        "  *    *    ",
        "  *    *    ",
        "  ******    ",
        "            ",
        "            "
    };



    char flask[ARRAY_SIZE][ARRAY_SIZE+1] = {
        "            ",
        "    T T     ",
        "    * *     ",
        "    * *     ",
        "  **   **   ",
        " *       *  ",
        " *       *  ",
        " *       *  ",
        "  *     *   ",
        "   *****    ",
        "            ",
        "            "
    };


    char up_and_down[ARRAY_SIZE][ARRAY_SIZE+1] = {
        "            ",
        "            ",
        "            ",
        "            ",
        " T T        ",
        " * * *******",
        " * * *   * *",
        " * *** * * *",
        " *     *   *",
        " ********* *",
        " *         *",
        " ***********"
    };

    char broken_u_flask[ARRAY_SIZE][ARRAY_SIZE+1] = {
        "            ",
        "            ",
        "            ",
        "            ",
        "    T T     ",
        "    * * *  *",
        "    * ***  *",
        "   *      * ",
        "  *     **  ",
        " *********  ",
        "            ",
        "            "
    };


    int opt;
    while (true) {
    cout << "Enter 0 (cleanup), 1 (warmup), 2 (simple), 3 (advanced) to select your algorithm, or other value to quit the program:" << endl;
    cin >> opt;
    if (opt < 0 || opt > 3)
        return 0;

    fill(opt, test_tube, 0, 6);
    fill(opt, conical_flask, 0, 6);
    fill(opt, flask,0,5);
        fill(opt, up_and_down, 0, 2);
    if (opt != ADVANCED_FILL)
       fill(opt, two_tubes, 0, 6);
    else
        cout << "Not for advanced_fill" << endl;
    if (opt != SIMPLE_FILL && opt != WARMUP_FILL)
        fill(opt, broken_flask, 0, 6);
    else
        cout << "Not for warmup_fill and simple_fill" << endl;
    if (opt != SIMPLE_FILL && opt != WARMUP_FILL)
        fill(opt, broken_tube, 0, 6);
    else
          cout << "Not for warmup_fill and simple_fill" << endl;
    if (opt != SIMPLE_FILL && opt != WARMUP_FILL)
        fill(opt, beaker, 0, 4);
    else
        cout << "Not for warmup_fill and simple_fill" << endl;
    if (opt != SIMPLE_FILL && opt != WARMUP_FILL)
        fill(opt, broken_u_flask,0,5);
    else
        cout << "Not for warmup_fill and simple_fill" << endl;
    }
    return 0;


}
