//Board.cpp
#include "Board.h"
#include <iostream>
#include <string>
using namespace std;

Board::Board() {
board = new char*[9]; // x9

for(int i = 0; i < 10; i++) { 
board[i] = new char[10]; // y10
}

for(int i = 0; i < 9; i ++) {
 for(int j = 0; j < 10; j++) {
     board[i][j] = 'X';
    }
 }
 
}


void Board::BoardPrint() {
  //temp
  int counter = 9;
for(int i = 0; i < 9; i ++) {
  std::cout << counter << ' ';
  counter--;
 for(int j = 0; j < 10; j++) {
    std::cout << board[i][j] << ' ';
  }
  std::cout << '\n';
 }  
 std::cout << "  A B C D E F G H I J\n";
}

Board::~Board() {
    for (int i = 0; i < 9; i++){
        delete[] board[i];
    }
    delete[] board;
};

/*void Board::placeShips(int numShip) {
  if(numShip == 1){
    //numShip1();
    int row_1 = promptRow();
    int col_1 = promptCol();
    board[row_1][col_1] = 'S';
  }
  if(numShip == 2){

  }


}*/

void Board::Ship1(){
std::cout << "Ship 1: ";
int row_1 = promptRow();
int col_1 = promptCol();
board[row_1][col_1] = 'S';
std::cout << "Ship placed!\n";

}

void Board::Ship2() {
Ship1();
std::cout << "Ship 2: ";
int row_1 = promptRow();
int col_1 = promptCol();
while(checkIfX(row_1, col_1) == false) {
  row_1 = promptRow();
  col_1 = promptCol();
 }

board[row_1][col_1] = 'S'; 
string _direction = direction();

if(_direction == "up"){
  if(row_1 != 0 && checkIfX(row_1-1, col_1) == true){
    board[row_1-1][col_1] = 'S';
  }
  else {
    cout << "Invalid";
  }
 }
else if(_direction == "down"){
  if(row_1 != 8 && checkIfX(row_1+1, col_1) == true){
    board[row_1+1][col_1] = 'S';
  }
  else {
    cout << "Invalid";
  }
 }
 else if(_direction == "left"){
  if(row_1 != 0 && checkIfX(row_1, col_1-1) == true){
    board[row_1][col_1-1] = 'S';
  }
  else {
    cout << "Invalid\n";
  }
 }
 else if(_direction == "right"){
  if(col_1 != 9 && checkIfX(row_1, col_1+1) == true){
    board[row_1][col_1+1] = 'S';
  }
  else {
    cout << "Invalid\n";
  }
 }
cout << "Ship placed.\n";
}

void Board::Ship3() {
  Ship2();
  cout << "\nShip 3: \n";
  int row_1 = promptRow();
  int col_1 = promptCol();
  
  while(checkIfX(row_1, col_1) == false) {
  row_1 = promptRow();
  col_1 = promptCol();
 }

string _direction = direction();
board[row_1][col_1] = 'S';

if(_direction == "up"){
  if(row_1 >= 0 && col_1-2 >= 0){
    if(checkIfX(row_1-1, col_1) == true && checkIfX(row_1-2, col_1) == true) {
    board[row_1-1][col_1] = 'S';
    board[row_1-2][col_1] = 'S';
   }
  }
  else {
    cout << "No empty spots up!";
  }
 }

else if(_direction == "down"){
 if(row_1-1 <= 8 && col_1-2 <= 8) {
   if( checkIfX(row_1+1, col_1) == true && checkIfX(row_1+2, col_1) == true) {
    board[row_1+1][col_1] = 'S';
    board[row_1+2][col_1] = 'S';
  }
   else {
    cout << "No empty spots down!";
  }
 }
}
 else if(_direction == "left"){
   if(col_1-1 >= 0 && col_1-2 >= 0) {
    if(checkIfX(row_1, col_1-1) == true && checkIfX(row_1, col_1-2) == true) {
     board[row_1][col_1-1] = 'S';
     board[row_1][col_1-2] = 'S';
  }
  else {
    cout << "No empty spots down!";
  }
 }
}
 else if(_direction == "right"){
   if(col_1+1 <= 8 && col_1+2 <= 8) {
    if(checkIfX(row_1, col_1+1) == true && checkIfX(row_1, col_1+2) == true) {
     board[row_1][col_1+1] = 'S';
     board[row_1][col_1+2] = 'S';
  }
  else {
    cout << "No Empty Spots\n";
   }
  }
 }
 cout << "Ship Placed!\n";
}

void Board::Ship4() {
  Ship3();
  cout << "Ship 4: \n";
  int row_1 = promptRow();
  int col_1 = promptCol();
  
  while(checkIfX(row_1, col_1) == false) {
  row_1 = promptRow();
  col_1 = promptCol();
 }
board[row_1][col_1] = 'S';
string _direction = direction();

if(_direction == "up"){
  if(row_1 >= 0 && row_1-1 >= 0 && row_1-2 >= 0){
    if(checkIfX(row_1-1, col_1) == true && checkIfX(row_1-2, col_1) == true && checkIfX(row_1-3, col_1) == true) {
    board[row_1-1][col_1] = 'S';
    board[row_1-2][col_1] = 'S';
    board[row_1-3][col_1] = 'S';
   }
  }
  else {
    cout << "No empty spots up!\n";
  }
 }

else if(_direction == "down"){
 if(row_1-1 <= 8 && row_1-2 <= 8 && row_1-3 <= 8) {
   if( checkIfX(row_1+1, col_1) == true && checkIfX(row_1+2, col_1) == true && checkIfX(row_1+3, col_1) == true) {
    board[row_1+1][col_1] = 'S';
    board[row_1+2][col_1] = 'S';
    board[row_1+3][col_1] = 'S';
  }
   else {
    cout << "No empty spots down!";
  }
 }
}
 else if(_direction == "left"){
   if(col_1-1 >= 0 && col_1-2 >= 0 && col_1-3) {
    if(checkIfX(row_1, col_1-1) == true && checkIfX(row_1, col_1-2) == true && checkIfX(row_1, col_1-3) == true) {
     board[row_1][col_1-1] = 'S';
     board[row_1][col_1-2] = 'S';
     board[row_1][col_1-3] = 'S';
  }
  else {
    cout << "No empty spots down!";
  }
 }
}
 else if(_direction == "right"){
   if(col_1+1 <= 8 && col_1+2 <= 8 && col_1+3 <= 8) {
    if(checkIfX(row_1, col_1+1) == true && checkIfX(row_1, col_1+2) == true && checkIfX(row_1, col_1+3) == true) {
     board[row_1][col_1+1] = 'S';
     board[row_1][col_1+2] = 'S';
     board[row_1][col_1+2] = 'S';
  }
  else {
    cout << "No Empty Spots\n";
   }
  }
 }
}

void Board::Ship5() {
 //functions calls previous ships to place.
  Ship4();
  cout << "Ship 5: \n";
  int row_1 = promptRow(); //initial mark acts as a pivot point.
  int col_1 = promptCol();
  
  while(checkIfX(row_1, col_1) == false) {
  row_1 = promptRow();
  col_1 = promptCol();
 }

board[row_1][col_1] = 'S'; //pivot point placed
string _direction = direction();

if(_direction == "up"){
  if(row_1 >= 0 && row_1-1 >= 0 && row_1-2 >= 0 && row_1-3 >= 0 && row_1-4 >= 0){
    if(checkIfX(row_1-1, col_1) == true && checkIfX(row_1-2, col_1) == true && checkIfX(row_1-3, col_1) == true && checkIfX(row_1-4, col_1) == true) {
    board[row_1-1][col_1] = 'S';
    board[row_1-2][col_1] = 'S';
    board[row_1-3][col_1] = 'S';
    board[row_1-4][col_1] = 'S';
   }
  }
  else {
    cout << "No empty spots up!\n";
  }
 }

else if(_direction == "down"){
 if(row_1+1 <= 8 && row_1+2 <= 8 && row_1+3 <= 8 && row_1+4 <= 8) {
   if( checkIfX(row_1+1, col_1) == true && checkIfX(row_1+2, col_1) == true && checkIfX(row_1+3, col_1) == true && checkIfX(row_1+4, col_1) == true) {
    board[row_1+1][col_1] = 'S';
    board[row_1+2][col_1] = 'S';
    board[row_1+3][col_1] = 'S';
    board[row_1+4][col_1] = 'S';
  }
   else {
    cout << "No empty spots down!\n";
  }
 }
}
 else if(_direction == "left"){
   if(col_1-1 >= 0 && col_1-2 >= 0 && col_1-3 && col_1-4) {
    if(checkIfX(row_1, col_1-1) == true && checkIfX(row_1, col_1-2) == true && checkIfX(row_1, col_1-3) == true && checkIfX(row_1, col_1-4) == true) {
     board[row_1][col_1-1] = 'S';
     board[row_1][col_1-2] = 'S';
     board[row_1][col_1-3] = 'S';
     board[row_1][col_1-4] = 'S';
  }
  else {
    cout << "No empty spots down!\n";
  }
 }
}
 else if(_direction == "right"){
   if(col_1+1 <= 8 && col_1+2 <= 8 && col_1+3 <= 8 && col_1+4 <= 8) {
    if(checkIfX(row_1, col_1+1) == true && checkIfX(row_1, col_1+2) == true && checkIfX(row_1, col_1+3) == true && checkIfX(row_1, col_1+4) == true) {
     board[row_1][col_1+1] = 'S';
     board[row_1][col_1+2] = 'S';
     board[row_1][col_1+3] = 'S';
     board[row_1][col_1+4] = 'S';
  }
  else {
    cout << "No Empty Spots\n";
   }
  }
 }
}

void Board::Ship6() {
 //function calls previous ships to place  
  Ship5();
  cout << "Ship 6: \n";
  int row_1 = promptRow();
  int col_1 = promptCol();
  
  while(checkIfX(row_1, col_1) == false) {
  row_1 = promptRow();
  col_1 = promptCol();
 }

board[row_1][col_1] = 'S'; //initial point placed.
string _direction = direction();

if(_direction == "up"){
  if(row_1 >= 0 && row_1-1 >= 0 && row_1-2 >= 0 && row_1-3 >= 0 && row_1-4 >= 0 && row_1-5 >= 0){
    if(checkIfX(row_1-1, col_1) == true && checkIfX(row_1-2, col_1) == true && checkIfX(row_1-3, col_1) == true && checkIfX(row_1-4, col_1) == true && checkIfX(row_1-5, col_1) == true) {
    board[row_1-1][col_1] = 'S';
    board[row_1-2][col_1] = 'S';
    board[row_1-3][col_1] = 'S';
    board[row_1-4][col_1] = 'S';
    board[row_1-5][col_1] = 'S';
   }
  }
  else {
    cout << "No empty spots up!";
  }
 }

else if(_direction == "down"){
 if(row_1+1 <= 8 && row_1+2 <= 8 && row_1+3 <= 8 && row_1+4 <= 8 && row_1+5 <= 8) {
   if( checkIfX(row_1+1, col_1) == true && checkIfX(row_1+2, col_1) == true && checkIfX(row_1+3, col_1) == true && checkIfX(row_1+4, col_1) == true && checkIfX(row_1+5, col_1) == true) {
    board[row_1+1][col_1] = 'S';
    board[row_1+2][col_1] = 'S';
    board[row_1+3][col_1] = 'S';
    board[row_1+4][col_1] = 'S';
    board[row_1+5][col_1] = 'S';
  }
   else {
    cout << "No empty spots down!\n";
  }
 }
}
 else if(_direction == "left"){
   if(col_1-1 >= 0 && col_1-2 >= 0 && col_1-3 && col_1-4 && col_1-5) {
    if(checkIfX(row_1, col_1-1) == true && checkIfX(row_1, col_1-2) == true && checkIfX(row_1, col_1-3) == true && checkIfX(row_1, col_1-4) == true && checkIfX(row_1, col_1-5) == true) {
     board[row_1][col_1-1] = 'S';
     board[row_1][col_1-2] = 'S';
     board[row_1][col_1-3] = 'S';
     board[row_1][col_1-4] = 'S';
     board[row_1][col_1-5] = 'S';
  }
  else {
    cout << "No empty spots down!\n";
  }
 }
}
 else if(_direction == "right"){
   if(col_1+1 <= 8 && col_1+2 <= 8 && col_1+3 <= 8 && col_1+4 <= 8 && col_1+5 <= 8) {
    if(checkIfX(row_1, col_1+1) == true && checkIfX(row_1, col_1+2) == true && checkIfX(row_1, col_1+3) == true && checkIfX(row_1, col_1+4) == true && checkIfX(row_1, col_1+5) == true) {
     board[row_1][col_1+1] = 'S';
     board[row_1][col_1+2] = 'S';
     board[row_1][col_1+3] = 'S';
     board[row_1][col_1+4] = 'S';
     board[row_1][col_1+5] = 'S';
  }
  else {
    cout << "No Empty Spots\n";
   }
  }
 }
}




bool Board::checkIfX(int row_1, int col_1) {
if(board[row_1][col_1] == 'X') {
return true;
 }
 else{
   return false;
 }
}

int Board::promptCol() {
  char m_col;
  bool valid = false;
  while(valid == false) {
    std::cout << "which col?(char)\n";
    std::cin >> m_col;
    valid = checkCol(m_col);
}
  int col = convertCharToInt(m_col);
  return(col);
}

int Board::promptRow(){
  int m_row;
  bool valid = false;
  while(valid == false){
    std::cout << "which row?(int)\n";
    std::cin >> m_row;
    valid = checkRow(m_row);
  }
  return(9-m_row); // temp // 
}

int Board::convertCharToInt(char m_col) {
  if(m_col == 'A'){
    return(0);
  } 
  else if(m_col == 'B'){
    return(1);
  }
  else if(m_col == 'C'){
    return(2);
  }
  else if(m_col == 'D'){
    return(3);
  }  
  else if(m_col == 'E'){
    return(4);
  }
  else if(m_col == 'F'){
    return(5);
  } 
  else if(m_col == 'G'){
    return(6);
  }
  else if(m_col == 'H'){
    return(7);
  }
  else if(m_col == 'I'){
    return(8);
  }
  else {
    return(9);
  }
}

string Board::direction() {
 string shipDirection;
 cin >> shipDirection;
 cout << "Where would you like to place the rest of your ship?: \n";
 cin >> shipDirection;
 return(shipDirection);
}




bool Board::checkCol(char m_col) {
  if(m_col == 'A' || m_col == 'B' || m_col == 'C' || m_col == 'D' || m_col == 'E' || m_col == 'F' || m_col == 'G' || m_col == 'H' || m_col == 'I' || m_col == 'J') {
    return true;
  }
  else {
    return false;
  }
}


bool Board::checkRow(int m_row) {
  if(m_row == 1 || m_row == 2 || m_row == 3 || m_row == 4 || m_row == 5 || m_row == 6 || m_row == 7 || m_row == 8 || m_row == 9) {
    return true;
 }
else {
  return false;
 }
}


//-------------------------------------------------------------------------END OF PROGRAM---------------------------------------------------------------------------//





















/*void Board::askPlacement(int row, int col) {
string direction;
cout << "Would you like to place the next coordinate; up, down, left or right?";
cin >> direction;

if(direction == "up" || direction == "UP" || direction == "Up" || direction == "uP") {
 if(row != 0) {
   if(checkIfX(row,col-1) == true) {
     
    }
  }

 }
}*/