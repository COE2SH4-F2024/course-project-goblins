#include "Player.h"

#include <iostream>
#include <set>

Player::Player(GameMechs* thisGMRef) {
    std::cout << "Player const: ";
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    //  more actions to be included
    playerPosList = new objPosArrayList;
    playerPosList->insertHead(objPos(1, 1, '@'));
    std::cout << "Success" << std::endl;
}

Player::~Player() {
    // delete any heap members here
    // delete playerPos;
    delete playerPosList;
}

objPos* Player::getHearPos() const {
    // return the reference to the playerPos arrray list
    return playerPosList->getHeadElement().getObjPos();
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
    int x = playerPosList->getHeadElement().getObjPos()->pos->x;
    int y = playerPosList->getHeadElement().getObjPos()->pos->y;
    if (playerPosList->getSize() > 0) {
        playerPosList->removeHead();
        playerPosList->insertHead(objPos(x, y, 'O'));
    }
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
        x = mainGameMechsRef->getBoardSizeX() - 2;
    if (x >= (mainGameMechsRef->getBoardSizeX() - 1))
        x = 1;
    if (y < 1)
        y = mainGameMechsRef->getBoardSizeY() - 2;
    if (y >= (mainGameMechsRef->getBoardSizeY() - 1))
        y = 1;

    playerPosList->insertHead(objPos(x, y, '@'));
}

// More methods to be added
objPosArrayList* Player::getPlayerBody() const {
    return playerPosList;  // Return the body list (head to tail)
}
void Player::cuttail() {
    playerPosList->removeTail();
}
int Player::getsize() {
    return playerPosList->getSize();
}

void Player::selfCollisionCheck() {
    int size = playerPosList->getSize();
    for (int i = 2; i < size; ++i) {
        if (playerPosList->getElement(i).isPosEqual(playerPosList->getHeadElement().getObjPos())) {
            mainGameMechsRef->setLoseFlag();
        }
    }
}