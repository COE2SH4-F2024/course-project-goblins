#include "Food.h"

#include <iostream>

#include "GameMechs.h"
#include "objPosArrayList.h"

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
        return;
    }
    do {
        isValid = true;
        x = rand() % (mainGameMechsRef->getBoardSizeX() - 2);
        y = rand() % (mainGameMechsRef->getBoardSizeY() - 2);
        ++x;
        ++y;
        objPos tempPos = objPos(x, y, '*');
        for (int i = 0; i < bodySize; ++i) {
            objPos genFood = snakeBody->getElement(i);
            if (tempPos.isPosEqual(&genFood)) {
                isValid = false;
                break;
            }
        }
        for (int i = 0; i < foodSize; ++i) {
            objPos genFood = foodPosList->getElement(i);
            if (tempPos.isPosEqual(&genFood)) {
                isValid = false;
                break;
            }
        }

    } while (!isValid);
    char sym = '*';
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
