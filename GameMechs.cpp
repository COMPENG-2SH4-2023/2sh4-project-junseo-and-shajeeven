#include "GameMechs.h"
#include "MacUILib.h"

//Default Game Mechanics Constructor
GameMechs::GameMechs()
{
    input = 0;
    score = 0;
    speed = 5;
    exitFlag = false;
    loseFlag = false;
    boardSizeX = 20;
    boardSizeY = 10;

}

//Specialized Game Mechanics Constructor
GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    score = 0;
    speed = 5;
    exitFlag = false;
    loseFlag = false;
    boardSizeX = boardX;
    boardSizeY = boardY;
}


//Boolean Exit Flag Function to see if Exit Flag is True or False
bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

//Boolean Lose Flag Function to see if Lose Flag is True or False
bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

//Function that obtains the keyboard presses
char GameMechs::getInput()
{
    if(MacUILib_hasChar()){
        input = MacUILib_getChar();
    }
    
    return input;
}

//Function that obtains the amount of columns of the board
int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

//Function that obtains the amount of rows of the board
int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

//Setter Function that sets the Exit Flag to True
void GameMechs::setExitTrue()
{
    exitFlag = true;
}

//Setter Function that sets the Lose Flag to True
void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

//Function that sets the input
void GameMechs::setInput(char this_input)
{
    input = this_input;

}

//Function that clears the input value 
void GameMechs::clearInput()
{
    input = 0;
}

//Returns the score that the player has achieved in the game
int GameMechs::getScore()
{
    return score;
}

//Increments the score based on the value of a specific food
void GameMechs::incrementScore(int size)
{
    score += size;
}

