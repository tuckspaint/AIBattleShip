#include "Robot.h"

bool Robot::hardMove(char board[][10])
{
    /*
    for(int i=0; i< board[0].length(); i++)
    {
        for(int j=0; j<board[0].length(); j++)
        {
            if(board[j][i] == 'S')
            {
                board[j][i] = 'H';
                return true;
            }
        }
    }
    return false;
}

//Decide based on the logic whether it was a hit or not and return true if it is a hit
bool Robot::mediumMove()
{
    return true;
}

//Decide based on the logic whether it was a hit or not and return true if it is a hit
bool Robot::easyMove()
{
    return true;
}