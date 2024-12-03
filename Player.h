#ifndef PLAYER_H
#define PLAYER_H

#include "Food.h"
#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player {
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

   public:
    enum Dir { UP,
               DOWN,
               LEFT,
               RIGHT,
               STOP };  // This is the direction state

    Player(GameMechs* thisGMRef);
    ~Player();

    objPos getHearPos() const;  // Upgrade this in iteration 3.
    void updatePlayerDir();
    void movePlayer();

    // More methods to be added here
    objPosArrayList* getPlayerBody() const;
    void cuttail();
    int getsize();
    void selfCollisionCheck();
    void addMoreTail();
    void checkFood(Food* food);

   private:
    // objPos* playerPos;  // Upgrade this in iteration 3.

    enum Dir myDir;
    objPosArrayList* playerPosList;
    int headx, heady;
    // Need a reference to the Main Game Mechanisms
    GameMechs* mainGameMechsRef;
};

#endif