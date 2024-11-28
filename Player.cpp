#include "Player.h"

Player::Player(GameMechs* thisGMRef) {
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '@');
    playerPosList->insertHead(playerPos);
}

Player::~Player() {
    // delete any heap members here
    // nothing to delet here
}

objPos Player::getPlayerPos() const {
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
    mainGameMechsRef->clearInput();
}

void Player::movePlayer() {
    // PPA3 Finite State Machine logic
    int x = playerPos.pos->x;
    int y = playerPos.pos->y;

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
    if (x < 0)
        x = mainGameMechsRef->getBoardSizeX() - 1;
    if (x >= mainGameMechsRef->getBoardSizeX())
        x = 0;
    if (y < 0)
        y = mainGameMechsRef->getBoardSizeY() - 1;
    if (y >= mainGameMechsRef->getBoardSizeY())
        y = 0;

    playerPos.setObjPos(x, y, '*');
}

// More methods to be added
void Player::increasePlayerBody() {
    playerPosList->insertHead(playerPos);
}

objPosArrayList* Player::getPlayerBody() const {
    return playerPosList;  // Return the body list (head to tail)
}