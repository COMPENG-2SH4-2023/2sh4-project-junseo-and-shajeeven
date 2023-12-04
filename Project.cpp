#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "food.h"
#include "objPosArrayList.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs * myGM;
Player * myPlayer;
Food * myFood;

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    //The functions will run while the exit flag and the lose flag are false
    while(myGM->getExitFlagStatus() == false && myGM->getLoseFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    objPosArrayList *temp;
    
    //Initialize the gameboard, player and food positions by allocating memory on the heap
    myGM = new GameMechs(31, 13);
    myFood = new Food(myGM);
    myPlayer = new Player(myGM, myFood);
    
    temp = myPlayer->getPlayerPos();
       
    myFood->generateFood(temp);
}

//Obtains the keyboard input that the user presses
void GetInput(void)
{
    myGM->getInput();
}

//Responsible for player movement and any collisions
void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();

    myGM->clearInput();
}

//Draws the board, player, food, score and controls
void DrawScreen(void)
{
    MacUILib_clearScreen(); 


    objPosArrayList *playerBody = myPlayer->getPlayerPos();
    objPosArrayList *foodBucket = myFood->getNewFoodPos();


    objPos tempFoodPos;

    objPos tempBody;

    

    myFood->getFoodPos(tempFoodPos);

    bool drawn;  

    int i, j, k, l;

    MacUILib_printf("          SNAKE GAME\n");
    for(i = 0; i < myGM->getBoardSizeY(); i++){

        for(j = 0; j < myGM->getBoardSizeX(); j++){

            drawn = false;

            //Outputs the player body (head and tail)
            for(k = 0; k < playerBody->getSize(); k++){
                playerBody->getElement(tempBody, k);
                if(tempBody.y == i && tempBody.x == j){
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                    break;
                }
            }

            //Outputs the randomly generated pieces of food
            if(drawn == false){
                for(l = 0; l < foodBucket->getSize(); l++){
                    foodBucket->getElement(tempFoodPos, l);
                    if(tempFoodPos.y == i && tempFoodPos.x == j){
                        MacUILib_printf("%c", tempFoodPos.symbol);
                        drawn = true;
                        break;
                    }
                }
            }

            //Generates the board 
            if(drawn == false){
                if(i == 0 || j == 0 || i == (myGM->getBoardSizeY() - 1) || j == (myGM->getBoardSizeX() - 1)){
                    MacUILib_printf("%c", '#');
                }
                else{
                    MacUILib_printf("%c", ' ');
                }
            }

        }
        MacUILib_printf("\n");

    }

    //Outputs Score and Controls
    MacUILib_printf("Score: %d\n\n", myGM->getScore());
    MacUILib_printf("Controls:\nW: UP\nA: LEFT\nS: DOWN\nD: RIGHT\nESC: EXIT");
}

//Speed of how fast the board and its contents are updated
void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST);
}

//Clears the screen and presents the final score of the player
void CleanUp(void)
{
    MacUILib_clearScreen();


    //Game ending screen
    if(myGM->getExitFlagStatus() == true){
        MacUILib_printf("Game Ended. You Scored %d points.\n", myGM->getScore());
    }

    //Game losing screen
    else if(myGM->getLoseFlagStatus() == true){
        MacUILib_printf("You Died. You Scored %d points.\n", myGM->getScore());
    }    
  
    MacUILib_uninit();

    //deleting heap members for reduced memory leaks
    delete myGM;
    delete myPlayer;
    delete myFood;
}
