//Board.h iteration 1.1
#ifndef BOARD_H
#define BOARD_H
#include <string>
using namespace std;

class Board {

private:
//char** board;
int m_numShips;

public:
char board;
Board(int numShips);
~Board();
void Ship1();             // Ships 1-6 will be called depending on the amount of ships the player wants to pick.
void Ship2();             // each function will call the previous ship function up to a maximum of 6.
void Ship3();             //
void Ship4();             //
void Ship5();             //
void Ship6();             //
void run();

//prints layout of the board at its current state.
void BoardPrint();

//helper functions
string direction();
int promptCol();
int promptRow();
int convertCharToInt(char m_row);
bool checkCol(char m_col);
bool checkRow(int m_row);
bool checkIfX(int row_1, int col_1);
//new 09/11
bool checkBoard(int m_row, int m_col);

};
#endif
