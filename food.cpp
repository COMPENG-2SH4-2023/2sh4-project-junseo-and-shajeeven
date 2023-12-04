#include "food.h"
#include "MacUILib.h"
#include "GameMechs.h"
#define SIZE 5

//Food Constructor that declares a game mechanics variable and allocates memory for the foodBucket variable, inserting 5 pieces of food 
Food::Food(GameMechs* thisGMRef){

    thisGM = thisGMRef;
    objPos tempFoodPos;
    foodBucket = new objPosArrayList();

    
    srand(time(NULL));

    for (int i =0; i<SIZE; i++)
    {
        tempFoodPos.setObjPos(1, 1, 'o');
        foodBucket->insertHead(tempFoodPos);
    }

}

//Food Destructor to deallocate the allocated memory of foodBucket
Food::~Food(){

    delete foodBucket;
}

//Function that generates the x-y coordinates and symbol of each piece of food, making sure that there is no overlap and duplication of x-y coordinates,
//adding them to the foodBucket if conditions are met
void Food::generateFood(objPosArrayList* blockPos){

    objPos body;
    objPos foodItem[SIZE];
    objPos newFoodPos;
    
    int xCandidate = 0;
    int yCandidate = 0;
    int count = 0;

    bool foodFlag = false;
    
    int xRange = thisGM->getBoardSizeX() - 1;
    int yRange = thisGM->getBoardSizeY() - 1;

    //Generating 5 random food items
    while(count < foodBucket->getSize()){
        foodBucket->getElement(foodItem[count], count);
        foodFlag = false;

        while(foodFlag == false){
            foodFlag = true;

            xCandidate = rand() % xRange;
            yCandidate = rand() % yRange;

            //parameters for food to not spawn on the border
            while(xCandidate == 0){
                xCandidate = rand() % xRange;
            }

            while(yCandidate == 0){
                yCandidate = rand() % yRange;
            }

            //for food to not overlap with the snake's body
            if(foodFlag == true){
                for(int a = 0; a < blockPos->getSize(); a++){
                    blockPos->getElement(body, a);
                    if(xCandidate == body.x && yCandidate == body.y){
                        foodFlag = false;
                        break;
                    }
                }
            }
            //for no food to overlap with the other generated foods
            for(int b = 0; b < count; b++){
                foodBucket->getElement(foodItem[b],b);
                if(xCandidate == foodItem[b].x && yCandidate == foodItem[b].y){
                    foodFlag = false;
                    break;
                }
            }

            //Setting the position and symbol to the generated foods
            if(foodFlag == true){
                foodItem[count].x = xCandidate;
                foodItem[count].y = yCandidate;
                if(count >= 0 && count <=2){
                    foodItem[count].symbol = 'o';
                }
                else if(count == 3){
                    foodItem[count].symbol = 'S';
                }
                else if(count == 4 ){
                    foodItem[count].symbol = '$';
                }
                break;
            }
        }

        //inserting the created food into the foodBucket
        foodBucket->insertHead(foodItem[count]);
        foodBucket->removeTail();

        count++;

    }

}

//Function that returns the x-y coordinates and symbol of the food
void Food::getFoodPos(objPos &returnPos){
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}

//Function that returns the contents of the foodBucket
objPosArrayList* Food::getNewFoodPos(){
    return foodBucket;
}