#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

#include <cstdlib>
#include <time.h>

class Food
{
    public:

        Food(GameMechs* thisGMRef);
        ~Food();

        void generateFood(objPosArrayList *blockPos);
        void getFoodPos(objPos &returnPos);


        //Function of pointer type objPosArrayList 
        objPosArrayList* getNewFoodPos();

    private:
        objPos foodPos;

        //imported the Game Mechanics header file to use its member functions
        GameMechs *thisGM;

        //imported the objPosArrayList header file to use its member functions
        objPosArrayList *foodBucket;
       
};

#endif