//main.cpp iteration 1.2
#include <iostream>
#include "Executive.h"
#include <cstdlib>
using namespace std;

int main() {
  std::cout << "\x1B[2J\x1B[H";
  cout << "Welcome to BattleShip:\n\n";
  Executive exe;
  exe.run();

  return(0);
};
