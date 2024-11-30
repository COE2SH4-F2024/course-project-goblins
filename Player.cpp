#include "Player.h"

#include <iostream>

Player::Player(GameMechs* thisGMRef) {
    std::cout << "Player const: ";
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    // first_body = new objPos;
    // first_body->setObjPos(0, 0, '=');
    //  more actions to be included
    playerPos = new objPos;
    playerPosList = new objPosArrayList;
    playerPos->setObjPos(1, 1, '@');
    // playerPosList->insertHead(*playerPos);
    std::cout << "Success" << std::endl;
}

Player::~Player() {
    // delete any heap members here
    delete playerPos;
    delete playerPosList;
}

objPos* Player::getPlayerPos() const {
    // return the reference to the playerPos arrray list
    return playerPos;
}

void Player::updatePlayerDir() {
    // PPA3 input processing logic
    char input;
    input = mainGameMechsRef->getInput();
    switch (input) {
        case 'w':
            if (myDir == LEFT || myDir == RIGHT || myDir == STOP)
                myDir = UP;
            break;

        case 's':
            if (myDir == LEFT || myDir == RIGHT || myDir == STOP)
                myDir = DOWN;
            break;

        case 'a':
            if (myDir == UP || myDir == DOWN || myDir == STOP)
                myDir = LEFT;
            break;

        case 'd':
            if (myDir == UP || myDir == DOWN || myDir == STOP)
                myDir = RIGHT;
            break;

        default:
            break;
    }
}

void Player::movePlayer() {
    // PPA3 Finite State Machine logic
    int x = playerPos->getObjPos()->pos->x;
    int y = playerPos->getObjPos()->pos->y;
    // headx = x;
    // heady = y;

    switch (myDir) {
        case UP:
            y -= 1;
            break;
        case DOWN:
            y += 1;
            break;
        case LEFT:
            x -= 1;
            break;
        case RIGHT:
            x += 1;
            break;
        default:
            break;
    }

    // Wrap-around logic
    if (x < 1)
        x = mainGameMechsRef->getBoardSizeX() - 1;
    if (x >= mainGameMechsRef->getBoardSizeX())
        x = 1;
    if (y < 1)
        y = mainGameMechsRef->getBoardSizeY() - 1;
    if (y >= mainGameMechsRef->getBoardSizeY())
        y = 1;

    playerPos->setObjPos(x, y, '@');
    // first_body->setObjPos(headx, heady, '=');
}

// More methods to be added
void Player::increasePlayerBody() {
    playerPosList->insertHead(*first_body);
}

objPosArrayList* Player::getPlayerBody() const {
    return playerPosList;  // Return the body list (head to tail)
}
void Player::moveBody() {
    playerPosList[0].setObjPos('o');
}
void Player::cuttail() {
    playerPosList->removeTail();
}
int Player::getsize() {
    return playerPosList->getSize();
}