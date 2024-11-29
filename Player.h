#ifndef PLAYER_H
#define PLAYER_H

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

    objPos* getPlayerPos() const;  // Upgrade this in iteration 3.
    void updatePlayerDir();
    void movePlayer();

    // More methods to be added here
    void increasePlayerBody();
    objPosArrayList* getPlayerBody() const;
    void moveBody();
    void moveBodyincrease();
    int getsize();

   private:
    objPos* playerPos;  // Upgrade this in iteration 3.
    objPos* first_body;
    enum Dir myDir;
    objPosArrayList* playerPosList;
    int headx, heady;
    // Need a reference to the Main Game Mechanisms
    GameMechs* mainGameMechsRef;
};

#endif