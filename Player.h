#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "food.h"

class Player
{
    

    public:
        enum Dir {up, down, left, right, stop}; 

        Player(GameMechs* thisGMRef, Food* thisFoodRef);
        ~Player();

        objPosArrayList* getPlayerPos(); 

        void updatePlayerDir();
        void movePlayer();

        bool checkSelfCollision();
        int checkFoodConsumption();

        void increasePlayerLength(int size);

    private:
        //imported the objPosArrayList header file to use its member functions
        objPosArrayList *playerPosList;        
        enum Dir direction;

        //imported the Game Mechanics header file to use its member functions
        GameMechs* mainGameMechsRef;
        //Imported the Food header file to use its member functions
        Food* mainFoodRef;
};

#endif