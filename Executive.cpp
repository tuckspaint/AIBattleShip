//Executive.cpp iteration 1.2
#include "Executive.h"
#include "Board.h"
#include <iostream>
#include <stdio.h>
using namespace std;

void Executive::run() {
char hitmiss_1[9][10];
char hitmiss_2[9][10];

for(int i = 0; i < 9; i ++) {
 for(int j = 0; j < 10; j++) {
     hitmiss_1[i][j] = '*';
     hitmiss_2[i][j] = '*';
    }
 }

int hitcount = 0;
int hitcount2 = 0;
int choice;
int row;
char col;
int numShips;
int new_char;
for( ; ; )
{
	cout << "How many ships would you like to play with? (enter 1-6):\n";
	cin >> numShips;
	if(numShips == 1 || numShips == 2 || numShips == 3 || numShips == 4 || numShips == 5 || numShips == 6)
	{
		break;
	}
	else
	{
		cout << "Invalid input, enter again" << endl;
	}
}
cout << "\nPLAYER 1 BOARD:\n";
Board board_1(numShips);
std::cout << "\x1B[2J\x1B[H";
cout << "\nPLAYER 2 BOARD:\n";
Board board_2(numShips);
std::cout << "\x1B[2J\x1B[H";

winningCondition(numShips);
do {
cout << "Its player " << currentPlayer << "'s turn.\n";
printMenu();
cin >> choice;

if(choice == 1) {
    if(currentPlayer == 1) {
        cout << "PLAYER 1 BOARD:\n";
        board_1.BoardPrint();
    }
    else {
        cout << "PLAYER 2 BOARD\n";
        board_2.BoardPrint();
    }
}

//choice 2
if(choice == 2) {
    bool bad = false;
	bool valid = false;
    do {
    cout << "What row would you like to hit?(int)\n";
	cin >> row;
    if(row == 1 || row == 2 || row == 3 || row == 4 || row == 5 || row == 6 || row == 7 || row == 8 || row == 9){
        valid = true;
    }
	bad = cin.fail();
    if(bad){
    cout << "Error message" << endl;
	cin.clear();
	cin.ignore(1000, '\n');
    }
 }while(valid == false);

for( ; ;)
{
	cout << "What col would you like to hit?(char)\n";
	cin >> col;
	if(col == 'A' || col == 'a'|| col == 'B' || col == 'b' || col == 'C' || col == 'c'
  || col == 'D' || col == 'd' || col == 'E' || col == 'e'|| col == 'F' ||
   col == 'f' || col == 'G' || col == 'g' || col == 'H' || col == 'h' || col == 'I' || col == 'i' || col == 'J' || col == 'j')
   {
	   break;
   }
   else
   {
	   cout << "Invalid input, enter again" << endl;
   }
}
if(currentPlayer == 1) {
    new_char = board_2.convertCharToInt(col);
    if(board_2.checkBoard(row,new_char) == true && hitmiss_1[9-row][new_char] != 'H')
    {
        cout << "You hit their ship\n";
        hitmiss_1[9-row][new_char] = 'H';
        hitcount++;
        if(winningCondition(numShips) == hitcount) {
            cout << "Congratulations Player 1! You win!\n";
            return;
        }
    }
    else {
        cout << "you missed their ship.\n";
        hitmiss_1[9-row][new_char] = 'M';
    }
}

if(currentPlayer == 2) {
    new_char = board_1.convertCharToInt(col);
    if(board_1.checkBoard(row,new_char) == true && hitmiss_2[9-row][new_char] != 'H')
    {
        cout << "You hit their ship\n";
        hitmiss_2[9-row][new_char] = 'H';
        hitcount2++;
        if(winningCondition(numShips) == hitcount2) {
            cout << "Congratulations Player 2! You win!\n";
            return;
        }
    }
    else {
        cout << "you missed their ship.\n";
        hitmiss_2[9-row][new_char] = 'M';
    }
 }
 std::cin.ignore(1024,'\n');
 cout << "Press Enter to continue:";
 std::cin.get();
playerChange();
}

//choice 3
if(choice == 3) {
    cout << "    Hit/Miss Board\n";
    if(currentPlayer == 1) {
         int counter = 9;
for(int i = 0; i < 9; i ++) {
  cout << counter << ' ';
  counter--;
 for(int j = 0; j < 10; j++) {
    cout << hitmiss_1[i][j] << ' ';
  }
  cout << '\n';
 }
 cout << "  A B C D E F G H I J\n";
     }

    else if(currentPlayer == 2) {
         int counter = 9;
     for(int i = 0; i < 9; i ++) {
        cout << counter << ' ';
        counter--;
      for(int j = 0; j < 10; j++) {
        cout << hitmiss_2[i][j] << ' ';
       }
  cout << '\n';
      }
 cout << "  A B C D E F G H I J\n";
    }
}
    } while(choice != 4);
}

void Executive::printMenu() {
cout << "1. See your board.\n";
cout << "2. Try to hit ship on other board.\n";
cout << "3. Print hit/miss board \n";
cout << "4. exit game.\n";
}

int Executive::winningCondition(int numShips) {
int winningCon = 0;
if(numShips == 1) {
    winningCon = 1;
}
else if(numShips == 2) {
    winningCon = 3;
}
else if(numShips == 3) {
    winningCon = 6;
}
else if(numShips == 4) {
    winningCon = 10;
}
else if(numShips == 5) {
    winningCon = 15;
}
else {
    winningCon = 21;
}

return winningCon;
}


void Executive::playerChange(){
    if(currentPlayer == 1){
        currentPlayer = 2;
    }
    else {
        currentPlayer = 1;
    }
    std::cout << "\x1B[2J\x1B[H";
}
