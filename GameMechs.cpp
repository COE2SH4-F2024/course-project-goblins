#include "GameMechs.h"

GameMechs::GameMechs() {
    boardSizeX = 30;
    boardSizeY = 15;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    input = '\0';

    // board = new char *[boardSizeY];
    // for (int i =0; i< boardSizeY;i++){
    //     board[i]= new char [boardSizeX];
    // }
    // for (int i =0; i< boardSizeY;i++){
    //     for (int j =0; j< boardSizeY; i++){
    //         if (i==0||i==boardSizeY-1||j==0||j==boardSizeX-1){
    //             board[i][j]='#';
    //         }

    //     }

    // }
}

GameMechs::GameMechs(int boardX, int boardY) {
    boardSizeX = boardX;
    boardSizeY = boardY;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    input = '\0';

    // board = new char *[boardSizeY];
    // for (int i =0; i< boardSizeY;i++){
    //     board[i]= new char [boardSizeX];
    // }
    // for (int i =0; i< boardSizeY;i++){
    //     for (int j =0; j< boardSizeY; i++){
    //         if (i==0||i==boardSizeY-1||j==0||j==boardSizeX-1){
    //             board[i][j]='#';
    //         }

    //     }

    // }
}

// do you need a destructor?
GameMechs::~GameMechs() {
    // no, but it is still here just to have it.
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
    input = NULL;
}

// More methods should be added here