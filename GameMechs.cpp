
#include "GameMechs.h"

#include <iostream>

GameMechs::GameMechs() {
    // std::cout << "GameMechs const: ";
    boardSizeX = 30;
    boardSizeY = 15;
    score = 0;
    speed = 100000;
    exitFlag = false;
    loseFlag = false;
    input = '\0';
    // std::cout << "Success" << std::endl;
    infoToggle = -1;
}

GameMechs::GameMechs(int boardX, int boardY) {
    // std::cout << "GameMechs const: ";
    boardSizeX = boardX;
    boardSizeY = boardY;
    speed = 100000;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    input = '\0';
    // std::cout << "Success" << std::endl;
    infoToggle = -1;
}

// do you need a destructor?
GameMechs::~GameMechs() {
    // using iteration 1B
}

bool GameMechs::getExitFlagStatus() const {
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const {
    return loseFlag;
}

char GameMechs::getInput() const {
    return input;
}

int GameMechs::getScore() const {
    return score;
}

void GameMechs::incrementScore() {
    score = score + 1;
}

int GameMechs::getBoardSizeX() const {
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const {
    return boardSizeY;
}

void GameMechs::setExitTrue() {
    exitFlag = 1;
}

void GameMechs::setLoseFlag() {
    loseFlag = 1;
}

void GameMechs::setInput(char this_input) {
    input = this_input;
}

void GameMechs::clearInput() {
    input = '\0';
}

// More methods should be added here
// using iteration 1B
void GameMechs::IncreaseDelay() {
    if (speed < 200000) {
        speed = speed + 50000;
    }
}
void GameMechs::DecreaseDelay() {
    if (speed > 0) {
        speed = speed - 50000;
    }
}
int GameMechs::getDelay() const {
    return speed;
}

void GameMechs::processInput() {
    if (this->input == 'o') this->DecreaseDelay();
    if (this->input == 'p') this->IncreaseDelay();
    if (this->input == ' ') this->setExitTrue();
}