//Executive.h iteration 1.1
#ifndef EXECUTIVE_H
#define EXECUTIVE_H

class Executive {
    private:
    //initiate current player to 1, player 1 always place's ships first and always shoot first.
    int currentPlayer = 1;

    public:
    Executive(){};
    void run();

    //prints choice menu for player.
    void printMenu();

    // dynamic winning conditions based on the number of ships in play. each player have their own hit counts which will compare to this value.
    // If hitcount of that player matches this number, player wins.
    int winningCondition(int numships);

    // at the end of choice 2(choosing which space to attack), game switches players.
    void playerChange();


};
#endif
