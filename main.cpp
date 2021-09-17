//main.cpp iteration 1.1
#include <iostream>
#include "Executive.h"

int main() {
  std::cout << "Welcome to BattleShip:\n\n";
  Executive exe;
  exe.run();

/*
Things to clean up:
- when the player is prompt for (int) coordinate (either player 1 or 2). The program runs an infinite loop of asking int coordinates.
- when placing ships 2-6. Player is able to place part of the ship out coordinates(for example; when placing ship 3, (2,j-right) will register as good coordinates). board.cpp? ships() 2-6
- Play the game with all 6 ships, test to see if the hitmiss board is registering marked areas.
- when ship >= 2: infinite loop menu print after a player hits a ship >= ship2().(2a, 2b->right).

*/
  return(0);
};
