#include "Food.h"

#include <iostream>

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

// Do I even need a defult constractor?
Food::Food(GameMechs* thisGMRef) {
    std::cout << "Food const: ";
    mainGameMechsRef = thisGMRef;
    foodPos = new objPos;
    foodPos->setObjPos(1, 1, '*');
    std::cout << "Success" << std::endl;
}

Food::~Food() {
    delete foodPos;
    delete mainGameMechsRef;
}

void Food::generateFood(objPosArrayList* snakeBody) {
    bool isValid = false;
    int x, y;
    int size = snakeBody->getSize();
    while (!isValid) {
        x = rand() % (mainGameMechsRef->getBoardSizeX() - 2);
        y = rand() % (mainGameMechsRef->getBoardSizeY() - 2);
        isValid = true;
        for (int i = 0; i < size; ++i) {
            if (y == snakeBody->getElement(i).getObjPos()->pos->y && x == snakeBody->getElement(i).getObjPos()->pos->x) {
                isValid = false;
                break;
            }
        }
    }
    foodPos->setObjPos(++x, ++y, '*');
}

objPos* Food::getFoodPos() const {
    return foodPos;
}
