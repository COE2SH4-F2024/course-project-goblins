#include "Food.h"

#include <iostream>

Food::Food() {
    foodPosList = new objPosArrayList;
    foodPosList->insertHead(objPos(1, 1, '*'));
}

Food::Food(GameMechs* thisGMRef) {
    // std::cout << "Food const: ";
    mainGameMechsRef = thisGMRef;
    // foodPos = new objPos;
    foodPosList = new objPosArrayList;
    foodPosList->insertHead(objPos(1, 1, '*'));
    // std::cout << "Success" << std::endl;
}

Food::~Food() {
    // delete foodPos;
    delete foodPosList;
    delete mainGameMechsRef;
}

void Food::generateFood(objPosArrayList* snakeBody, int def) {
    bool isValid = true;
    int x, y;
    int bodySize = snakeBody->getSize();
    int foodSize = foodPosList->getSize();
    if (foodSize > 5) {
        // If there are already 5 food, do not generate more food
        return;
    }
    do {
        isValid = true;
        x = rand() % (mainGameMechsRef->getBoardSizeX() - 2) + 1;
        y = rand() % (mainGameMechsRef->getBoardSizeY() - 2) + 1;
        objPos tempPos = objPos(x, y, '*');
        // body collision check
        for (int i = 0; i < bodySize; ++i) {
            objPos genFood = snakeBody->getElement(i);
            if (tempPos.isPosEqual(&genFood)) {
                isValid = false;
                break;
            }
        }
        // self collision check
        for (int i = 0; i < foodSize; ++i) {
            objPos genFood = foodPosList->getElement(i);
            if (tempPos.isPosEqual(&genFood)) {
                isValid = false;
                break;
            }
        }

    } while (!isValid);

    // defult to normal food
    char sym = '*';

    // if not defult food, choose randomly from the pool
    if (def == 0) {
        int entry = rand() % 3 + 1;
        switch (entry) {
            case 1:  // Shrink
                sym = 'S';
                break;
            case 2:  // Extra score
                sym = 'E';
                break;
            case 3:  // even more score but add 10 body parts
                sym = 'H';
                break;
        }
    }

    foodPosList->insertHead(objPos(x, y, sym));
}

objPosArrayList* Food::getFoodPos() const {
    return foodPosList;
}
