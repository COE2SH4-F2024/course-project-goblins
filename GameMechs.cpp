
#include "GameMechs.h"

#include <iostream>

#include "Food.h"
#include "Player.h"

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

string GameMechs::generateGameBoard(Food* food, Player* player) {
    char board[this->getBoardSizeY()][this->getBoardSizeX()];
    string boardString;

    for (int y = 0; y < this->getBoardSizeY(); ++y) {
        for (int x = 0; x < this->getBoardSizeX(); ++x) {
            board[y][x] = ' ';

            if (x == 0 || y == 0 || x == this->getBoardSizeX() - 1 || y == this->getBoardSizeY() - 1) {
                board[y][x] = '#';
            }

            for (int i = 0; i < food->getFoodPos()->getSize(); i++) {
                if (y == food->getFoodPos()->getElement(i).getObjPos().pos->y && x == food->getFoodPos()->getElement(i).getObjPos().pos->x) {
                    board[y][x] = food->getFoodPos()->getElement(i).getSymbol();
                }
            }
            for (int i = 0; i < player->getsize(); i++) {
                if (y == player->getPlayerBody()->getElement(i).getObjPos().pos->y && x == player->getPlayerBody()->getElement(i).getObjPos().pos->x) {
                    board[y][x] = player->getPlayerBody()->getElement(i).getSymbol();
                }
            }
            if (x == player->getHearPos().pos->x && y == player->getHearPos().pos->y) {
                board[y][x] = player->getHearPos().symbol;
            }
        }
    }

    // Convert board to string
    for (int y = 0; y < this->getBoardSizeY(); ++y) {
        for (int x = 0; x < this->getBoardSizeX(); ++x) {
            switch (board[y][x]) {
                case '#':
                    boardString += "\033[1;37m#\033[0m";
                    break;
                case 'O':
                    boardString += "\033[1;32mO\033[0m";
                    break;
                case '@':
                    boardString += "\033[1;92m@\033[0m";
                    break;
                case '*':
                    boardString += "\033[1;31m*\033[0m";
                    break;
                case 'S':
                    boardString += "\033[1;34mS\033[0m";
                    break;
                case 'E':
                    boardString += "\033[1;36mE\033[0m";
                    break;
                case 'H':
                    boardString += "\033[1;35mH\033[0m";
                    break;
                default:
                    boardString += board[y][x];
                    break;
            }
        }
        boardString += '\n';
    }

    return boardString;
}