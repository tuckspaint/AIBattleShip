//Executive.h iteration 1.2
#ifndef EXECUTIVE_H
#define EXECUTIVE_H

class Executive {
    private:
    //initiate current player to 1, player 1 always place's ships first and always shoot first.
    int currentPlayer = 1;

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


};
#endif
