//Executive.h iteration 1.2
#ifndef EXECUTIVE_H
#define EXECUTIVE_H
#include "Board.h"

class Executive {
    private:
    //initiate current player to 1, player 1 always place's ships first and always shoot first.
    int currentPlayer = 1;
    bool aiChosen = 0;
    int modeChosen = 0;

    public:
    /*
    * @pre none
    * @post executive constructor
    * @param none
    * @return none
    */
    Executive(){};
    
    /*
    * @pre non
    * @post runs the game
    * @param none
    * @return none
    */
    void run();

    /*
    * @pre none
    * @post prints menu of choices for players
    * @param none
    * @return none
    */
    void printMenu();

    /*
    * @pre given number of ships
    * @post each player has their own number of hit cuonts which is then compared to how many ships were placed
    * @param numships
    * @return int to see if winner
    */
    int winningCondition(int numships);

    /*
    * @pre none
    * @post switches players based on which player just went
    * @param none
    * @return none
    */
    void playerChange();
    
      /*
    * @pre none
    * @post Prints the board[9][10] handed to the function to the consol, then waits for milliSec
    * @param board[9][10], milliSec
    * @return none
    */
    void Printframe(char board[9][10], int milliSec); 
      /*
    * @pre none
    * @post calls Printframe for each frame in the animation and passes it the msPerFrame for each frame
    * @param msPerFrame
    * @return none
    */
    void Playmiss(int msPerFrame);
    /*
    * @pre none
    * @post calls Printframe for each frame in the animation and passes it the msPerFrame for each frame
    * @param msPerFrame
    * @return none
    */
    void Playhit(int msPerFrame);
    /*
    * @pre none
    * @post calls Printframe for each frame in the animation and passes it the msPerFrame for each frame, it will repeat the animation for loops number of times
    * @param msPerFrame, loops
    * @return none
    */
    void Playp1win(int msPerFrame, int loops);
    /*
    * @pre none
    * @post calls Printframe for each frame in the animation and passes it the msPerFrame for each frame, it will repeat the animation for loops number of times
    * @param msPerFrame, loops
    * @return none
    */
    void Playp2win(int msPerFrame, int loops); 
    
    /*
    * @pre hitmiss_2 is initialized
    * @post tries to attack the first valid(not already hit or out of bounds) spot up from initHit, changes aiRow and aiCol to the coordinates of that spot
    * @param aiRow and aiCol (the coordinates of the valid attack), initHit (the coordinates of the first spot hit), hitmiss_2 (the array of all hits and misses on the board)
    * @return true if there was a valid spot up from the initHit, false if there was not
    */
    bool attackUp(int &aiRow, int &aiCol, int initHit[2], char hitmiss_2[9][10]);
    /*
    * @pre hitmiss_2 is initialized
    * @post tries to attack the first valid(not already hit or out of bounds) spot right from initHit, changes aiRow and aiCol to the coordinates of that spot
    * @param aiRow and aiCol (the coordinates of the valid attack), initHit (the coordinates of the first spot hit), hitmiss_2 (the array of all hits and misses on the board)
    * @return true if there was a valid spot right from the initHit, false if there was not
    */
    bool attackRight(int &aiRow, int &aiCol, int initHit[2], char hitmiss_2[9][10]);
    /*
    * @pre hitmiss_2 is initialized
    * @post tries to attack the first valid(not already hit or out of bounds) spot down from initHit, changes aiRow and aiCol to the coordinates of that spot
    * @param aiRow and aiCol (the coordinates of the valid attack), initHit (the coordinates of the first spot hit), hitmiss_2 (the array of all hits and misses on the board)
    * @return true if there was a valid spot down from the initHit, false if there was not
    */
    bool attackDown(int &aiRow, int &aiCol, int initHit[2], char hitmiss_2[9][10]);
    /*
    * @pre hitmiss_2 is initialized
    * @post tries to attack the first valid(not already hit or out of bounds) spot left from initHit, changes aiRow and aiCol to the coordinates of that spot
    * @param aiRow and aiCol (the coordinates of the valid attack), initHit (the coordinates of the first spot hit), hitmiss_2 (the array of all hits and misses on the board)
    * @return true if there was a valid spot left from the initHit, false if there was not
    */
    bool attackLeft(int &aiRow, int &aiCol, int initHit[2], char hitmiss_2[9][10]);
    
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

};
#endif
