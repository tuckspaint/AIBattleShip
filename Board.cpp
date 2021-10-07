//Board.cpp iteration 1.2
#include "Board.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
using namespace std;


//constructor takes in desired number of ships to play, creates board and designates number of ships to member variable.
Board::Board(int numShips, bool ifAi) {
for(int i = 0; i < 9; i ++) {
 for(int j = 0; j < 10; j++) {
     board[i][j] = '*';
    }
 }
 m_numShips = numShips;
 m_ifAi = ifAi;
 run();
}

//prints layout of the board.
void Board::BoardPrint() {
  int counter = 9;
for(int i = 0; i < 9; i ++) {
  cout << counter << ' ';
  counter--;
 for(int j = 0; j < 10; j++) {
    cout << board[i][j] << ' ';
  }
  cout << '\n';
 }
 cout << "  A B C D E F G H I J\n";
}

void Board::run() {
  if(m_ifAi == 1)
  {
    runShipBoard();
  }
  else {
    BoardPrint();
    runShipBoard();
  }

}

void Board::runShipBoard() {
  if(m_numShips == 1) {
    Ship1();
  }
  else if(m_numShips == 2) {
    Ship2();
  }
  else if(m_numShips == 3) {
    Ship3();
  }
  else if(m_numShips == 4) {
    Ship4();
  }
  else if(m_numShips == 5) {
    Ship5();
  }
  else{
    Ship6();
  }
}

void Board::Ship1(){
  if(m_ifAi == 1) {
    board[9-aiRandomRow()][aiRandomCol()] = '1';
    cout << "Ai Ship placed!\n";
  }
  else {
    cout << "\nPlace ship 1: ";
    int row_1 = promptRow();
    int col_1 = promptCol();
    board[row_1][col_1] = '1';
    cout << "Ship placed!\n";
     BoardPrint();
  }
}

void Board::Ship2() {
Ship1();

int row_1;
int col_1;
bool flag = true;
if(m_ifAi == 1) {
  //Ai
  do{

  do{
    row_1 = 9-aiRandomRow();
    col_1 = aiRandomCol();
   }while(checkIfX(row_1, col_1) == false);


  string _direction = direction();

  if(_direction == "up"){
    if(row_1 >= 0 && checkIfX(row_1-1, col_1) == true){
      board[row_1][col_1] = '2';
      board[row_1-1][col_1] = '2';
      flag = true;

    }
    else {

      flag = false;
    }
   }
  else if(_direction == "down"){
    if(row_1 <= 8 && checkIfX(row_1+1, col_1) == true){
      board[row_1][col_1] = '2';
      board[row_1+1][col_1] = '2';
      flag = true;

    }
    else {

      flag = false;
    }
   }
   else if(_direction == "left"){
    if(row_1 <= 0 && checkIfX(row_1, col_1-1) == true){
      board[row_1][col_1] = '2';
      board[row_1][col_1-1] = '2';
      flag = true;

    }
    else {

      flag = false;

    }
   }
   else if(_direction == "right"){
    if(col_1 <= 9 && checkIfX(row_1, col_1+1) == true){
      board[row_1][col_1] = '2';
      board[row_1][col_1+1] = '2';
      flag = true;

    }

    else {

      flag = false;

    }
   }
  }while(flag == false);
  cout << "Ai Ship 2 placed!\n";
}
else {
  //PLayer 2
  cout << "Place ship 2: ";
  do{

  do{
    row_1 = promptRow();
    col_1 = promptCol();
   }while(checkIfX(row_1, col_1) == false);


  string _direction = direction();

  if(_direction == "up"){
    if(row_1 >= 0 && checkIfX(row_1-1, col_1) == true){
      board[row_1][col_1] = '2';
      board[row_1-1][col_1] = '2';
      flag = true;

    }
    else {
      cout << "Invalid\n";
      flag = false;
    }
   }
  else if(_direction == "down"){
    if(row_1 <= 8 && checkIfX(row_1+1, col_1) == true){
      board[row_1][col_1] = '2';
      board[row_1+1][col_1] = '2';
      flag = true;

    }
    else {
      cout << "Invalid\n";
      flag = false;
    }
   }
   else if(_direction == "left"){
    if(row_1 <= 0 && checkIfX(row_1, col_1-1) == true){
      board[row_1][col_1] = '2';
      board[row_1][col_1-1] = '2';
      flag = true;

    }
    else {
      cout << "No empty spots in that direction.\n";
      flag = false;

    }
   }
   else if(_direction == "right"){
    if(col_1 <= 9 && checkIfX(row_1, col_1+1) == true){
      board[row_1][col_1] = '2';
      board[row_1][col_1+1] = '2';
      flag = true;

    }

    else {
      cout << "Invalid\n";
      flag = false;

    }
   }
  }while(flag == false);

  cout << "Ship 2 placed.\n\n";
  BoardPrint();
}

}

void Board::Ship3() {
  Ship2();
  int row_1;
  int col_1;
  bool flag = true;
  if(m_ifAi == 1) {
    row_1 = 9-aiRandomRow();
    col_1 = aiRandomCol();
    do {
      while(checkIfX(row_1, col_1) == false) {
      row_1 = 9-aiRandomRow();
      col_1 = aiRandomCol();
     }

    string _direction = direction();


    if(_direction == "up") {
      if(row_1-1 >= 0 && row_1-2 >= 0) {
        if(checkIfX(row_1-1, col_1) == true && checkIfX(row_1-2, col_1) == true) {
        board[row_1][col_1] = '3';
        board[row_1-1][col_1] = '3';
        board[row_1-2][col_1] = '3';
        flag = true;
       }
        else {

        flag = false;
       }
      }
      else {

        flag = false;
      }
     }

    else if(_direction == "down"){
     if(row_1+1 <= 8 && row_1+2 <= 8) {
       if( checkIfX(row_1+1, col_1) == true && checkIfX(row_1+2, col_1) == true) {
        board[row_1][col_1] = '3';
        board[row_1+1][col_1] = '3';
        board[row_1+2][col_1] = '3';
        flag = true;
        }
       else {

        flag = false;
       }
     }
       else {

        flag = false;
       }
    }

     else if(_direction == "left"){
       if(col_1-1 >= 0 && col_1-2 >= 0) {
        if(checkIfX(row_1, col_1-1) == true && checkIfX(row_1, col_1-2) == true) {
         board[row_1][col_1] = '3';
         board[row_1][col_1-1] = '3';
         board[row_1][col_1-2] = '3';
         flag = true;
      }
      else {

        flag = false;
      }
     }
      else {

        flag = false;
      }
    }

     else if(_direction == "right"){
       if(col_1+1 <= 8 && col_1+2 <= 8) {
        if(checkIfX(row_1, col_1+1) == true && checkIfX(row_1, col_1+2) == true) {
         board[row_1][col_1] = '3';
         board[row_1][col_1+1] = '3';
         board[row_1][col_1+2] = '3';
         flag = true;
      }
      else {

        flag = false;
       }
      }
      else {

        flag = false;
      }
     }
    } while (flag == false);
     cout << "Ai Ship 3 placed.\n";
  }
  else {
    row_1 = promptRow();
    col_1 = promptCol();
    cout << "\nPlace Ship 3: \n";
    do {
      while(checkIfX(row_1, col_1) == false) {
      row_1 = promptRow();
      col_1 = promptCol();
     }

    string _direction = direction();


    if(_direction == "up") {
      if(row_1-1 >= 0 && row_1-2 >= 0) {
        if(checkIfX(row_1-1, col_1) == true && checkIfX(row_1-2, col_1) == true) {
        board[row_1][col_1] = '3';
        board[row_1-1][col_1] = '3';
        board[row_1-2][col_1] = '3';
        flag = true;
       }
        else {
        cout << "You cannot place ship in that direction\n";
        flag = false;
       }
      }
      else {
        cout << "No empty spots up!\n";
        flag = false;
      }
     }

    else if(_direction == "down"){
     if(row_1+1 <= 8 && row_1+2 <= 8) {
       if( checkIfX(row_1+1, col_1) == true && checkIfX(row_1+2, col_1) == true) {
        board[row_1][col_1] = '3';
        board[row_1+1][col_1] = '3';
        board[row_1+2][col_1] = '3';
        flag = true;
        }
       else {
        cout << "You cannot place ship in that direction\n";
        flag = false;
       }
     }
       else {
        cout << "No empty spots down!\n";
        flag = false;
       }
    }

     else if(_direction == "left"){
       if(col_1-1 >= 0 && col_1-2 >= 0) {
        if(checkIfX(row_1, col_1-1) == true && checkIfX(row_1, col_1-2) == true) {
         board[row_1][col_1] = '3';
         board[row_1][col_1-1] = '3';
         board[row_1][col_1-2] = '3';
         flag = true;
      }
      else {
        cout << "No empty spots left!\n";
        flag = false;
      }
     }
      else {
        cout << "You cannot place ship in that direction\n";
        flag = false;
      }
    }

     else if(_direction == "right"){
       if(col_1+1 <= 8 && col_1+2 <= 8) {
        if(checkIfX(row_1, col_1+1) == true && checkIfX(row_1, col_1+2) == true) {
         board[row_1][col_1] = '3';
         board[row_1][col_1+1] = '3';
         board[row_1][col_1+2] = '3';
         flag = true;
      }
      else {
        cout << "No empty spots right\n";
        flag = false;
       }
      }
      else {
        cout << "You cannot place ship in that direction\n";
        flag = false;
      }
     }
    } while (flag == false);
     cout << "Ship 3 placed.\n";
     BoardPrint();

  }
}

void Board::Ship4() {
  Ship3();

  int row_1;
  int col_1;
  bool flag = true;
  if(m_ifAi == 1)
  {
    row_1 = 9-aiRandomRow();
    col_1 = aiRandomCol();
    do {
      while(checkIfX(row_1, col_1) == false) {
      row_1 = 9-aiRandomRow();
      col_1 = aiRandomCol();
     }

    string _direction = direction();

    if(_direction == "up"){
      if(row_1 >= 0 && row_1-1 >= 0 && row_1-2 >= 0){
        if(checkIfX(row_1-1, col_1) == true && checkIfX(row_1-2, col_1) == true && checkIfX(row_1-3, col_1) == true) {
        board[row_1][col_1] = '4';
        board[row_1-1][col_1] = '4';
        board[row_1-2][col_1] = '4';
        board[row_1-3][col_1] = '4';
        flag = true;
       }
      }
      else {

        flag = false;
      }
     }

    else if(_direction == "down"){
     if(row_1-1 <= 8 && row_1-2 <= 8 && row_1-3 <= 8) {
       if( checkIfX(row_1+1, col_1) == true && checkIfX(row_1+2, col_1) == true && checkIfX(row_1+3, col_1) == true) {
        board[row_1][col_1] = '4';
        board[row_1+1][col_1] = '4';
        board[row_1+2][col_1] = '4';
        board[row_1+3][col_1] = '4';
        flag = true;
      }
       else {

        flag = false;
      }
     }
      else {

        flag = false;
      }
    }
     else if(_direction == "left"){
       if(col_1-1 >= 0 && col_1-2 >= 0 && col_1-3) {
        if(checkIfX(row_1, col_1-1) == true && checkIfX(row_1, col_1-2) == true && checkIfX(row_1, col_1-3) == true) {
         board[row_1][col_1] = '4';
         board[row_1][col_1-1] = '4';
         board[row_1][col_1-2] = '4';
         board[row_1][col_1-3] = '4';
         flag = true;
      }
      else {

        flag = false;
      }
     }
      else {

        flag = false;
      }
    }
     else if(_direction == "right"){
       if(col_1+1 <= 8 && col_1+2 <= 8 && col_1+3 <= 8) {
        if(checkIfX(row_1, col_1+1) == true && checkIfX(row_1, col_1+2) == true && checkIfX(row_1, col_1+3) == true) {
         board[row_1][col_1] = '4';
         board[row_1][col_1+1] = '4';
         board[row_1][col_1+2] = '4';
         board[row_1][col_1+3] = '4';
         flag = true;
      }
      else {

        flag = false;
       }
      }
      else {

        flag = false;
      }
     }
      } while (flag == false);
        cout << "Ai Ship 4 placed.\n\n";
  }
  else {
    cout << "\nPlace ship 4: \n";
    int row_1 = promptRow();
    int col_1 = promptCol();
    do {
      while(checkIfX(row_1, col_1) == false) {
      row_1 = promptRow();
      col_1 = promptCol();
     }

    string _direction = direction();

    if(_direction == "up"){
      if(row_1 >= 0 && row_1-1 >= 0 && row_1-2 >= 0){
        if(checkIfX(row_1-1, col_1) == true && checkIfX(row_1-2, col_1) == true && checkIfX(row_1-3, col_1) == true) {
        board[row_1][col_1] = '4';
        board[row_1-1][col_1] = '4';
        board[row_1-2][col_1] = '4';
        board[row_1-3][col_1] = '4';
        flag = true;
       }
      }
      else {
        cout << "No empty spots up!\n";
        flag = false;
      }
     }

    else if(_direction == "down"){
     if(row_1-1 <= 8 && row_1-2 <= 8 && row_1-3 <= 8) {
       if( checkIfX(row_1+1, col_1) == true && checkIfX(row_1+2, col_1) == true && checkIfX(row_1+3, col_1) == true) {
        board[row_1][col_1] = '4';
        board[row_1+1][col_1] = '4';
        board[row_1+2][col_1] = '4';
        board[row_1+3][col_1] = '4';
        flag = true;
      }
       else {
        cout << "No empty spots down!\n";
        flag = false;
      }
     }
      else {
        cout << "You cannot place ship in that direction\n";
        flag = false;
      }
    }
     else if(_direction == "left"){
       if(col_1-1 >= 0 && col_1-2 >= 0 && col_1-3) {
        if(checkIfX(row_1, col_1-1) == true && checkIfX(row_1, col_1-2) == true && checkIfX(row_1, col_1-3) == true) {
         board[row_1][col_1] = '4';
         board[row_1][col_1-1] = '4';
         board[row_1][col_1-2] = '4';
         board[row_1][col_1-3] = '4';
         flag = true;
      }
      else {
        cout << "no empty spots left!\n";
        flag = false;
      }
     }
      else {
        cout << "You cannot place ship in that direction\n";
        flag = false;
      }
    }
     else if(_direction == "right"){
       if(col_1+1 <= 8 && col_1+2 <= 8 && col_1+3 <= 8) {
        if(checkIfX(row_1, col_1+1) == true && checkIfX(row_1, col_1+2) == true && checkIfX(row_1, col_1+3) == true) {
         board[row_1][col_1] = '4';
         board[row_1][col_1+1] = '4';
         board[row_1][col_1+2] = '4';
         board[row_1][col_1+3] = '4';
         flag = true;
      }
      else {
        cout << "No empty spots right\n";
        flag = false;
       }
      }
      else {
        cout << "You cannot place ship in that direction\n";
        flag = false;
      }
     }
      } while (flag == false);
        cout << "Ship 4 placed.\n\n";
        BoardPrint();
  }

}

void Board::Ship5() {
 //functions calls previous ships to place.
  Ship4();

  int row_1;
  int col_1;
  bool flag = true;
  if(m_ifAi == 1) {
    int row_1 = aiRandomRow();
    int col_1 = aiRandomCol();
    do{
      while(checkIfX(row_1, col_1) == false) {
      row_1 = aiRandomRow();
      col_1 = aiRandomCol();
     }

    string _direction = direction();

    if(_direction == "up"){
      if(row_1 >= 0 && row_1-1 >= 0 && row_1-2 >= 0 && row_1-3 >= 0 && row_1-4 >= 0){
        if(checkIfX(row_1-1, col_1) == true && checkIfX(row_1-2, col_1) == true && checkIfX(row_1-3, col_1) == true && checkIfX(row_1-4, col_1) == true) {
        board[row_1][col_1] = '5';
        board[row_1-1][col_1] = '5';
        board[row_1-2][col_1] = '5';
        board[row_1-3][col_1] = '5';
        board[row_1-4][col_1] = '5';
        flag = true;
        }
      else {

        flag = false;
       }
      }
      else {

        flag = false;
      }
     }

    else if(_direction == "down"){
     if(row_1+1 <= 8 && row_1+2 <= 8 && row_1+3 <= 8 && row_1+4 <= 8) {
       if( checkIfX(row_1+1, col_1) == true && checkIfX(row_1+2, col_1) == true && checkIfX(row_1+3, col_1) == true && checkIfX(row_1+4, col_1) == true) {
        board[row_1][col_1] = '5';
        board[row_1+1][col_1] = '5';
        board[row_1+2][col_1] = '5';
        board[row_1+3][col_1] = '5';
        board[row_1+4][col_1] = '5';
        flag = true;
      }
       else {

        flag = false;
      }
     }
      else {

        flag = false;
      }
    }
     else if(_direction == "left"){
       if(col_1-1 >= 0 && col_1-2 >= 0 && col_1-3 && col_1-4) {
        if(checkIfX(row_1, col_1-1) == true && checkIfX(row_1, col_1-2) == true && checkIfX(row_1, col_1-3) == true && checkIfX(row_1, col_1-4) == true) {
         board[row_1][col_1] = '5';
         board[row_1][col_1-1] = '5';
         board[row_1][col_1-2] = '5';
         board[row_1][col_1-3] = '5';
         board[row_1][col_1-4] = '5';
         flag = true;
      }
      else {

        flag = false;
      }
     }
      else {

        flag = false;
      }
    }
     else if(_direction == "right"){
       if(col_1+1 <= 8 && col_1+2 <= 8 && col_1+3 <= 8 && col_1+4 <= 8) {
        if(checkIfX(row_1, col_1+1) == true && checkIfX(row_1, col_1+2) == true && checkIfX(row_1, col_1+3) == true && checkIfX(row_1, col_1+4) == true) {
         board[row_1][col_1] = '5';
         board[row_1][col_1+1] = '5';
         board[row_1][col_1+2] = '5';
         board[row_1][col_1+3] = '5';
         board[row_1][col_1+4] = '5';
         flag = true;
      }
      else {

        flag = false;
       }
      }
      else {

        flag = false;
      }
     }
    } while (flag == false);
        cout << "Ai Ship 5 placed.\n\n";
  }
  else {
    cout << "\nPlace ship 5: \n";
    int row_1 = promptRow(); //initial mark acts as a pivot point.
    int col_1 = promptCol();
    do{
      while(checkIfX(row_1, col_1) == false) {
      row_1 = promptRow();
      col_1 = promptCol();
     }

    string _direction = direction();

    if(_direction == "up"){
      if(row_1 >= 0 && row_1-1 >= 0 && row_1-2 >= 0 && row_1-3 >= 0 && row_1-4 >= 0){
        if(checkIfX(row_1-1, col_1) == true && checkIfX(row_1-2, col_1) == true && checkIfX(row_1-3, col_1) == true && checkIfX(row_1-4, col_1) == true) {
        board[row_1][col_1] = '5';
        board[row_1-1][col_1] = '5';
        board[row_1-2][col_1] = '5';
        board[row_1-3][col_1] = '5';
        board[row_1-4][col_1] = '5';
        flag = true;
        }
      else {
        cout << "You cannot place ship in that direction\n";
        flag = false;
       }
      }
      else {
        cout << "No empty spots up!\n";
        flag = false;
      }
     }

    else if(_direction == "down"){
     if(row_1+1 <= 8 && row_1+2 <= 8 && row_1+3 <= 8 && row_1+4 <= 8) {
       if( checkIfX(row_1+1, col_1) == true && checkIfX(row_1+2, col_1) == true && checkIfX(row_1+3, col_1) == true && checkIfX(row_1+4, col_1) == true) {
        board[row_1][col_1] = '5';
        board[row_1+1][col_1] = '5';
        board[row_1+2][col_1] = '5';
        board[row_1+3][col_1] = '5';
        board[row_1+4][col_1] = '5';
        flag = true;
      }
       else {
        cout << "No empty spots down!\n";
        flag = false;
      }
     }
      else {
        cout << "You cannot place ship in that direction\n";
        flag = false;
      }
    }
     else if(_direction == "left"){
       if(col_1-1 >= 0 && col_1-2 >= 0 && col_1-3 && col_1-4) {
        if(checkIfX(row_1, col_1-1) == true && checkIfX(row_1, col_1-2) == true && checkIfX(row_1, col_1-3) == true && checkIfX(row_1, col_1-4) == true) {
         board[row_1][col_1] = '5';
         board[row_1][col_1-1] = '5';
         board[row_1][col_1-2] = '5';
         board[row_1][col_1-3] = '5';
         board[row_1][col_1-4] = '5';
         flag = true;
      }
      else {
        cout << "No empty spots left!\n";
        flag = false;
      }
     }
      else {
        cout << "You cannot place ship in that direction\n";
        flag = false;
      }
    }
     else if(_direction == "right"){
       if(col_1+1 <= 8 && col_1+2 <= 8 && col_1+3 <= 8 && col_1+4 <= 8) {
        if(checkIfX(row_1, col_1+1) == true && checkIfX(row_1, col_1+2) == true && checkIfX(row_1, col_1+3) == true && checkIfX(row_1, col_1+4) == true) {
         board[row_1][col_1] = '5';
         board[row_1][col_1+1] = '5';
         board[row_1][col_1+2] = '5';
         board[row_1][col_1+3] = '5';
         board[row_1][col_1+4] = '5';
         flag = true;
      }
      else {
        cout << "No empty spots right\n";
        flag = false;
       }
      }
      else {
        cout << "You cannot place ship in that direction\n";
        flag = false;
      }
     }
    } while (flag == false);
        cout << "Ship 5 placed.\n\n";
        BoardPrint();
  }

}

void Board::Ship6() {
 //function calls previous ships to place
  Ship5();

  int row_1;
  int col_1;
  bool flag = true;
  if(m_ifAi == 1) {
    row_1 = aiRandomRow();
    col_1 = aiRandomCol();
    do {

    while(checkIfX(row_1, col_1) == false) {
      row_1 = aiRandomRow();
      col_1 = aiRandomCol();
   }


  string _direction = direction();

  if(_direction == "up"){
    if(row_1 >= 0 && row_1-1 >= 0 && row_1-2 >= 0 && row_1-3 >= 0 && row_1-4 >= 0 && row_1-5 >= 0){
      if(checkIfX(row_1-1, col_1) == true && checkIfX(row_1-2, col_1) == true && checkIfX(row_1-3, col_1) == true && checkIfX(row_1-4, col_1) == true && checkIfX(row_1-5, col_1) == true) {
      board[row_1][col_1] = '6';
      board[row_1-1][col_1] = '6';
      board[row_1-2][col_1] = '6';
      board[row_1-3][col_1] = '6';
      board[row_1-4][col_1] = '6';
      board[row_1-5][col_1] = '6'; // check, test ship five & output.
      flag = true;
     }
    else {

      flag = false;
   }
    }
    else {

      flag = false;
    }
   }

  else if(_direction == "down"){
   if(row_1+1 <= 8 && row_1+2 <= 8 && row_1+3 <= 8 && row_1+4 <= 8 && row_1+5 <= 8) {
     if( checkIfX(row_1+1, col_1) == true && checkIfX(row_1+2, col_1) == true && checkIfX(row_1+3, col_1) == true && checkIfX(row_1+4, col_1) == true && checkIfX(row_1+5, col_1) == true) {
      board[row_1][col_1] = '6';
      board[row_1+1][col_1] = '6';
      board[row_1+2][col_1] = '6';
      board[row_1+3][col_1] = '6';
      board[row_1+4][col_1] = '6';
      board[row_1+5][col_1] = '6';
      flag = true;
    }
     else {

      flag = false;
    }
   }
   else {

      flag = false;
    }

  }
   else if(_direction == "left"){
     if(col_1-1 >= 0 && col_1-2 >= 0 && col_1-3 && col_1-4 && col_1-5) {
      if(checkIfX(row_1, col_1-1) == true && checkIfX(row_1, col_1-2) == true && checkIfX(row_1, col_1-3) == true && checkIfX(row_1, col_1-4) == true && checkIfX(row_1, col_1-5) == true) {
       board[row_1][col_1] = '6';
       board[row_1][col_1-1] = '6';
       board[row_1][col_1-2] = '6';
       board[row_1][col_1-3] = '6';
       board[row_1][col_1-4] = '6';
       board[row_1][col_1-5] = '6';
       flag = true;
    }
    else {

      flag = false;
    }
   }
  else {

      flag = false;
    }

  }
   else if(_direction == "right"){
     if(col_1+1 <= 8 && col_1+2 <= 8 && col_1+3 <= 8 && col_1+4 <= 8 && col_1+5 <= 8) {
      if(checkIfX(row_1, col_1+1) == true && checkIfX(row_1, col_1+2) == true && checkIfX(row_1, col_1+3) == true && checkIfX(row_1, col_1+4) == true && checkIfX(row_1, col_1+5) == true) {
       board[row_1][col_1] = '6';
       board[row_1][col_1+1] = '6';
       board[row_1][col_1+2] = '6';
       board[row_1][col_1+3] = '6';
       board[row_1][col_1+4] = '6';
       board[row_1][col_1+5] = '6';
       flag = true;
    }
    else {

      flag = false;
     }
    }
  else {

      flag = false;
    }

   }
    } while( flag == false );
      cout << "Ai Ship 6 placed.\n";
  }
  else {
    cout << "\nPlace Ship 6:\n";
    int row_1 = promptRow();
    int col_1 = promptCol();
    do {

    while(checkIfX(row_1, col_1) == false) {
    row_1 = promptRow();
    col_1 = promptCol();
   }


  string _direction = direction();

  if(_direction == "up"){
    if(row_1 >= 0 && row_1-1 >= 0 && row_1-2 >= 0 && row_1-3 >= 0 && row_1-4 >= 0 && row_1-5 >= 0){
      if(checkIfX(row_1-1, col_1) == true && checkIfX(row_1-2, col_1) == true && checkIfX(row_1-3, col_1) == true && checkIfX(row_1-4, col_1) == true && checkIfX(row_1-5, col_1) == true) {
      board[row_1][col_1] = '6';
      board[row_1-1][col_1] = '6';
      board[row_1-2][col_1] = '6';
      board[row_1-3][col_1] = '6';
      board[row_1-4][col_1] = '6';
      board[row_1-5][col_1] = '6'; // check, test ship five & output.
      flag = true;
     }
    else {
      cout << "No empty spots up!\n";
      flag = false;
   }
    }
    else {
      cout << "You cannot place ship in that direction\n";
      flag = false;
    }
   }

  else if(_direction == "down"){
   if(row_1+1 <= 8 && row_1+2 <= 8 && row_1+3 <= 8 && row_1+4 <= 8 && row_1+5 <= 8) {
     if( checkIfX(row_1+1, col_1) == true && checkIfX(row_1+2, col_1) == true && checkIfX(row_1+3, col_1) == true && checkIfX(row_1+4, col_1) == true && checkIfX(row_1+5, col_1) == true) {
      board[row_1][col_1] = '6';
      board[row_1+1][col_1] = '6';
      board[row_1+2][col_1] = '6';
      board[row_1+3][col_1] = '6';
      board[row_1+4][col_1] = '6';
      board[row_1+5][col_1] = '6';
      flag = true;
    }
     else {
      cout << "No empty spots down!\n";
      flag = false;
    }
   }
   else {
      cout << "You cannot place ship in that direction\n";
      flag = false;
    }

  }
   else if(_direction == "left"){
     if(col_1-1 >= 0 && col_1-2 >= 0 && col_1-3 && col_1-4 && col_1-5) {
      if(checkIfX(row_1, col_1-1) == true && checkIfX(row_1, col_1-2) == true && checkIfX(row_1, col_1-3) == true && checkIfX(row_1, col_1-4) == true && checkIfX(row_1, col_1-5) == true) {
       board[row_1][col_1] = '6';
       board[row_1][col_1-1] = '6';
       board[row_1][col_1-2] = '6';
       board[row_1][col_1-3] = '6';
       board[row_1][col_1-4] = '6';
       board[row_1][col_1-5] = '6';
       flag = true;
    }
    else {
      cout << "No empty spots down!\n";
      flag = false;
    }
   }
  else {
      cout << "You cannot place ship in that direction\n";
      flag = false;
    }

  }
   else if(_direction == "right"){
     if(col_1+1 <= 8 && col_1+2 <= 8 && col_1+3 <= 8 && col_1+4 <= 8 && col_1+5 <= 8) {
      if(checkIfX(row_1, col_1+1) == true && checkIfX(row_1, col_1+2) == true && checkIfX(row_1, col_1+3) == true && checkIfX(row_1, col_1+4) == true && checkIfX(row_1, col_1+5) == true) {
       board[row_1][col_1] = '6';
       board[row_1][col_1+1] = '6';
       board[row_1][col_1+2] = '6';
       board[row_1][col_1+3] = '6';
       board[row_1][col_1+4] = '6';
       board[row_1][col_1+5] = '6';
       flag = true;
    }
    else {
      cout << "No Empty Spots\n";
      flag = false;
     }
    }
  else {
      cout << "You cannot place ship in that direction\n";
      flag = false;
    }

   }
    } while( flag == false );
      cout << "Ship 6 placed.\n";
      BoardPrint();
  }

}



// returns true if the desired row, col is valid location. X.
bool Board::checkIfX(int row_1, int col_1) {
if(board[row_1][col_1] == '*') {
return true;
 }
 else{
   return false;
 }
}

// returns integer when the player inputs a char. This function calls convertCharToInt to satisfy board contraints. A-J = 0-9.
int Board::promptCol() {
  char m_col;
  bool valid = false;
  while(valid == false) {
    cout << "which col?(char)\n";
    cin >> m_col;
    valid = checkCol(m_col);
}
  int col = convertCharToInt(m_col);
  return(col);
}

// returns integer and checks to see if desired location is valid. 1-9.
int Board::promptRow(){
  bool bad = false;
  int m_row;
  bool valid = false;
  do {
    cout << "which row?(int)\n";
    cin >> m_row;
    bad = cin.fail();
	if (bad){
	cout << "ERROR try entering a valid coordinate\n" << endl;
	cin.clear();
	cin.ignore(1000, '\n');
	}
    valid = checkRow(m_row);
  } while(valid == false);

  return(9-m_row);
}

//converts Char to corresponding integer on the board.
int Board::convertCharToInt(char m_col) {
  if(m_col == 'A' || m_col == 'a'){
    return(0);
  }
  else if(m_col == 'B' || m_col == 'b'){
    return(1);
  }
  else if(m_col == 'C' || m_col =='c'){
    return(2);
  }
  else if(m_col == 'D' || m_col =='d'){
    return(3);
  }
  else if(m_col == 'E'|| m_col == 'e'){
    return(4);
  }
  else if(m_col == 'F'|| m_col == 'f'){
    return(5);
  }
  else if(m_col == 'G'|| m_col == 'g'){
    return(6);
  }
  else if(m_col == 'H'|| m_col == 'h'){
    return(7);
  }
  else if(m_col == 'I' || m_col == 'i'){
    return(8);
  }
  else if(m_col =='J'|| m_col == 'j') {
    return(9);
  }
  else{
    char col;
    cout << "please enter valid char coordinate: \n";
    cin >> col;
    return convertCharToInt(col);
  }
}

//returns a string, function used when the player wants to orient the ship in a desired direction.
string Board::direction() {
 string shipDirection;
 for( ; ;)
{
  if(m_ifAi == 1){
    int tempDir = aiRandomDir();
    if(tempDir == 1) {
      shipDirection == "up";
    }
    else if(tempDir == 2) {
      shipDirection == "down";
    }
    else if(tempDir == 3) {
      shipDirection == "left";
    }
    else {
      shipDirection == "right";
    }
  }
  else {
    cout << "Where would you like to place the rest of your ship?(up, down, left or right): \n";
 	 cin >> shipDirection;
 	 if(shipDirection == "up" || shipDirection == "down" || shipDirection == "left" || shipDirection == "right")
 	 {
 		 break;
 	 }
 	 else
 	 {
 		 cout << "Invalid input, enter again" << endl;
 	 }
  }

}
	return(shipDirection);
}




// returns bool depending if the desired location is valid on the board. A-J.
bool Board::checkCol(char m_col) {
  if(m_col == 'A' || m_col == 'a'|| m_col == 'B' || m_col == 'b' || m_col == 'C' || m_col == 'c'
  || m_col == 'D' || m_col == 'd' || m_col == 'E' || m_col == 'e'|| m_col == 'F' ||
   m_col == 'f' || m_col == 'G' || m_col == 'g' || m_col == 'H' || m_col == 'h' || m_col == 'I' || m_col == 'i' || m_col == 'J' || m_col == 'j') {
    return true;
  }
  else {
    return false;
  }
}

// returns bool depending if the desired location is valid on the board. 1-9.
bool Board::checkRow(int m_row) {
  if(m_row == 1 || m_row == 2 || m_row == 3 || m_row == 4 || m_row == 5 || m_row == 6 || m_row == 7 || m_row == 8 || m_row == 9) {
    return 1;
 }
else {
  return 0;
 }
}


bool Board::checkBoard(int row, int col) {
if(board[9-row][col] == '1' || board[9-row][col] == '2'
|| board[9-row][col] == '3' || board[9-row][col] == '4'
|| board[9-row][col] == '5' || board[9-row][col] == '6') {
  return true;
 }
else {
return false;
 }
}

///////////////////////////////////////New Project 2
bool Board::checkSunk(char shipSize) {
	for(int i = 0; i < 9; i ++) {
		for(int j = 0; j < 10; j++) {
			if(board[i][j] == shipSize) {
				return(false);
			}
		}
	}
	return(true);
 }

int Board::aiRandomDir() {
  srand((unsigned) time(0));
  return((rand() % 4)+1);
}

int Board::aiRandomRow() {
  srand((unsigned) time(0));
  return((rand() % 9)+1);
}

int Board::aiRandomCol() {
  srand((unsigned) time(0));
  return((rand() % 10)+1);
}
