#include "Food.h"

#include <iostream>

#include "GameMechs.h"
#include "objPosArrayList.h"

// Do I even need a defult constractor?
Food::Food(GameMechs* thisGMRef) {
    // std::cout << "Food const: ";
    mainGameMechsRef = thisGMRef;
    foodPos = new objPos;
    foodPosList = new objPosArrayList;
    foodPosList->insertHead(objPos(1, 1, '*'));
    // std::cout << "Success" << std::endl;
}

Food::~Food() {
    delete foodPos;
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
        for (int i = 0; i < bodySize; ++i) {
            if (y == snakeBody->getElement(i).getObjPos()->pos->y && x == snakeBody->getElement(i).getObjPos()->pos->x) {
                isValid = false;
                break;
            }
        }
        for (int i = 0; i < foodSize; ++i) {
            if (y == foodPosList->getElement(i).getObjPos()->pos->y && x == foodPosList->getElement(i).getObjPos()->pos->x) {
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
