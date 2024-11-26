#include "Food.h"

// Do I even need a defult constractor?
Food::Food() {
    foodPos.setObjPos(1, 1, '*');
}

Food::~Food() {
    // nothing here too?
}

void Food::generateFood(int boardWidth, int boardHeight, objPosArrayList* snakeBody) {
    bool isValid = false;
    while (!isValid) {
        int x = rand() % 30;  // Example board width
        int y = rand() % 15;  // Example board height
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
