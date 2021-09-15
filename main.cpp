//main.cpp
#include <iostream>
#include "Executive.h"

int main() {
  std::cout << "Welcome to BattleShip:\n\n";
  Executive exe;
  exe.run();

/*
Things to clean up:
- when placing ships 2-6. Player is able to place ships out of board coordinates. board.cpp ships() 2-6
- Play the game with all 6 ships, test to see if the hitmiss board is registering marked areas.  
- when ship >= 2: infinite loop menu print after a player hits a ship >= ship2().(2a, 2b->right).
*/
  return(0);
};