#include "Food.h"

// Do I even need a defult constractor?
Food::Food(GameMechs* thisGMRef) {
    mainGameMechsRef = thisGMRef;
    foodPos.setObjPos(1, 1, '*');
}

Food::~Food() {
    // nothing here too?
}

void Food::generateFood(objPosArrayList* snakeBody) {
    bool isValid = false;
    while (!isValid) {
        int x = rand() % mainGameMechsRef->getBoardSizeX();
        int y = rand() % mainGameMechsRef->getBoardSizeY();
        foodPos.setObjPos(x, y, '*');
        isValid = true;
        for (int i = 0; i < snakeBody->getSize(); ++i) {
            if (snakeBody->getElement(i).isPosEqual(&foodPos)) {
                isValid = false;
                break;
            }
        }
    }
}

objPos Food::getFoodPos() const {
    return foodPos;
}
