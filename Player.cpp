#include "Player.h"
#include "MacUILib.h"

//Function that declares Game Mechanics and Reference to Food, sets the intitial x-y coordinates and symbol of the player to the head
//as well as allocates memory to the player position array list
Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    mainFoodRef = thisFoodRef;
    direction = stop;

    
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '@');

    playerPosList = new objPosArrayList();
    
    playerPosList->insertHead(tempPos);



}

//Deallocates the memory of the player position array list
Player::~Player()
{
    delete playerPosList;
   
}

// Returns the reference to the playerPos array list
objPosArrayList* Player::getPlayerPos()
{
    return playerPosList;
    
}

//Function that updates the keyboard input of the player and sets the direction's value
void Player::updatePlayerDir()
{

    char input = mainGameMechsRef->getInput();

    switch(input){ 
        case 27:
            mainGameMechsRef->setExitTrue();
            break;
        case 'W':
        case 'w':
            if(direction != down){
                direction = up;
            }
            break;

        case 'S':
        case 's':
            if(direction != up){
                direction = down;
            }
            break;
        
        case 'A':
        case 'a':
            if(direction != right){
                direction = left;
            }
            break;
            
        case 'D':
        case 'd':
            if(direction != left){
                direction = right;
            }
            break;

        default:
            break;
    }        
}

//Function that updates the snakes movement on the screen, making it wrap around the board as it makes contact with the border
//Sets specific values to the length and score based on the checkFoodConsumption functions value. Also sets the lose flag if self collision has happened.
void Player::movePlayer()
{
    

    objPos currentHead;
    objPos foodPos;

    mainFoodRef->getFoodPos(foodPos);
    playerPosList->getHeadElement(currentHead);

    //If the "o" is eaten, increase snake length by 1 and score by 1
    if(checkFoodConsumption() == 1){

        increasePlayerLength(1);
        mainFoodRef->generateFood(playerPosList);
        mainGameMechsRef->incrementScore(1);
    }

    //If the "S" is eaten, increase snake length by 5 and score by 1
    else if(checkFoodConsumption() == 2){

        increasePlayerLength(5);
        mainFoodRef->generateFood(playerPosList);
        mainGameMechsRef->incrementScore(1);
    }

    //If the "$" is eaten, increase snake length by 1 and score by 5
    else if(checkFoodConsumption() == 3){

        increasePlayerLength(1);
        mainFoodRef->generateFood(playerPosList);
        mainGameMechsRef->incrementScore(5);
    }


    //Wraps around the board based on location
    if(direction == up){
        currentHead.y--;
        if(currentHead.y <= 0){
            currentHead.y = mainGameMechsRef->getBoardSizeY() - 2;
        }
    }

    else if(direction == down){
        currentHead.y++;
        if(currentHead.y >= mainGameMechsRef->getBoardSizeY() - 1){
            currentHead.y = 1;
        }
    }

    else if(direction == left){
        currentHead.x--;
        if(currentHead.x <= 0){
            currentHead.x = mainGameMechsRef->getBoardSizeX() - 2;
        }
    }

    else if(direction == right){
        currentHead.x++;
        if(currentHead.x >= mainGameMechsRef->getBoardSizeX() - 1){
            currentHead.x = 1;
        }
    }
    playerPosList->insertHead(currentHead);
    playerPosList->removeTail();

    //Lose condition is activated when collision happens
    if(checkSelfCollision() == true){
        mainGameMechsRef->setLoseFlag();
    }

}

//Boolean Function for the self collision check
bool Player::checkSelfCollision(){
    objPos currentHead;
    objPos bodySize;

    bool crashFlag = false;

    playerPosList->getHeadElement(currentHead);

    //Checks if the head has collided with its body
    for(int a = 1; a < playerPosList->getSize(); a++){
        playerPosList->getElement(bodySize, a);
        if (currentHead.isPosEqual(&bodySize))
        {
            crashFlag = true;
        }
    }

    return crashFlag;
}

//Checks the food consumption by checking if the head has overlapped with the food's coordinates
int Player::checkFoodConsumption(){
    
    objPosArrayList* foodBucket = mainFoodRef->getNewFoodPos();
    objPos currentHead;
    objPos newFoodPos;

    int returnNum;

    

    playerPosList->getHeadElement(currentHead);


    for(int i = 0; i < foodBucket->getSize(); i++){
        foodBucket->getElement(newFoodPos, i);
        if(currentHead.isPosEqual(&newFoodPos)){

            //Depending on which food is eaten, sets a specific return value to be used
            if(newFoodPos.symbol == 'o')
            {
                returnNum = 1;
            }
            else if(newFoodPos.symbol == 'S')
            {
                returnNum = 2;
            }
            else if(newFoodPos.symbol == '$')
            {
                returnNum = 3;
            }
        }
    }

    return returnNum;

}

//Increases player length based on the value of the food
void Player::increasePlayerLength(int size){

    objPos currentHead;
    playerPosList->getHeadElement(currentHead);
    

    for (int i = 0; i <size; i++)
    {
        playerPosList->insertHead(currentHead);
    }

}
