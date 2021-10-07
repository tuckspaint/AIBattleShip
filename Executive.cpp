//Executive.cpp iteration 1.2
#include "Executive.h"
#include "Board.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>

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
string userChoice;
aiChosen = 0;
//medium AI stuff
int aiRow;
int aiCol;
int initHit[2] = {11, 11}; //initHit {11,11} means a ship has not been hit, anything else is the location of the first hit on the most recently hit ship
int prevMedTurn[2]; //last coordinate medium ai attacked
int dist = 0; //iterator for some while loops pretty much
char tempSize; //for checkSunk
	
while(1)
{
    cout << "Which game mode would you like to play with? (PvP or PvAI):";
    cin >> userChoice;
    if(userChoice == "PvP" || userChoice == "PvAI")
    {
        if(userChoice == "PvAI")
        {
            aiChosen = 1;
            while(1)
            {
                cout << "What difficulty do you want to play on? (1=Easy, 2=Medium, 3=Hard):";
                cin >> modeChosen;
                if(modeChosen == 1 || modeChosen == 2 || modeChosen == 3)
                {
                    break;
                }
                else
                {
                    cout << "Invalid input, enter again" << endl;
                }
            }
        }
        break;
    }
    else
    {
        cout << "Invalid input, enter again" << endl;
    }

}
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
Board board_1(numShips, 0);
std::cout << "\x1B[2J\x1B[H";
if (aiChosen == 0) {
	cout << "\nPLAYER 2 BOARD:\n";
}
	Board board_2(numShips, aiChosen);
	std::cout << "\x1B[2J\x1B[H";


winningCondition(numShips);

do {
    //Shows if it the players or the AIs turn at the beginning of the turn
  
    if(currentPlayer == 1 || currentPlayer == 2)
    {
        cout << "Its player " << currentPlayer << "'s turn.\n";
        printMenu();
        cin >> choice;
    }
    else
    {
        cout << "It's the robot's turn\n";
        choice = 2;
    }

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
        if(currentPlayer == 1 || currentPlayer == 2)
        {
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
                cout << "Enter a valid position." << endl;
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
        }
        else
        {
            cout << "The AI is currently choosing a move\n";
            sleep(2);

        }

        if(currentPlayer == 1) {
            new_char = board_2.convertCharToInt(col);
            if(board_2.checkBoard(row,new_char) == true && hitmiss_1[9-row][new_char] != 'H')
            {
                //cout << "You hit their ship\n";
		Playhit(150);
                hitmiss_1[9-row][new_char] = 'H';
                board_2.board[9-row][new_char] = 'H';
                hitcount++;
                if(winningCondition(numShips) == hitcount) {
                    //cout << "Congratulations Player 1! You win!\n";
		    Playp1win(100, 1);
                    return;
                }
            }
            else if(hitmiss_1[9-row][new_char] == 'H' || hitmiss_1[9-row][new_char] == 'M') {
                cout << "You already hit that spot.\n";
            }

            else {
                //cout << "you missed their ship.\n";
		Playmiss(100);
                hitmiss_1[9-row][new_char] = 'M';
                board_2.board[9-row][new_char] = 'M';
            }
    }

        if(currentPlayer == 2) {
            new_char = board_1.convertCharToInt(col);
            if(board_1.checkBoard(row,new_char) == true && hitmiss_2[9-row][new_char] != 'H')
            {
                //cout << "You hit their ship\n";
		Playhit(150);
                hitmiss_2[9-row][new_char] = 'H';
                board_1.board[9-row][new_char] = 'H';
                hitcount2++;
                if(winningCondition(numShips) == hitcount2) {
                    //cout << "Congratulations Player 2! You win!\n";
		    Playp2win(100, 1);
                    return;
                }
            }
            else if(hitmiss_2[9-row][new_char] == 'H' || hitmiss_2[9-row][new_char] == 'M') {
                cout << "You already hit that spot.\n";
            }

            else {
                //cout << "you missed their ship.\n";
		Playmiss(100);
                hitmiss_2[9-row][new_char] = 'M';
                board_1.board[9-row][new_char] = 'M';
            }
        }

        if(currentPlayer == 3) {
            if(modeChosen == 1)
            {
                //put code for easy move in here
                aiRow = aiRandomRow();
                aiCol = aiRandomCol();
                if(board_1.checkBoard(aiRow,aiCol) == true && hitmiss_2[9-aiRow][aiCol] != 'H')
                {
                        hitmiss_2[9-aiRow][aiCol] = 'H';
                        board_1.board[9-aiRow][aiCol] = 'H';
                        hitcount2++;
                        cout << "The AI hit a ship!";
                        if(winningCondition(numShips) == hitcount2) {
                        //cout << "Congratulations the AI won!\n";
			Playp2win(100,1);
                        return;
                        }
                }
                else if(hitmiss_2[9-aiRow][aiCol] == 'H' || hitmiss_2[9-aiRow][aiCol] == 'M') {
                        cout << "The AI shot at the same spot again.\n";
                }
                else {
                        cout << "The AI missed their shot.\n";
                        hitmiss_2[9-aiRow][aiCol] = 'M';
                    board_1.board[9-aiRow][aiCol] = 'M';
                }
            }
            else if(modeChosen == 2)
            {
                //put code for medium move in here	
                if (initHit[0] == 11 && initHit[1] == 11) { //random attack if a ship hasnt been hit
                    //randomize a coordinate until it gets a spot that hasnt been attacked
                    do {
                        aiRow = aiRandomRow();
                        aiCol = aiRandomCol();
                    } while(hitmiss_2[9-aiRow][aiCol] == 'H' || hitmiss_2[9-aiRow][aiCol] == 'M');
                        
                    if (board_1.checkBoard(aiRow, aiCol) && hitmiss_2[9-aiRow][aiCol] != 'H') {//im assuming we're just gonna use board_2 and hitmiss_2 for the ai
                        initHit[0] = aiRow;
                        initHit[0] = aiCol;
                    }
                }
                else {
                    if (prevMedTurn == initHit) {
                        //try to attack north of initHit
                        dist = 1;
                        while (initHit[0] + dist <= 9) {//while there is a space on the board dist spaces north of initHit
                            if (hitmiss_2[9-(initHit[0] + dist)][initHit[1]] == 'M') {//if the ai has already missed in the tile dist spaces north of initHit
                                //exit loop, try east next
                                break;
                            }
                            else if (hitmiss_2[9-(initHit[0] + dist)][initHit[1]] == 'H') {//if the tile dist spaces north of initHit has already been hit (could be part of the same ship)
                                dist++;
                            }
                            else {//if the tile dist spaces north of initHit has not been attacked
                                //attack dist spaces north of initHit
                                aiRow = initHit[0] + dist;
                                aiCol = initHit[1];
                                break;
                            }
                        }
                        if (initHit[0] + dist > 9 || hitmiss_2[9-(initHit[0] + dist)][initHit[1]] == 'M') {//if attacking north failed
                            //try to attack east of initHit
                            dist = 1;
                            while (initHit[1] + dist <= 9) {//while there is a space on the board dist spaces east of initHit
                                if (hitmiss_2[9-initHit[0]][initHit[1] + dist] == 'M') {//if the ai has already missed in the tile dist spaces east of initHit
                                    //exit loop, try south next
                                    break;
                                }
                                else if (hitmiss_2[9-initHit[0]][initHit[1] + dist] == 'H') {//if the tile dist spaces east of initHit has already been hit (could be part of the same ship)
                                    dist++;
                                }
                                else {//if the tile dist spaces east of initHit has not been attacked
                                    //attack dist spaces east of initHit
                                    aiRow = initHit[0];
                                    aiCol = initHit[1] + dist;
                                    break;
                                }
                            }	
                        }
                        if (initHit[1] + dist > 9 || hitmiss_2[9-initHit[0]][initHit[1] + dist] == 'M') {//if attacking east failed
                            //try to attack south of initHit
                            dist = 1;
                            while (initHit[0] - dist >= 1) {//while there is a space on the board dist spaces south of initHit
                                if (hitmiss_2[9-(initHit[0]-dist)][initHit[1]] == 'M') {//if the ai has already missed in the tile dist spaces south of initHit
                                    //exit loop, try west next
                                    break;
                                }
                                else if (hitmiss_2[9-(initHit[0]-dist)][initHit[1]] == 'H') {//if the tile dist spaces south of initHit has already been hit (could be part of the same ship)
                                    dist++;
                                }
                                else {//if the tile dist spaces south of initHit has not been attacked
                                    //attack dist spaces south of initHit
                                    aiRow = initHit[0] - dist;
                                    aiCol = initHit[1];
                                    break;
                                }
                            }	
                        }
                        if (initHit[0] + dist < 1 || hitmiss_2[9-(initHit[0] - dist)][initHit[1]] == 'M') {//if attacking south failed
                            //try to attack west of initHit
                            dist = 1;
                            while (initHit[1] - dist >= 0) {//while there is a space on the board dist spaces west of initHit
                                if (hitmiss_2[9-initHit[0]][initHit[1] - dist] == 'M') {//if the ai has already missed in the tile dist spaces west of initHit
                                    //exit loop, try south next
                                    break;
                                }
                                else if (hitmiss_2[9-initHit[0]][initHit[1] - dist] == 'H') {//if the tile dist spaces west of initHit has already been hit (could be part of the same ship)
                                    dist++;
                                }
                                else {//if the tile dist spaces west of initHit has not been attacked
                                    //attack dist spaces west of initHit
                                    aiRow = initHit[0];
                                    aiCol = initHit[1] - dist;
                                    break;
                                }
                            }	
                        }
                        if (initHit[1] - dist < 0 || hitmiss_2[9-initHit[0]][initHit[1] - dist] == 'M') {//if attacking west failed
                            //this shouldn't really be possible but i'll just try to attack a random spot and reset initHit if it happens somehow
                            //randomize a coordinate until it gets a spot that hasnt been attacked
                            initHit[0] = 11;
                            initHit[1] = 11;

                            do {
                                aiRow = aiRandomRow();
                                aiCol = aiRandomCol();
                            } while(hitmiss_2[9-aiRow][aiCol] == 'H' || hitmiss_2[9-aiRow][aiCol] == 'M');
                        
                            if (board_1.checkBoard(aiRow, aiCol) && hitmiss_2[9-aiRow][aiCol] != 'H') {//im assuming we're just gonna use board_2 and hitmiss_2 for the ai
                        	initHit[0] = aiRow;
                        	initHit[0] = aiCol;
                            }
                        }
                    }
                    else if (prevMedTurn[0] > initHit[0]) { //last turn was north of initHit
                        if (board_1.checkBoard(prevMedTurn[0], prevMedTurn[1])) { //if last turn was a hit
                            dist = 1;
                            while (initHit[0] + dist <= 9) {//while there is a space on the board dist spaces north of initHit
                                if (hitmiss_2[9-(initHit[0] + dist)][initHit[1]] == 'M') {//if the ai has already missed in the tile dist spaces north of initHit
                                    //exit loop, try east next
                                    break;
                                }
                                else if (hitmiss_2[9-(initHit[0] + dist)][initHit[1]] == 'H') {//if the tile dist spaces north of initHit has already been hit (could be part of the same ship)
                                    dist++;
                                }
                                else {//if the tile dist spaces north of initHit has not been attacked
                                    //attack dist spaces north of initHit
                                    aiRow = initHit[0] + dist;
                                    aiCol = initHit[1];
                                    break;
                                }
                            }
                            if (initHit[0] + dist > 9 || hitmiss_2[9-(initHit[0] + dist)][initHit[1]] == 'M') {//if attacking north failed
                                //try to attack east of initHit
                                dist = 1;
                                while (initHit[1] + dist <= 9) {//while there is a space on the board dist spaces east of initHit
                                    if (hitmiss_2[9-initHit[0]][initHit[1] + dist] == 'M') {//if the ai has already missed in the tile dist spaces east of initHit
                                        //exit loop, try south next
                                        break;
                                    }
                                    else if (hitmiss_2[9-initHit[0]][initHit[1] + dist] == 'H') {//if the tile dist spaces east of initHit has already been hit (could be part of the same ship)
                                        dist++;
                                    }
                                    else {//if the tile dist spaces east of initHit has not been attacked
                                        //attack dist spaces east of initHit
                                        aiRow = initHit[0];
                                        aiCol = initHit[1] + dist;
                                        break;
                                    }
                                }	
                            }
                            if (initHit[1] + dist > 9 || hitmiss_2[9-initHit[0]][initHit[1] + dist] == 'M') {//if attacking east failed
                                //try to attack south of initHit
                                dist = 1;
                                while (initHit[0] - dist >= 1) {//while there is a space on the board dist spaces south of initHit
                                    if (hitmiss_2[9-(initHit[0]-dist)][initHit[1]] == 'M') {//if the ai has already missed in the tile dist spaces south of initHit
                                        //exit loop, try west next
                                        break;
                                    }
                                    else if (hitmiss_2[9-(initHit[0]-dist)][initHit[1]] == 'H') {//if the tile dist spaces south of initHit has already been hit (could be part of the same ship)
                                        dist++;
                                    }
                                    else {//if the tile dist spaces south of initHit has not been attacked
                                        //attack dist spaces south of initHit
                                        aiRow = initHit[0] - dist;
                                        aiCol = initHit[1];
                                        break;
                                    }
                                }	
                            }
                            if (initHit[0] + dist < 1 || hitmiss_2[9-(initHit[0] - dist)][initHit[1]] == 'M') {//if attacking south failed
                                //try to attack west of initHit
                                dist = 1;
                                while (initHit[1] - dist >= 0) {//while there is a space on the board dist spaces west of initHit
                                    if (hitmiss_2[9-initHit[0]][initHit[1] - dist] == 'M') {//if the ai has already missed in the tile dist spaces west of initHit
                                        //exit loop, try south next
                                        break;
                                    }
                                    else if (hitmiss_2[9-initHit[0]][initHit[1] - dist] == 'H') {//if the tile dist spaces west of initHit has already been hit (could be part of the same ship)
                                        dist++;
                                    }
                                    else {//if the tile dist spaces west of initHit has not been attacked
                                        //attack dist spaces west of initHit
                                        aiRow = initHit[0];
                                        aiCol = initHit[1] - dist;
                                        break;
                                    }
                                }	
                            }
                            if (initHit[1] - dist < 0 || hitmiss_2[9-initHit[0]][initHit[1] - dist] == 'M') {//if attacking west failed
                                //this shouldn't really be possible but i'll just try to attack a random spot and reset initHit if it happens somehow
                                //randomize a coordinate until it gets a spot that hasnt been attacked
                            	initHit[0] = 11;
                            	initHit[1] = 11;

                                do {
                                    aiRow = aiRandomRow();
                                    aiCol = aiRandomCol();
                                } while(hitmiss_2[9-aiRow][aiCol] == 'H' || hitmiss_2[9-aiRow][aiCol] == 'M');
                            
                                if (board_1.checkBoard(aiRow, aiCol) && hitmiss_2[9-aiRow][aiCol] != 'H') {//im assuming we're just gonna use board_2 and hitmiss_2 for the ai
                        		initHit[0] = aiRow;
                        		initHit[0] = aiCol;
                                }
                            }
                        }
                        else { //there is nothing directly north of initHit
                            //try to attack east of initHit
                            dist = 1;
                            while (initHit[1] + dist <= 9) {//while there is a space on the board dist spaces east of initHit
                                if (hitmiss_2[9-initHit[0]][initHit[1] + dist] == 'M') {//if the ai has already missed in the tile dist spaces east of initHit
                                    //exit loop, try south next
                                    break;
                                }
                                else if (hitmiss_2[9-initHit[0]][initHit[1] + dist] == 'H') {//if the tile dist spaces east of initHit has already been hit (could be part of the same ship)
                                    dist++;
                                }
                                else {//if the tile dist spaces east of initHit has not been attacked
                                    //attack dist spaces east of initHit
                                    aiRow = initHit[0];
                                    aiCol = initHit[1] + dist;
                                    break;
                                }
                            }	
                            if (initHit[1] + dist > 9 || hitmiss_2[9-initHit[0]][initHit[1] + dist] == 'M') {//if attacking east failed
                                //try to attack south of initHit
                                dist = 1;
                                while (initHit[0] - dist >= 1) {//while there is a space on the board dist spaces south of initHit
                                    if (hitmiss_2[9-(initHit[0]-dist)][initHit[1]] == 'M') {//if the ai has already missed in the tile dist spaces south of initHit
                                        //exit loop, try west next
                                        break;
                                    }
                                    else if (hitmiss_2[9-(initHit[0]-dist)][initHit[1]] == 'H') {//if the tile dist spaces south of initHit has already been hit (could be part of the same ship)
                                        dist++;
                                    }
                                    else {//if the tile dist spaces south of initHit has not been attacked
                                        //attack dist spaces south of initHit
                                        aiRow = initHit[0] - dist;
                                        aiCol = initHit[1];
                                        break;
                                    }
                                }	
                            }
                            if (initHit[0] + dist < 1 || hitmiss_2[9-(initHit[0] - dist)][initHit[1]] == 'M') {//if attacking south failed
                                //try to attack west of initHit
                                dist = 1;
                                while (initHit[1] - dist >= 0) {//while there is a space on the board dist spaces west of initHit
                                    if (hitmiss_2[9-initHit[0]][initHit[1] - dist] == 'M') {//if the ai has already missed in the tile dist spaces west of initHit
                                        //exit loop, try south next
                                        break;
                                    }
                                    else if (hitmiss_2[9-initHit[0]][initHit[1] - dist] == 'H') {//if the tile dist spaces west of initHit has already been hit (could be part of the same ship)
                                        dist++;
                                    }
                                    else {//if the tile dist spaces west of initHit has not been attacked
                                        //attack dist spaces west of initHit
                                        aiRow = initHit[0];
                                        aiCol = initHit[1] - dist;
                                        break;
                                    }
                                }	
                            }
                            if (initHit[1] - dist < 0 || hitmiss_2[9-initHit[0]][initHit[1] - dist] == 'M') {//if attacking west failed
                                //this shouldn't really be possible but i'll just try to attack a random spot and reset initHit if it happens somehow
                                //randomize a coordinate until it gets a spot that hasnt been attacked
                            	initHit[0] = 11;
                            	initHit[1] = 11;

                                do {
                                    aiRow = aiRandomRow();
                                    aiCol = aiRandomCol();
                                } while(hitmiss_2[9-aiRow][aiCol] == 'H' || hitmiss_2[9-aiRow][aiCol] == 'M');
                            
                                if (board_1.checkBoard(aiRow, aiCol) && hitmiss_2[9-aiRow][aiCol] != 'H') {//im assuming we're just gonna use board_2 and hitmiss_2 for the ai
                        		initHit[0] = aiRow;
                        		initHit[0] = aiCol;
                                }
                            }
                        }
                    }
                    else if (prevMedTurn[1] > initHit[1]) { //last turn was east of initHit
                        if (board_1.checkBoard(prevMedTurn[0], prevMedTurn[1])) { //if last turn was a hit
                            //try to attack east of initHit
                            dist = 1;
                            while (initHit[1] + dist <= 9) {//while there is a space on the board dist spaces east of initHit
                                if (hitmiss_2[9-initHit[0]][initHit[1] + dist] == 'M') {//if the ai has already missed in the tile dist spaces east of initHit
                                    //exit loop, try south next
                                    break;
                                }
                                else if (hitmiss_2[9-initHit[0]][initHit[1] + dist] == 'H') {//if the tile dist spaces east of initHit has already been hit (could be part of the same ship)
                                    dist++;
                                }
                                else {//if the tile dist spaces east of initHit has not been attacked
                                    //attack dist spaces east of initHit
                                    aiRow = initHit[0];
                                    aiCol = initHit[1] + dist;
                                    break;
                                }
                            }	
                            if (initHit[1] + dist > 9 || hitmiss_2[9-initHit[0]][initHit[1] + dist] == 'M') {//if attacking east failed
                                //try to attack south of initHit
                                dist = 1;
                                while (initHit[0] - dist >= 1) {//while there is a space on the board dist spaces south of initHit
                                    if (hitmiss_2[9-(initHit[0]-dist)][initHit[1]] == 'M') {//if the ai has already missed in the tile dist spaces south of initHit
                                        //exit loop, try west next
                                        break;
                                    }
                                    else if (hitmiss_2[9-(initHit[0]-dist)][initHit[1]] == 'H') {//if the tile dist spaces south of initHit has already been hit (could be part of the same ship)
                                        dist++;
                                    }
                                    else {//if the tile dist spaces south of initHit has not been attacked
                                        //attack dist spaces south of initHit
                                        aiRow = initHit[0] - dist;
                                        aiCol = initHit[1];
                                        break;
                                    }
                                }	
                            }
                            if (initHit[0] + dist < 1 || hitmiss_2[9-(initHit[0] - dist)][initHit[1]] == 'M') {//if attacking south failed
                                //try to attack west of initHit
                                dist = 1;
                                while (initHit[1] - dist >= 0) {//while there is a space on the board dist spaces west of initHit
                                    if (hitmiss_2[9-initHit[0]][initHit[1] - dist] == 'M') {//if the ai has already missed in the tile dist spaces west of initHit
                                        //exit loop, try south next
                                        break;
                                    }
                                    else if (hitmiss_2[9-initHit[0]][initHit[1] - dist] == 'H') {//if the tile dist spaces west of initHit has already been hit (could be part of the same ship)
                                        dist++;
                                    }
                                    else {//if the tile dist spaces west of initHit has not been attacked
                                        //attack dist spaces west of initHit
                                        aiRow = initHit[0];
                                        aiCol = initHit[1] - dist;
                                        break;
                                    }
                                }	
                            }
                            if (initHit[1] - dist < 0 || hitmiss_2[9-initHit[0]][initHit[1] - dist] == 'M') {//if attacking west failed
                                //this shouldn't really be possible but i'll just try to attack a random spot and reset initHit if it happens somehow
                                //randomize a coordinate until it gets a spot that hasnt been attacked
                            	initHit[0] = 11;
                            	initHit[1] = 11;

                                do {
                                    aiRow = aiRandomRow();
                                    aiCol = aiRandomCol();
                                } while(hitmiss_2[9-aiRow][aiCol] == 'H' || hitmiss_2[9-aiRow][aiCol] == 'M');
                            
                                if (board_1.checkBoard(aiRow, aiCol) && hitmiss_2[9-aiRow][aiCol] != 'H') {//im assuming we're just gonna use board_2 and hitmiss_2 for the ai
                        		initHit[0] = aiRow;
                        		initHit[0] = aiCol;
                                }
                            }
                        }
                        else { //there is nothing directly east of initHit	
                            //try to attack south of initHit
                            dist = 1;
                            while (initHit[0] - dist >= 1) {//while there is a space on the board dist spaces south of initHit
                                if (hitmiss_2[9-(initHit[0]-dist)][initHit[1]] == 'M') {//if the ai has already missed in the tile dist spaces south of initHit
                                    //exit loop, try west next
                                    break;
                                }
                                else if (hitmiss_2[9-(initHit[0]-dist)][initHit[1]] == 'H') {//if the tile dist spaces south of initHit has already been hit (could be part of the same ship)
                                    dist++;
                                }
                                else {//if the tile dist spaces south of initHit has not been attacked
                                    //attack dist spaces south of initHit
                                    aiRow = initHit[0] - dist;
                                    aiCol = initHit[1];
                                    break;
                                }
                            }	
                            if (initHit[0] + dist < 1 || hitmiss_2[9-(initHit[0] - dist)][initHit[1]] == 'M') {//if attacking south failed
                                //try to attack west of initHit
                                dist = 1;
                                while (initHit[1] - dist >= 0) {//while there is a space on the board dist spaces west of initHit
                                    if (hitmiss_2[9-initHit[0]][initHit[1] - dist] == 'M') {//if the ai has already missed in the tile dist spaces west of initHit
                                        //exit loop, try south next
                                        break;
                                    }
                                    else if (hitmiss_2[9-initHit[0]][initHit[1] - dist] == 'H') {//if the tile dist spaces west of initHit has already been hit (could be part of the same ship)
                                        dist++;
                                    }
                                    else {//if the tile dist spaces west of initHit has not been attacked
                                        //attack dist spaces west of initHit
                                        aiRow = initHit[0];
                                        aiCol = initHit[1] - dist;
                                        break;
                                    }
                                }	
                            }
                            if (initHit[1] - dist < 0 || hitmiss_2[9-initHit[0]][initHit[1] - dist] == 'M') {//if attacking west failed
                                //this shouldn't really be possible but i'll just try to attack a random spot and reset initHit if it happens somehow
                                //randomize a coordinate until it gets a spot that hasnt been attacked
                            	initHit[0] = 11;
                            	initHit[1] = 11;

                                do {
                                    aiRow = aiRandomRow();
                                    aiCol = aiRandomCol();
                                } while(hitmiss_2[9-aiRow][aiCol] == 'H' || hitmiss_2[9-aiRow][aiCol] == 'M');
                            
                                if (board_1.checkBoard(aiRow, aiCol) && hitmiss_2[9-aiRow][aiCol] != 'H') {//im assuming we're just gonna use board_2 and hitmiss_2 for the ai
                        		initHit[0] = aiRow;
                        		initHit[0] = aiCol;
                                }
                            }
                        }
                    }
                    else if (prevMedTurn[0] < initHit[0]) { //last turn was south of initHit
                        if (board_1.checkBoard(prevMedTurn[0], prevMedTurn[1])) { //if last turn was a hit
                            //try to attack south of initHit
                            dist = 1;
                            while (initHit[0] - dist >= 1) {//while there is a space on the board dist spaces south of initHit
                                if (hitmiss_2[9-(initHit[0]-dist)][initHit[1]] == 'M') {//if the ai has already missed in the tile dist spaces south of initHit
                                    //exit loop, try west next
                                    break;
                                }
                                else if (hitmiss_2[9-(initHit[0]-dist)][initHit[1]] == 'H') {//if the tile dist spaces south of initHit has already been hit (could be part of the same ship)
                                    dist++;
                                }
                                else {//if the tile dist spaces south of initHit has not been attacked
                                    //attack dist spaces south of initHit
                                    aiRow = initHit[0] - dist;
                                    aiCol = initHit[1];
                                    break;
                                }
                            }	
                            if (initHit[0] + dist < 1 || hitmiss_2[9-(initHit[0] - dist)][initHit[1]] == 'M') {//if attacking south failed
                                //try to attack west of initHit
                                dist = 1;
                                while (initHit[1] - dist >= 0) {//while there is a space on the board dist spaces west of initHit
                                    if (hitmiss_2[9-initHit[0]][initHit[1] - dist] == 'M') {//if the ai has already missed in the tile dist spaces west of initHit
                                        //exit loop, try south next
                                        break;
                                    }
                                    else if (hitmiss_2[9-initHit[0]][initHit[1] - dist] == 'H') {//if the tile dist spaces west of initHit has already been hit (could be part of the same ship)
                                        dist++;
                                    }
                                    else {//if the tile dist spaces west of initHit has not been attacked
                                        //attack dist spaces west of initHit
                                        aiRow = initHit[0];
                                        aiCol = initHit[1] - dist;
                                        break;
                                    }
                                }	
                            }
                            if (initHit[1] - dist < 0 || hitmiss_2[9-initHit[0]][initHit[1] - dist] == 'M') {//if attacking west failed
                                //this shouldn't really be possible but i'll just try to attack a random spot and reset initHit if it happens somehow
                                //randomize a coordinate until it gets a spot that hasnt been attacked
                            	initHit[0] = 11;
                            	initHit[1] = 11;

                                do {
                                    aiRow = aiRandomRow();
                                    aiCol = aiRandomCol();
                                } while(hitmiss_2[9-aiRow][aiCol] == 'H' || hitmiss_2[9-aiRow][aiCol] == 'M');
                            
                                if (board_1.checkBoard(aiRow, aiCol) && hitmiss_2[9-aiRow][aiCol] != 'H') {//im assuming we're just gonna use board_2 and hitmiss_2 for the ai
                        		initHit[0] = aiRow;
                        		initHit[0] = aiCol;
                                }
                            }
                        }
                        else { //there is nothing directly south of initHit
                            //try to attack west of initHit
                            dist = 1;
                            while (initHit[1] - dist >= 0) {//while there is a space on the board dist spaces west of initHit
                                if (hitmiss_2[9-initHit[0]][initHit[1] - dist] == 'M') {//if the ai has already missed in the tile dist spaces west of initHit
                                    //exit loop, try south next
                                    break;
                                }
                                else if (hitmiss_2[9-initHit[0]][initHit[1] - dist] == 'H') {//if the tile dist spaces west of initHit has already been hit (could be part of the same ship)
                                    dist++;
                                }
                                else {//if the tile dist spaces west of initHit has not been attacked
                                    //attack dist spaces west of initHit
                                    aiRow = initHit[0];
                                    aiCol = initHit[1] - dist;
                                    break;
                                }
                            }	
                            if (initHit[1] - dist < 0 || hitmiss_2[9-initHit[0]][initHit[1] - dist] == 'M') {//if attacking west failed
                                //this shouldn't really be possible but i'll just try to attack a random spot and reset initHit if it happens somehow
                                //randomize a coordinate until it gets a spot that hasnt been attacked
                            	initHit[0] = 11;
                            	initHit[1] = 11;

                                do {
                                    aiRow = aiRandomRow();
                                    aiCol = aiRandomCol();
                                } while(hitmiss_2[9-aiRow][aiCol] == 'H' || hitmiss_2[9-aiRow][aiCol] == 'M');
                            
                                if (board_1.checkBoard(aiRow, aiCol) && hitmiss_2[9-aiRow][aiCol] != 'H') {//im assuming we're just gonna use board_2 and hitmiss_2 for the ai
                        		initHit[0] = aiRow;
                        		initHit[0] = aiCol;
                                }
                            }
                        }
                    }
                    else if (prevMedTurn[1] < initHit[1]) { //last turn was west of initHit
                        if (board_1.checkBoard(prevMedTurn[0], prevMedTurn[1])) { //if last turn was a hit
                            //try to attack west of initHit
                            dist = 1;
                            while (initHit[1] - dist >= 0) {//while there is a space on the board dist spaces west of initHit
                                if (hitmiss_2[9-initHit[0]][initHit[1] - dist] == 'M') {//if the ai has already missed in the tile dist spaces west of initHit
                                    //exit loop, try south next
                                    break;
                                }
                                else if (hitmiss_2[9-initHit[0]][initHit[1] - dist] == 'H') {//if the tile dist spaces west of initHit has already been hit (could be part of the same ship)
                                    dist++;
                                }
                                else {//if the tile dist spaces west of initHit has not been attacked
                                    //attack dist spaces west of initHit
                                    aiRow = initHit[0];
                                    aiCol = initHit[1] - dist;
                                    break;
                                }
                            }	
                            if (initHit[1] - dist < 0 || hitmiss_2[9-initHit[0]][initHit[1] - dist] == 'M') {//if attacking west failed
                                //this shouldn't really be possible but i'll just try to attack a random spot and reset initHit if it happens somehow
                                //randomize a coordinate until it gets a spot that hasnt been attacked
                            	initHit[0] = 11;
                            	initHit[1] = 11;

                                do {
                                    aiRow = aiRandomRow();
                                    aiCol = aiRandomCol();
                                } while(hitmiss_2[9-aiRow][aiCol] == 'H' || hitmiss_2[9-aiRow][aiCol] == 'M');
                            
                                if (board_1.checkBoard(aiRow, aiCol) && hitmiss_2[9-aiRow][aiCol] != 'H') {//im assuming we're just gonna use board_2 and hitmiss_2 for the ai
                        		initHit[0] = aiRow;
                        		initHit[0] = aiCol;
                                }
                            }
                        }
                        else {//checking every direction did not result in a sunk ship
                            //this shouldn't really be possible but i'll just try to attack a random spot and reset initHit if it happens somehow
                            //randomize a coordinate until it gets a spot that hasnt been attacked
                            initHit[0] = 11;
			    initHit[1] = 11;
                            do {
                                aiRow = aiRandomRow();
                                aiCol = aiRandomCol();
                            } while(hitmiss_2[9-aiRow][aiCol] == 'H' || hitmiss_2[9-aiRow][aiCol] == 'M');
                        
                            if (board_1.checkBoard(aiRow, aiCol) && hitmiss_2[9-aiRow][aiCol] != 'H') {//im assuming we're just gonna use board_2 and hitmiss_2 for the ai
                        		initHit[0] = aiRow;
                        		initHit[0] = aiCol;
                            }
                        }
                    }
                }
                
                //now actually tell the player what happened and edit the arrays
                //I copied Jason's code for this, EXCEPT FOR THE PART WITH THE CAPS COMMENT ABOVE IT
                //doesn't really need to be in a different piece of code for each difficulty so whoever's doing the integration can get rid of this
                if(board_1.checkBoard(aiRow,aiCol) == true && hitmiss_2[9-aiRow][aiCol] != 'H')
                {
			tempSize = board_1.board[9-aiRow][aiCol];
                        hitmiss_2[9-aiRow][aiCol] = 'H';
                        board_1.board[9-aiRow][aiCol] = 'H';
                        hitcount2++;
                        cout << "The AI hit a ship!";
			
			//NEED THIS FOR MEDIUM AI
			if (board_1.checkSunk(tempSize)) {
				initHit[0] = 11;
				initHit[1] = 11;
			}
			
                        if(winningCondition(numShips) == hitcount2) {
                        //cout << "Congratulations the AI won!\n";
			Playp2win(100, 1);
                        return;
                        }
                }
                else if(hitmiss_2[9-aiRow][aiCol] == 'H' || hitmiss_2[9-aiRow][aiCol] == 'M') {
                        cout << "The AI shot at the same spot again.\n";
                }
                else {
                        cout << "The AI missed their shot.\n";
                        hitmiss_2[9-aiRow][aiCol] = 'M';
                    board_1.board[9-aiRow][aiCol] = 'M';
                }
            
            }
            else 
            {
                bool changed = 0;
                for(int i=0; i<9; i++)
                {
                    for(int j=0; j<10; j++)
                    {
                        if(board_1.checkBoard(9-i, j))
                        {
                            cout << "The AI hit your ship!\n";
                            board_1.board[i][j] = 'H';
			    hitmiss_2[i][j] = 'H';
                            changed = 1;
                            hitcount2++;
                            break;
                        }
                    }
                    if(changed==1)
                    {
                        break;
                    }
                }
                if(changed == 0) {
                    cout << "The AI missed!\n";
                    //miss
                }
                else
                {
                    changed = 0;
                }
            }
            
            if(winningCondition(numShips) == hitcount2)
            {
                //cout << "Congratulations the robot wins!\n";
		Playp2win(100, 1);
                return;
            }
        }
    if(currentPlayer !=3 )
    {
        std::cin.ignore(1024,'\n');
    }
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
    if(aiChosen == 1)
    {
        if(currentPlayer == 1){
            currentPlayer = 3;
        }
        else {
            currentPlayer = 1;
        }
    }
    else
    {
        if(currentPlayer == 1){
            currentPlayer = 2;
        }
        else {
            currentPlayer = 1;
        }
        std::cout << "\x1B[2J\x1B[H";
    }
}

bool Executive::hardMove(Board board1)
{
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<10; j++)
        {
            if(board1.board[i][j] == 'S')
            {
                cout << "Changed!\n";
                return true;
            }
        }
    }
    return false;
}

//Decide based on the logic whether it was a hit or not and return true if it is a hit
bool Executive::mediumMove(Board board1)
{
    return true;
}

//Decide based on the logic whether it was a hit or not and return true if it is a hit
bool Executive::easyMove(Board board1)
{
    return true;
}

int Executive::aiRandomRow() {
  srand((unsigned) time(0));
  return((rand() % 9)+1);
}

int Executive::aiRandomCol() {
  srand((unsigned) time(0));
  return(rand() % 10);
}

void Executive::Printframe(char board[9][10], int milliSec) {
    cout << "\x1B[2J\x1B[H";
    
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
    usleep(1000*milliSec); 
}

void Executive::Playmiss(int msPerFrame){
    char frame1[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame2[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', }};
    char frame3[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', }};
    char frame4[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', }};
    char frame5[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', }};
    char frame6[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '.', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '@', }};
    char frame7[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '.', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', }};
    char frame8[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '.', '@', '.', },{'@', '@', '@', '@', '@', '.', '@', '.', '@', '.', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', }};
    char frame9[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '.', '@', '.', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '.', '@', '.', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', }};
    char frame10[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '.', '@', '.', '@', '.', '@', '.', },{'@', '@', '@', '.', '@', '.', '@', '.', '@', '.', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame11[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '.', '@', '.', '@', '.', '@', '.', '@', },{'@', '@', '.', '@', '.', '@', '.', '@', '.', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '.', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame12[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '.', '@', '.', '@', '.', '@', '.', '@', '@', },{'@', '.', '@', '.', '@', '.', '@', '.', '@', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', }};
    char frame13[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '@', },{'.', '@', '.', '@', '.', '@', '.', '@', '@', '@', },{'.', '@', '.', '@', '.', '@', '.', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', }};
    char frame14[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'.', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'@', '.', '@', '.', '@', '.', '@', '@', '@', '@', },{'@', '.', '@', '.', '@', '.', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '.', }};
    char frame15[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '.', '.', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'.', '@', '.', '@', '.', '@', '@', '@', '@', '@', },{'.', '@', '.', '@', '.', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '.', '.', }};
    char frame16[9][10]={{'@', '@', '@', '@', '@', '@', '@', '.', '.', '.', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '.', },{'@', '.', '@', '.', '@', '@', '@', '@', '@', '.', },{'@', '.', '@', '.', '@', '@', '@', '@', '@', '.', },{'.', '@', '@', '@', '.', '@', '@', '@', '@', '.', },{'.', '@', '@', '@', '.', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '.', '@', '.', '.', '.', }};
    char frame17[9][10]={{'@', '@', '@', '@', '@', '@', '.', '.', '.', '.', },{'@', '.', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '.', '@', },{'.', '@', '.', '@', '@', '@', '@', '@', '.', '@', },{'.', '@', '.', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '.', '.', '.', '.', }};
    char frame18[9][10]={{'@', '@', '@', '@', '@', '.', '.', '.', '.', '.', },{'.', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '.', '.', '.', '.', '.', }};
    char frame19[9][10]={{'@', '@', '@', '@', '.', '.', '.', '.', '.', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '.', '.', '.', '.', '.', '@', }};
    char frame20[9][10]={{'@', '@', '@', '.', '.', '.', '.', '.', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '.', '@', '.', '.', '.', '.', '.', '@', '@', }};
    char frame21[9][10]={{'@', '@', '.', '.', '.', '.', '.', '@', '@', '.', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'.', '@', '.', '.', '.', '.', '.', '@', '@', '.', }};
    char frame22[9][10]={{'@', '.', '.', '.', '.', '.', '@', '@', '.', '.', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '.', '.', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '.', '.', '.', '.', '.', '@', '@', '.', '.', }};
    char frame23[9][10]={{'.', '.', '.', '.', '.', '@', '@', '.', '.', '.', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '.', '.', '.', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'.', '.', '.', '.', '.', '@', '@', '.', '.', '.', }};
    char frame24[9][10]={{'.', '.', '.', '.', '@', '@', '.', '.', '.', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '.', '.', '.', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '.', },{'.', '.', '.', '.', '@', '@', '.', '.', '.', '@', }};
    char frame25[9][10]={{'.', '.', '.', '@', '@', '.', '.', '.', '@', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '.', '.', '.', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'.', '.', '.', '@', '@', '.', '.', '.', '@', '@', }};
    char frame26[9][10]={{'.', '.', '@', '@', '.', '.', '.', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '.', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '.', '.', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '.', },{'.', '.', '@', '@', '.', '.', '.', '@', '@', '@', }};
    char frame27[9][10]={{'.', '@', '@', '.', '.', '.', '@', '@', '@', '.', },{'@', '@', '.', '@', '@', '@', '.', '@', '.', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '.', '.', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '.', '@', },{'.', '@', '@', '.', '.', '.', '@', '@', '@', '.', }};
    char frame28[9][10]={{'@', '@', '.', '.', '.', '@', '@', '@', '.', '.', },{'@', '.', '@', '@', '@', '.', '@', '.', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '.', '.', '.', '@', '@', '@', '.', '.', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '.', '@', '@', },{'@', '@', '.', '.', '.', '@', '@', '@', '.', '.', }};
    char frame29[9][10]={{'@', '.', '.', '.', '@', '@', '@', '.', '.', '.', },{'.', '@', '@', '@', '.', '@', '.', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '.', '.', '.', '@', '@', '@', '.', '.', '.', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '.', '@', '.', '@', '@', '@', },{'@', '.', '.', '.', '@', '@', '@', '.', '.', '.', }};
    char frame30[9][10]={{'.', '.', '.', '@', '@', '@', '.', '.', '.', '@', },{'@', '@', '@', '.', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'.', '.', '.', '@', '@', '@', '.', '.', '.', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '.', '@', '.', '@', '@', '@', '.', },{'.', '.', '.', '@', '@', '@', '.', '.', '.', '@', }};
    char frame31[9][10]={{'.', '.', '@', '@', '@', '.', '.', '.', '@', '@', },{'@', '@', '.', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'.', '.', '@', '@', '@', '.', '.', '.', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '.', '@', '.', '@', '@', '@', '.', '@', },{'.', '.', '@', '@', '@', '.', '.', '.', '@', '@', }};
    char frame32[9][10]={{'.', '@', '@', '@', '.', '.', '.', '@', '@', '@', },{'@', '.', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '.', '.', '.', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '.', '@', '.', '@', '@', '@', '.', '@', '@', },{'.', '@', '@', '@', '.', '.', '.', '@', '@', '@', }};
    char frame33[9][10]={{'@', '@', '@', '.', '.', '.', '@', '@', '@', '@', },{'.', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '.', '.', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'.', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '.', '.', '.', '@', '@', '@', '@', }};
    char frame34[9][10]={{'@', '@', '.', '.', '.', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '.', '.', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '@', '.', '.', '.', '@', '@', '@', '@', '@', }};
    char frame35[9][10]={{'@', '.', '.', '.', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '.', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'@', '.', '.', '.', '@', '@', '@', '@', '@', '@', }};
    char frame36[9][10]={{'.', '.', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '.', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'.', '.', '.', '@', '@', '@', '@', '@', '@', '@', }};
    char frame37[9][10]={{'.', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'.', '.', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame38[9][10]={{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame39[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame40[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', }};

    Printframe(frame1,msPerFrame);
    Printframe(frame2,msPerFrame);
    Printframe(frame3,msPerFrame);
    Printframe(frame4,msPerFrame);
    Printframe(frame5,msPerFrame);
    Printframe(frame6,msPerFrame);
    Printframe(frame7,msPerFrame);
    Printframe(frame8,msPerFrame);
    Printframe(frame9,msPerFrame);
    Printframe(frame10,msPerFrame);
    Printframe(frame11,msPerFrame);
    Printframe(frame12,msPerFrame);
    Printframe(frame13,msPerFrame);
    Printframe(frame14,msPerFrame);
    Printframe(frame15,msPerFrame);
    Printframe(frame16,msPerFrame);
    Printframe(frame17,msPerFrame);
    Printframe(frame18,msPerFrame);
    Printframe(frame19,msPerFrame);
    Printframe(frame20,msPerFrame);
    Printframe(frame21,msPerFrame);
    Printframe(frame22,msPerFrame);
    Printframe(frame23,msPerFrame);
    Printframe(frame24,msPerFrame);
    Printframe(frame25,msPerFrame);
    Printframe(frame26,msPerFrame);
    Printframe(frame27,msPerFrame);
    Printframe(frame28,msPerFrame);
    Printframe(frame29,msPerFrame);
    Printframe(frame30,msPerFrame);
    Printframe(frame31,msPerFrame);
    Printframe(frame32,msPerFrame);
    Printframe(frame33,msPerFrame);
    Printframe(frame34,msPerFrame);
    Printframe(frame35,msPerFrame);
    Printframe(frame36,msPerFrame);
    Printframe(frame37,msPerFrame);
    Printframe(frame38,msPerFrame);
    Printframe(frame39,msPerFrame);
    Printframe(frame40,msPerFrame);
    
}

void Executive::Playhit(int msPerFrame){
    char frame1[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame2[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', }};
    char frame3[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', }};
    char frame4[9][10]={{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '.', '.', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', }};
    char frame5[9][10]={{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '.', '.', '.', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', }};
    char frame6[9][10]={{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '.', '.', '.', '.', '.', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', }};
    char frame7[9][10]={{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '.', '.', '.', '.', '.', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', }};
    char frame8[9][10]={{'@', '@', '@', '.', '@', '@', '@', '.', '@', '.', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '.', '.', '.', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '.', }};
    char frame9[9][10]={{'@', '@', '.', '@', '@', '@', '.', '@', '.', '.', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '.', '.', '.', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '.', '.', }};
    char frame10[9][10]={{'@', '.', '@', '@', '@', '.', '@', '.', '.', '.', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '.', '.', '.', '.', '.', '@', '@', '@', '.', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '.', '@', '@', '@', '.', '@', '.', '.', '.', }};
    char frame11[9][10]={{'.', '@', '@', '@', '.', '@', '.', '.', '.', '.', },{'.', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'.', '.', '.', '.', '.', '@', '@', '@', '.', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'.', '@', '@', '@', '.', '@', '.', '.', '.', '.', }};
    char frame12[9][10]={{'@', '@', '@', '.', '@', '.', '.', '.', '.', '.', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'.', '.', '.', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '.', '.', '.', '.', '.', }};
    char frame13[9][10]={{'@', '@', '.', '@', '.', '.', '.', '.', '.', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'.', '.', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '.', '.', '.', '.', '.', '@', }};
    char frame14[9][10]={{'@', '.', '@', '.', '.', '.', '.', '.', '@', '.', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '@', },{'.', '.', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '.', '@', '.', '.', '.', '.', '.', '@', '@', }};
    char frame15[9][10]={{'.', '@', '.', '.', '.', '.', '.', '@', '.', '.', },{'.', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'.', '@', '.', '.', '.', '.', '.', '@', '@', '@', }};
    char frame16[9][10]={{'@', '.', '.', '.', '.', '.', '@', '.', '.', '.', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '.', },{'@', '.', '.', '.', '.', '.', '@', '@', '@', '.', }};
    char frame17[9][10]={{'.', '.', '.', '.', '.', '@', '.', '.', '.', '.', },{'@', '@', '.', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '.', '@', },{'.', '.', '.', '.', '.', '@', '@', '@', '.', '@', }};
    char frame18[9][10]={{'.', '.', '.', '.', '@', '.', '.', '.', '.', '.', },{'@', '.', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '.', '@', '@', },{'.', '.', '.', '.', '@', '@', '@', '.', '@', '@', }};
    char frame19[9][10]={{'.', '.', '.', '@', '.', '.', '.', '.', '.', '@', },{'.', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'.', '.', '.', '@', '@', '@', '.', '@', '@', '@', }};
    char frame20[9][10]={{'.', '.', '@', '.', '.', '.', '.', '.', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'.', '.', '@', '@', '@', '.', '@', '@', '@', '@', }};
    char frame21[9][10]={{'.', '@', '.', '.', '.', '.', '.', '@', '@', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '@', '@', }};
    char frame22[9][10]={{'@', '.', '.', '.', '.', '.', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', }};
    char frame23[9][10]={{'.', '.', '.', '.', '.', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', }};
    char frame24[9][10]={{'.', '.', '.', '.', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame25[9][10]={{'.', '.', '.', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame26[9][10]={{'.', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame27[9][10]={{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame28[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', }};
    
    Printframe(frame1,msPerFrame);
    Printframe(frame2,msPerFrame);
    Printframe(frame3,msPerFrame);
    Printframe(frame4,msPerFrame);
    Printframe(frame5,msPerFrame);
    Printframe(frame6,msPerFrame);
    Printframe(frame7,msPerFrame);
    Printframe(frame8,msPerFrame);
    Printframe(frame9,msPerFrame);
    Printframe(frame10,msPerFrame);
    Printframe(frame11,msPerFrame);
    Printframe(frame12,msPerFrame);
    Printframe(frame13,msPerFrame);
    Printframe(frame14,msPerFrame);
    Printframe(frame15,msPerFrame);
    Printframe(frame16,msPerFrame);
    Printframe(frame17,msPerFrame);
    Printframe(frame18,msPerFrame);
    Printframe(frame19,msPerFrame);
    Printframe(frame20,msPerFrame);
    Printframe(frame21,msPerFrame);
    Printframe(frame22,msPerFrame);
    Printframe(frame23,msPerFrame);
    Printframe(frame24,msPerFrame);
    Printframe(frame25,msPerFrame);
    Printframe(frame26,msPerFrame);
    Printframe(frame27,msPerFrame);
    Printframe(frame28,msPerFrame);
    
    
}

void Executive::Playp1win(int msPerFrame, int loops){
    char frame1[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame2[9][10]={{'1', '1', '@', '@', '@', '@', '@', '1', '1', '1', },{'1', '1', '@', '@', '@', '@', '@', '@', '1', '1', },{'1', '1', '@', '@', '1', '1', '@', '@', '1', '1', },{'1', '1', '@', '@', '1', '1', '@', '@', '1', '1', },{'1', '1', '@', '@', '@', '@', '@', '@', '1', '1', },{'1', '1', '@', '@', '@', '@', '@', '1', '1', '1', },{'1', '1', '@', '@', '1', '1', '1', '1', '1', '1', },{'1', '1', '@', '@', '1', '1', '1', '1', '1', '1', },{'1', '1', '@', '@', '1', '1', '1', '1', '1', '1', }};
    char frame3[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame4[9][10]={{'1', '1', '1', '1', '@', '@', '1', '1', '1', '1', },{'1', '1', '1', '@', '@', '@', '1', '1', '1', '1', },{'1', '1', '1', '@', '@', '@', '1', '1', '1', '1', },{'1', '1', '1', '1', '@', '@', '1', '1', '1', '1', },{'1', '1', '1', '1', '@', '@', '1', '1', '1', '1', },{'1', '1', '1', '1', '@', '@', '1', '1', '1', '1', },{'1', '1', '1', '1', '@', '@', '1', '1', '1', '1', },{'1', '1', '@', '@', '@', '@', '@', '@', '1', '1', },{'1', '1', '@', '@', '@', '@', '@', '@', '1', '1', }};
    char frame5[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame6[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame7[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame8[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame9[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', }};
    char frame10[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', }};
    char frame11[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '.', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', }};
    char frame12[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '.', '@', '.', '@', '.', },{'@', '@', '@', '@', '@', '.', '@', '.', '@', '.', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', }};
    char frame13[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '.', '@', '.', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '.', '@', '.', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', }};
    char frame14[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '.', '@', '.', '@', '.', '@', '.', },{'@', '@', '@', '.', '@', '.', '@', '.', '@', '.', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', }};
    char frame15[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '.', '@', '.', '@', '.', '@', '.', '@', },{'@', '@', '.', '@', '.', '@', '.', '@', '.', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', }};
    char frame16[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'.', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '.', '@', '.', '@', '.', '@', '.', '@', '@', },{'@', '.', '@', '.', '@', '.', '@', '.', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', }};
    char frame17[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'.', '@', '.', '@', '.', '@', '.', '@', '@', '@', },{'.', '@', '.', '@', '.', '@', '.', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '@', }};
    char frame18[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '.', '@', '.', '@', '.', '@', '@', '@', '@', },{'@', '.', '@', '.', '@', '.', '@', '@', '@', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '@', '.', }};
    char frame19[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '.', '.', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '@', },{'.', '@', '.', '@', '.', '@', '@', '@', '@', '@', },{'.', '@', '.', '@', '.', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '.', '.', }};
    char frame20[9][10]={{'@', '@', '@', '@', '@', '@', '@', '.', '.', '.', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'.', '@', '@', '@', '.', '@', '@', '@', '@', '.', },{'.', '@', '@', '@', '.', '@', '@', '@', '@', '.', },{'@', '.', '@', '.', '@', '@', '@', '@', '@', '.', },{'@', '.', '@', '.', '@', '@', '@', '@', '@', '.', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '.', '@', '@', '@', '@', '.', '.', '.', }};
    char frame21[9][10]={{'@', '@', '@', '@', '@', '@', '.', '.', '.', '.', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '.', '@', },{'.', '@', '.', '@', '@', '@', '@', '@', '.', '@', },{'.', '@', '.', '@', '@', '@', '@', '@', '.', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '.', '@', '@', '@', '@', '.', '.', '.', '.', }};
    char frame22[9][10]={{'@', '@', '@', '@', '@', '.', '.', '.', '.', '.', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '.', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '.', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'.', '@', '@', '@', '@', '.', '.', '.', '.', '.', }};
    char frame23[9][10]={{'@', '@', '@', '@', '.', '.', '.', '.', '.', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '.', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '.', '.', '.', '.', '.', '@', }};
    char frame24[9][10]={{'@', '@', '@', '.', '.', '.', '.', '.', '@', '.', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '.', },{'.', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'.', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '.', '.', '.', '.', '.', '@', '.', }};
    char frame25[9][10]={{'@', '@', '.', '.', '.', '.', '.', '@', '.', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '.', '.', },{'.', '@', '@', '@', '.', '@', '@', '@', '.', '.', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '.', '.', '.', '.', '.', '@', '.', '@', }};
    char frame26[9][10]={{'@', '.', '.', '.', '.', '.', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '.', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '.', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '.', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '.', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '.', '.', '.', '.', '.', '@', '.', '@', '@', }};
    char frame27[9][10]={{'.', '.', '.', '.', '.', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '.', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '.', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '.', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '.', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '.', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '.', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'.', '.', '.', '.', '.', '@', '.', '@', '@', '@', }};
    char frame28[9][10]={{'.', '.', '.', '.', '@', '.', '@', '@', '@', '.', },{'@', '.', '@', '@', '@', '.', '.', '@', '@', '.', },{'@', '.', '@', '@', '@', '.', '.', '@', '@', '.', },{'@', '.', '@', '@', '@', '.', '@', '.', '@', '.', },{'@', '.', '@', '@', '@', '.', '@', '.', '@', '.', },{'@', '.', '@', '@', '@', '.', '@', '@', '.', '.', },{'@', '.', '@', '@', '@', '.', '@', '@', '.', '.', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '.', },{'.', '.', '.', '.', '@', '.', '@', '@', '@', '.', }};
    char frame29[9][10]={{'.', '.', '.', '@', '.', '@', '@', '@', '.', '@', },{'.', '@', '@', '@', '.', '.', '@', '@', '.', '@', },{'.', '@', '@', '@', '.', '.', '@', '@', '.', '@', },{'.', '@', '@', '@', '.', '@', '.', '@', '.', '@', },{'.', '@', '@', '@', '.', '@', '.', '@', '.', '@', },{'.', '@', '@', '@', '.', '@', '@', '.', '.', '@', },{'.', '@', '@', '@', '.', '@', '@', '.', '.', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'.', '.', '.', '@', '.', '@', '@', '@', '.', '@', }};
    char frame30[9][10]={{'.', '.', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '.', '@', '@', '.', '@', '.', },{'@', '@', '@', '.', '.', '@', '@', '.', '@', '.', },{'@', '@', '@', '.', '@', '.', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '.', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '.', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '.', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '.', },{'.', '.', '@', '.', '@', '@', '@', '.', '@', '@', }};
    char frame31[9][10]={{'.', '@', '.', '@', '@', '@', '.', '@', '@', '.', },{'@', '@', '.', '.', '@', '@', '.', '@', '.', '@', },{'@', '@', '.', '.', '@', '@', '.', '@', '.', '@', },{'@', '@', '.', '@', '.', '@', '.', '@', '@', '.', },{'@', '@', '.', '@', '.', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '.', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '.', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '.', '@', },{'.', '@', '.', '@', '@', '@', '.', '@', '@', '.', }};
    char frame32[9][10]={{'@', '.', '@', '@', '@', '.', '@', '@', '.', '.', },{'@', '.', '.', '@', '@', '.', '@', '.', '@', '@', },{'@', '.', '.', '@', '@', '.', '@', '.', '@', '@', },{'@', '.', '@', '.', '@', '.', '@', '@', '.', '.', },{'@', '.', '@', '.', '@', '.', '@', '@', '@', '@', },{'@', '.', '@', '@', '.', '.', '@', '@', '@', '@', },{'@', '.', '@', '@', '.', '.', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '.', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '.', '.', }};
    char frame33[9][10]={{'.', '@', '@', '@', '.', '@', '@', '.', '.', '.', },{'.', '.', '@', '@', '.', '@', '.', '@', '@', '@', },{'.', '.', '@', '@', '.', '@', '.', '@', '@', '@', },{'.', '@', '.', '@', '.', '@', '@', '.', '.', '.', },{'.', '@', '.', '@', '.', '@', '@', '@', '@', '@', },{'.', '@', '@', '.', '.', '@', '@', '@', '@', '@', },{'.', '@', '@', '.', '.', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '.', '@', '.', '@', '@', '@', },{'.', '@', '@', '@', '.', '@', '@', '.', '.', '.', }};
    char frame34[9][10]={{'@', '@', '@', '.', '@', '@', '.', '.', '.', '@', },{'.', '@', '@', '.', '@', '.', '@', '@', '@', '.', },{'.', '@', '@', '.', '@', '.', '@', '@', '@', '@', },{'@', '.', '@', '.', '@', '@', '.', '.', '.', '@', },{'@', '.', '@', '.', '@', '@', '@', '@', '@', '.', },{'@', '@', '.', '.', '@', '@', '@', '@', '@', '.', },{'@', '@', '.', '.', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '.', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '.', '@', '@', '.', '.', '.', '@', }};
    char frame35[9][10]={{'@', '@', '.', '@', '@', '.', '.', '.', '@', '@', },{'@', '@', '.', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '.', '@', '.', '@', '@', '@', '@', '@', },{'.', '@', '.', '@', '@', '.', '.', '.', '@', '@', },{'.', '@', '.', '@', '@', '@', '@', '@', '.', '@', },{'@', '.', '.', '@', '@', '@', '@', '@', '.', '@', },{'@', '.', '.', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '.', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '.', '@', '@', '.', '.', '.', '@', '@', }};
    char frame36[9][10]={{'@', '.', '@', '@', '.', '.', '.', '@', '@', '@', },{'@', '.', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '.', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '.', '.', '.', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '.', '@', '@', },{'.', '.', '@', '@', '@', '@', '@', '.', '@', '@', },{'.', '.', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '.', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '.', '@', '@', '.', '.', '.', '@', '@', '@', }};
    char frame37[9][10]={{'.', '@', '@', '.', '.', '.', '@', '@', '@', '@', },{'.', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'.', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '.', '.', '.', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'.', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'.', '@', '@', '.', '.', '.', '@', '@', '@', '@', }};
    char frame38[9][10]={{'@', '@', '.', '.', '.', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '.', '.', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '@', '.', '.', '.', '@', '@', '@', '@', '@', }};
    char frame39[9][10]={{'@', '.', '.', '.', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '.', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'@', '.', '.', '.', '@', '@', '@', '@', '@', '@', }};
    char frame40[9][10]={{'.', '.', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '.', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'.', '.', '.', '@', '@', '@', '@', '@', '@', '@', }};
    char frame41[9][10]={{'.', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'.', '.', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame42[9][10]={{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame43[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame44[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', }};

    for(int i=0; i<loops; i++){
        Printframe(frame1,(msPerFrame*4));	
        Printframe(frame2,(msPerFrame*12));	
        Printframe(frame3,(msPerFrame*4));	
        Printframe(frame4,(msPerFrame*12));	
        Printframe(frame5,(msPerFrame*4));	
        Printframe(frame6,msPerFrame);	
        Printframe(frame7,msPerFrame);	
        Printframe(frame8,msPerFrame);	
        Printframe(frame9,msPerFrame);	
        Printframe(frame10,msPerFrame);	
        Printframe(frame11,msPerFrame);	
        Printframe(frame12,msPerFrame);	
        Printframe(frame13,msPerFrame);	
        Printframe(frame14,msPerFrame);	
        Printframe(frame15,msPerFrame);	
        Printframe(frame16,msPerFrame);	
        Printframe(frame17,msPerFrame);	
        Printframe(frame18,msPerFrame);	
        Printframe(frame19,msPerFrame);	
        Printframe(frame20,msPerFrame);	
        Printframe(frame21,msPerFrame);	
        Printframe(frame22,msPerFrame);	
        Printframe(frame23,msPerFrame);	
        Printframe(frame24,msPerFrame);	
        Printframe(frame25,msPerFrame);	
        Printframe(frame26,msPerFrame);	
        Printframe(frame27,msPerFrame);	
        Printframe(frame28,msPerFrame);	
        Printframe(frame29,msPerFrame);	
        Printframe(frame30,msPerFrame);	
        Printframe(frame31,msPerFrame);	
        Printframe(frame32,msPerFrame);	
        Printframe(frame33,msPerFrame);	
        Printframe(frame34,msPerFrame);	
        Printframe(frame35,msPerFrame);	
        Printframe(frame36,msPerFrame);	
        Printframe(frame37,msPerFrame);	
        Printframe(frame38,msPerFrame);	
        Printframe(frame39,msPerFrame);	
        Printframe(frame40,msPerFrame);	
        Printframe(frame41,msPerFrame);	
        Printframe(frame42,msPerFrame);	
        Printframe(frame43,msPerFrame);	
        Printframe(frame44,msPerFrame);	
    }
    
}

void Executive::Playp2win(int msPerFrame, int loops){
    char frame1[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame2[9][10]={{'2', '2', '@', '@', '@', '@', '@', '2', '2', '2', },{'2', '2', '@', '@', '@', '@', '@', '@', '2', '2', },{'2', '2', '@', '@', '2', '2', '@', '@', '2', '2', },{'2', '2', '@', '@', '2', '2', '@', '@', '2', '2', },{'2', '2', '@', '@', '@', '@', '@', '@', '2', '2', },{'2', '2', '@', '@', '@', '@', '@', '2', '2', '2', },{'2', '2', '@', '@', '2', '2', '2', '2', '2', '2', },{'2', '2', '@', '@', '2', '2', '2', '2', '2', '2', },{'2', '2', '@', '@', '2', '2', '2', '2', '2', '2', }};
    char frame3[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame4[9][10]={{'2', '2', '2', '@', '@', '@', '@', '2', '2', '2', },{'2', '2', '@', '@', '@', '@', '@', '@', '2', '2', },{'2', '2', '@', '@', '2', '2', '@', '@', '2', '2', },{'2', '2', '2', '2', '2', '@', '@', '@', '2', '2', },{'2', '2', '2', '2', '@', '@', '@', '2', '2', '2', },{'2', '2', '2', '@', '@', '@', '2', '2', '2', '2', },{'2', '2', '@', '@', '@', '2', '2', '2', '2', '2', },{'1', '1', '@', '@', '@', '@', '@', '@', '1', '1', },{'1', '1', '@', '@', '@', '@', '@', '@', '1', '1', }};
    char frame5[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame6[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame7[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame8[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame9[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', }};
    char frame10[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', }};
    char frame11[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '.', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', }};
    char frame12[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '.', '@', '.', '@', '.', },{'@', '@', '@', '@', '@', '.', '@', '.', '@', '.', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', }};
    char frame13[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '.', '@', '.', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '.', '@', '.', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', }};
    char frame14[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '.', '@', '.', '@', '.', '@', '.', },{'@', '@', '@', '.', '@', '.', '@', '.', '@', '.', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', }};
    char frame15[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '.', '@', '.', '@', '.', '@', '.', '@', },{'@', '@', '.', '@', '.', '@', '.', '@', '.', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', }};
    char frame16[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'.', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '.', '@', '.', '@', '.', '@', '.', '@', '@', },{'@', '.', '@', '.', '@', '.', '@', '.', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', }};
    char frame17[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'.', '@', '.', '@', '.', '@', '.', '@', '@', '@', },{'.', '@', '.', '@', '.', '@', '.', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '@', }};
    char frame18[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '.', '@', '.', '@', '.', '@', '@', '@', '@', },{'@', '.', '@', '.', '@', '.', '@', '@', '@', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '@', '.', }};
    char frame19[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '.', '.', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '@', },{'.', '@', '.', '@', '.', '@', '@', '@', '@', '@', },{'.', '@', '.', '@', '.', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '.', '.', }};
    char frame20[9][10]={{'@', '@', '@', '@', '@', '@', '@', '.', '.', '.', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'.', '@', '@', '@', '.', '@', '@', '@', '@', '.', },{'.', '@', '@', '@', '.', '@', '@', '@', '@', '.', },{'@', '.', '@', '.', '@', '@', '@', '@', '@', '.', },{'@', '.', '@', '.', '@', '@', '@', '@', '@', '.', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '.', },{'@', '@', '.', '@', '@', '@', '@', '.', '.', '.', }};
    char frame21[9][10]={{'@', '@', '@', '@', '@', '@', '.', '.', '.', '.', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '.', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '.', '@', },{'.', '@', '.', '@', '@', '@', '@', '@', '.', '@', },{'.', '@', '.', '@', '@', '@', '@', '@', '.', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '.', '@', },{'@', '.', '@', '@', '@', '@', '.', '.', '.', '.', }};
    char frame22[9][10]={{'@', '@', '@', '@', '@', '.', '.', '.', '.', '.', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '.', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '.', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '.', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '.', '@', '@', },{'.', '@', '@', '@', '@', '.', '.', '.', '.', '.', }};
    char frame23[9][10]={{'@', '@', '@', '@', '.', '.', '.', '.', '.', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '.', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'@', '@', '@', '@', '.', '.', '.', '.', '.', '@', }};
    char frame24[9][10]={{'@', '@', '@', '.', '.', '.', '.', '.', '@', '.', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '.', },{'.', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'.', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '.', '.', '.', '.', '.', '@', '.', }};
    char frame25[9][10]={{'@', '@', '.', '.', '.', '.', '.', '@', '.', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '.', '.', },{'.', '@', '@', '@', '.', '@', '@', '@', '.', '.', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '.', '.', '.', '.', '.', '@', '.', '@', }};
    char frame26[9][10]={{'@', '.', '.', '.', '.', '.', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '.', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '.', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '.', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '.', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '.', '.', '.', '.', '.', '@', '.', '@', '@', }};
    char frame27[9][10]={{'.', '.', '.', '.', '.', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '.', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '.', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '.', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '.', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '.', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '.', },{'@', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'.', '.', '.', '.', '.', '@', '.', '@', '@', '@', }};
    char frame28[9][10]={{'.', '.', '.', '.', '@', '.', '@', '@', '@', '.', },{'@', '.', '@', '@', '@', '.', '.', '@', '@', '.', },{'@', '.', '@', '@', '@', '.', '.', '@', '@', '.', },{'@', '.', '@', '@', '@', '.', '@', '.', '@', '.', },{'@', '.', '@', '@', '@', '.', '@', '.', '@', '.', },{'@', '.', '@', '@', '@', '.', '@', '@', '.', '.', },{'@', '.', '@', '@', '@', '.', '@', '@', '.', '.', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '.', },{'.', '.', '.', '.', '@', '.', '@', '@', '@', '.', }};
    char frame29[9][10]={{'.', '.', '.', '@', '.', '@', '@', '@', '.', '@', },{'.', '@', '@', '@', '.', '.', '@', '@', '.', '@', },{'.', '@', '@', '@', '.', '.', '@', '@', '.', '@', },{'.', '@', '@', '@', '.', '@', '.', '@', '.', '@', },{'.', '@', '@', '@', '.', '@', '.', '@', '.', '@', },{'.', '@', '@', '@', '.', '@', '@', '.', '.', '@', },{'.', '@', '@', '@', '.', '@', '@', '.', '.', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '.', '@', },{'.', '.', '.', '@', '.', '@', '@', '@', '.', '@', }};
    char frame30[9][10]={{'.', '.', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '@', '@', '.', '.', '@', '@', '.', '@', '.', },{'@', '@', '@', '.', '.', '@', '@', '.', '@', '.', },{'@', '@', '@', '.', '@', '.', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '.', '@', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '.', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '.', '.', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '.', '@', '.', },{'.', '.', '@', '.', '@', '@', '@', '.', '@', '@', }};
    char frame31[9][10]={{'.', '@', '.', '@', '@', '@', '.', '@', '@', '.', },{'@', '@', '.', '.', '@', '@', '.', '@', '.', '@', },{'@', '@', '.', '.', '@', '@', '.', '@', '.', '@', },{'@', '@', '.', '@', '.', '@', '.', '@', '@', '.', },{'@', '@', '.', '@', '.', '@', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '.', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '.', '.', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '.', '@', '.', '@', },{'.', '@', '.', '@', '@', '@', '.', '@', '@', '.', }};
    char frame32[9][10]={{'@', '.', '@', '@', '@', '.', '@', '@', '.', '.', },{'@', '.', '.', '@', '@', '.', '@', '.', '@', '@', },{'@', '.', '.', '@', '@', '.', '@', '.', '@', '@', },{'@', '.', '@', '.', '@', '.', '@', '@', '.', '.', },{'@', '.', '@', '.', '@', '.', '@', '@', '@', '@', },{'@', '.', '@', '@', '.', '.', '@', '@', '@', '@', },{'@', '.', '@', '@', '.', '.', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '.', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '.', '.', }};
    char frame33[9][10]={{'.', '@', '@', '@', '.', '@', '@', '.', '.', '.', },{'.', '.', '@', '@', '.', '@', '.', '@', '@', '@', },{'.', '.', '@', '@', '.', '@', '.', '@', '@', '@', },{'.', '@', '.', '@', '.', '@', '@', '.', '.', '.', },{'.', '@', '.', '@', '.', '@', '@', '@', '@', '@', },{'.', '@', '@', '.', '.', '@', '@', '@', '@', '@', },{'.', '@', '@', '.', '.', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '.', '@', '.', '@', '@', '@', },{'.', '@', '@', '@', '.', '@', '@', '.', '.', '.', }};
    char frame34[9][10]={{'@', '@', '@', '.', '@', '@', '.', '.', '.', '@', },{'.', '@', '@', '.', '@', '.', '@', '@', '@', '.', },{'.', '@', '@', '.', '@', '.', '@', '@', '@', '@', },{'@', '.', '@', '.', '@', '@', '.', '.', '.', '@', },{'@', '.', '@', '.', '@', '@', '@', '@', '@', '.', },{'@', '@', '.', '.', '@', '@', '@', '@', '@', '.', },{'@', '@', '.', '.', '@', '@', '@', '@', '@', '.', },{'@', '@', '@', '.', '@', '.', '@', '@', '@', '.', },{'@', '@', '@', '.', '@', '@', '.', '.', '.', '@', }};
    char frame35[9][10]={{'@', '@', '.', '@', '@', '.', '.', '.', '@', '@', },{'@', '@', '.', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '.', '@', '.', '@', '@', '@', '@', '@', },{'.', '@', '.', '@', '@', '.', '.', '.', '@', '@', },{'.', '@', '.', '@', '@', '@', '@', '@', '.', '@', },{'@', '.', '.', '@', '@', '@', '@', '@', '.', '@', },{'@', '.', '.', '@', '@', '@', '@', '@', '.', '@', },{'@', '@', '.', '@', '.', '@', '@', '@', '.', '@', },{'@', '@', '.', '@', '@', '.', '.', '.', '@', '@', }};
    char frame36[9][10]={{'@', '.', '@', '@', '.', '.', '.', '@', '@', '@', },{'@', '.', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '.', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '.', '.', '.', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '.', '@', '@', },{'.', '.', '@', '@', '@', '@', '@', '.', '@', '@', },{'.', '.', '@', '@', '@', '@', '@', '.', '@', '@', },{'@', '.', '@', '.', '@', '@', '@', '.', '@', '@', },{'@', '.', '@', '@', '.', '.', '.', '@', '@', '@', }};
    char frame37[9][10]={{'.', '@', '@', '.', '.', '.', '@', '@', '@', '@', },{'.', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'.', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '.', '.', '.', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '.', '@', '@', '@', },{'.', '@', '.', '@', '@', '@', '.', '@', '@', '@', },{'.', '@', '@', '.', '.', '.', '@', '@', '@', '@', }};
    char frame38[9][10]={{'@', '@', '.', '.', '.', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '.', '.', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '.', '@', '@', '@', '@', },{'@', '@', '.', '.', '.', '@', '@', '@', '@', '@', }};
    char frame39[9][10]={{'@', '.', '.', '.', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '.', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '.', '@', '@', '@', '@', '@', },{'@', '.', '.', '.', '@', '@', '@', '@', '@', '@', }};
    char frame40[9][10]={{'.', '.', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '.', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '.', '@', '@', '@', '@', '@', '@', },{'.', '.', '.', '@', '@', '@', '@', '@', '@', '@', }};
    char frame41[9][10]={{'.', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '.', '@', '@', '@', '@', '@', '@', '@', },{'.', '.', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame42[9][10]={{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '.', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame43[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'.', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', }};
    char frame44[9][10]={{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', },{'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', }};

    for(int i=0; i<loops; i++){
        Printframe(frame1,(msPerFrame*4));	
        Printframe(frame2,(msPerFrame*12));	
        Printframe(frame3,(msPerFrame*4));	
        Printframe(frame4,(msPerFrame*12));	
        Printframe(frame5,(msPerFrame*4));	
        Printframe(frame6,msPerFrame);	
        Printframe(frame7,msPerFrame);	
        Printframe(frame8,msPerFrame);	
        Printframe(frame9,msPerFrame);	
        Printframe(frame10,msPerFrame);	
        Printframe(frame11,msPerFrame);	
        Printframe(frame12,msPerFrame);	
        Printframe(frame13,msPerFrame);	
        Printframe(frame14,msPerFrame);	
        Printframe(frame15,msPerFrame);	
        Printframe(frame16,msPerFrame);	
        Printframe(frame17,msPerFrame);	
        Printframe(frame18,msPerFrame);	
        Printframe(frame19,msPerFrame);	
        Printframe(frame20,msPerFrame);	
        Printframe(frame21,msPerFrame);	
        Printframe(frame22,msPerFrame);	
        Printframe(frame23,msPerFrame);	
        Printframe(frame24,msPerFrame);	
        Printframe(frame25,msPerFrame);	
        Printframe(frame26,msPerFrame);	
        Printframe(frame27,msPerFrame);	
        Printframe(frame28,msPerFrame);	
        Printframe(frame29,msPerFrame);	
        Printframe(frame30,msPerFrame);	
        Printframe(frame31,msPerFrame);	
        Printframe(frame32,msPerFrame);	
        Printframe(frame33,msPerFrame);	
        Printframe(frame34,msPerFrame);	
        Printframe(frame35,msPerFrame);	
        Printframe(frame36,msPerFrame);	
        Printframe(frame37,msPerFrame);	
        Printframe(frame38,msPerFrame);	
        Printframe(frame39,msPerFrame);	
        Printframe(frame40,msPerFrame);	
        Printframe(frame41,msPerFrame);	
        Printframe(frame42,msPerFrame);	
        Printframe(frame43,msPerFrame);	
        Printframe(frame44,msPerFrame);	
    }
    
}
