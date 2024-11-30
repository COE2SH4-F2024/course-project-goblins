#include "objPos.h"

#include <iostream>

objPos::objPos() {
    // std::cout << "objPos const: ";
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0;  // NULL
    // std::cout << "Success" << std::endl;
}

objPos::objPos(int xPos, int yPos, char sym) {
    // std::cout << "objPos const: ";
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
    // std::cout << "Success" << std::endl;
}

// Respect the rule of six / minimum four
// [TODO] Implement the missing special member functions to meet the minimum four rule
objPos::~objPos() {
    delete pos;
}

void objPos::setObjPos(objPos o) {
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos) {
    pos->x = xPos;
    pos->y = yPos;
}

void objPos::setObjPos(int xPos, int yPos, char sym) {
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}
void objPos::setObjPos(char sym) {
    symbol = sym;
}
objPos* objPos::getObjPos() const {
    objPos* returnPos = new objPos();
    returnPos->pos->x = pos->x;
    returnPos->pos->y = pos->y;
    returnPos->symbol = symbol;

    return returnPos;
}

char objPos::getSymbol() const {
    return symbol;
}

bool objPos::isPosEqual(const objPos* refPos) const {
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

char objPos::getSymbolIfPosEqual(const objPos* refPos) const {
    if (isPosEqual(refPos))
        return symbol;
    else
        return 0;
}
objPos::objPos(const objPos& other) {
    pos = new Pos;  // Allocate new memory
    pos->x = other.pos->x;
    pos->y = other.pos->y;
    symbol = other.symbol;
}
objPos& objPos::operator=(const objPos& other) {
    if (this != &other) {
        delete pos;  // Free existing memory

        pos = new Pos;  // Allocate new memory
        pos->x = other.pos->x;
        pos->y = other.pos->y;
        symbol = other.symbol;
    }
    return *this;
}