//Board.h iteration 1.2
#ifndef BOARD_H
#define BOARD_H
#include <string>
using namespace std;

class Board {

private:

    int m_numShips;
    bool m_ifAi;

public:
    /*
    * @pre none
    * @post board of char
    * @param none
    * @return none
    */
    char board[9][10];

    /*
    * @pre none
    * @post takes number of ships and fills board with 'X'
    * @param numShips
    * @return none
    */
    Board(int numShips, bool ifAi);

    /*
    * @pre none
    * @post asks players to place 1 ships on their board
    * @param none
    * @return none
    */
    void Ship1();

    /*
    * @pre none
    * @post asks players to each place 2 ships on their board
    * @param none
    * @return none
    */
    void Ship2();

    /*
    * @pre none
    * @post asks players to each place 3 ships on their board
    * @param none
    * @return none
    */
    void Ship3();

    /*
    * @pre none
    * @post asks players to each place 4 ships on their board
    * @param none
    * @return none
    */
    void Ship4();

    /*
    * @pre none
    * @post asks players to each place 5 ships on their board
    * @param none
    * @return none
    */
    void Ship5();

    /*
    * @pre none
    * @post asks players to each place 6 ships on their board
    * @param none
    * @return none
    */
    void Ship6();

    /*
    * @pre uses global variable numShips
    * @post prints board and calls the method due to amount of ships
    * @param none
    * @return none
    */
    void run();

    /*
    * @pre none
    * @post prints board in its current state
    * @param none
    * @return none
    */
    void BoardPrint();

    //helper functions

    /*
    * @pre none
    * @post used to place ships in the desired direction
    * @param none
    * @return the string for the ship oriantation
    */
    string direction();

    /*
    * @pre none
    * @post calls convertCharToInt due to the input
    * @param none
    * @return the integer based on the given char
    */
    int promptCol();

    /*
    * @pre none
    * @post checks given row input
    * @param none
    * @return integer and checks to see if location is valid
    */
    int promptRow();

    /*
    * @pre none
    * @post converts the row in char to an int for the board
    * @param m_row
    * @return int that matches the given char
    */
    int convertCharToInt(char m_row);

    /*
    * @pre none
    * @post checks to see if location is valid for col
    * @param m_col
    * @return true if valid, false if not
    */
    bool checkCol(char m_col);

    /*
    * @pre none
    * @post checks to see if location is valid for row
    * @param m_row
    * @return true if valid, false if not
    */
    bool checkRow(int m_row);

    /*
    * @pre none
    * @post checks board
    * @param row_1, col_1
    * @return true if row and col is a valid location
    */
    bool checkIfX(int row_1, int col_1);

    //new 09/11
    /*
    * @pre none
    * @post checks board for ships
    * @param m_row, m_col
    * @return true if there is a ship, false if not
    */
    bool checkBoard(int m_row, int m_col);

    /*
    * @pre none
    * @post checks if the ship is on the board
    * @param shipSize
    * @return true if the ship is NOT on the board (i.e. it's sunk), false if the ship is on the board
    */
    bool checkSunk(char shipSize);
    
    /*
    * @pre none
    * @post Checks the amount of ships being played and runs code off of that
    * @param none
    * @return none
    */
    void runShipBoard();
    
    /*
    * @pre none
    * @post A random number generator for choosing the AI's row
    * @param none
    * @return A number 1-9 for each row
    */
    int aiRandomRow();
    
    /*
    * @pre none
    * @post A random number generator for choosing the AI's col
    * @param none
    * @return A number 1-10 for each column
    */
    int aiRandomCol();
    
    /*
    * @pre none
    * @post Randomly generates a direction for placing the Ai's ship
    * @param none
    * @return A number 1-4 each representing a cardinal direction
    */
    int aiRandomDir();
    

};
#endif
