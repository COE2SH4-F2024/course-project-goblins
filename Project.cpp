#include <algorithm>
#include <iostream>

#include "GameMechs.h"
#include "MacUILib.h"
#include "Player.h"
#include "food.h"
#include "objPos.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs* gameMechs;
Player* player;
Food* food;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void) {
    Initialize();

    while (!gameMechs->getExitFlagStatus()) {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}

void Initialize(void) {
    MacUILib_init();
    cout << "\033[2J\033[1;1H";
    srand(time(NULL));
    gameMechs = new GameMechs(30, 15);
    player = new Player(gameMechs);
    food = new Food(gameMechs);

    for (int i = 0; i < 2; ++i)
        food->generateFood(player->getPlayerBody(), 1);

    for (int i = 0; i < 2; ++i)
        food->generateFood(player->getPlayerBody(), 0);

    // MacUILib_Delay(1500000);
    //  gameMechs->incrementScore();
    // cout << "\033[2J\033[1;1H";
    // hide cursor
    cout << "\033[?25l";
}

void GetInput(void) {
    if (MacUILib_hasChar()) {
        char input = MacUILib_getChar();
        gameMechs->setInput(input);
    }
}

void RunLogic(void) {
    bool didEatfood = false;
    if (gameMechs->getInput() == ' ')
        gameMechs->setExitTrue();

    player->updatePlayerDir();

    for (int i = 0; i < food->getFoodPos()->getSize(); ++i) {
        objPos foodPos = food->getFoodPos()->getElement(i);
        if (player->getHearPos().isPosEqual(&foodPos) || gameMechs->getInput() == 't') {
            // if player ate food
            gameMechs->incrementScore();
            int foodtype = 1;
            if (food->getFoodPos()->getElement(i).getSymbol() != '*') {
                foodtype = 0;
                switch (food->getFoodPos()->getElement(i).getSymbol()) {
                    case 'S':  // Shrink
                        for (int j = 0; j < 6; ++j) {
                            if (player->getPlayerBody()->getSize() > 3) {
                                player->getPlayerBody()->removeTail();
                            }
                        }
                        break;
                    case 'E':  // Extra score
                        for (int j = 0; j < 10; ++j) {
                            gameMechs->incrementScore();
                        }
                        break;
                    case 'H':  // even more score but add 10 body parts
                        for (int j = 0; j < 50; ++j) {
                            gameMechs->incrementScore();
                        }
                        for (int k = 0; k < 10; ++k) {
                            player->addMoreTail();
                        }
                        break;
                }
            }
            food->getFoodPos()->removeAtIndex(i);
            food->generateFood(player->getPlayerBody(), foodtype);
            didEatfood = true;
        }
    }
    if (player->getsize() > 0 && !didEatfood) {
        // if player did not ate food
        player->cuttail();
    }
    player->movePlayer();

    player->selfCollisionCheck();

    if (gameMechs->getLoseFlagStatus())
        gameMechs->setExitTrue();

    gameMechs->clearInput();
}

void DrawScreen(void) {
    // MacUILib_clearScreen();

    char board[15][30];
    string boardString;

    // Populate the board
    for (int y = 0; y < gameMechs->getBoardSizeY(); ++y) {
        for (int x = 0; x < gameMechs->getBoardSizeX(); ++x) {
            board[y][x] = ' ';

            if (x == 0 || y == 0 || x == gameMechs->getBoardSizeX() - 1 || y == gameMechs->getBoardSizeY() - 1) {
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
    for (int y = 0; y < gameMechs->getBoardSizeY(); ++y) {
        for (int x = 0; x < gameMechs->getBoardSizeX(); ++x) {
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
    // Print at once
    // cout << "\033[2J\033[1;1H";
    cout << "\033[H" << boardString;

    if (gameMechs->getLoseFlagStatus()) {
        cout << "\033[1;31m" << "You Lost" << "\033[0m" << endl;
    } else {
        cout << endl;
    }

    if (player->getPlayerBody()->getSize() >= 200) {
        cout << "\033[1;39m" << "You Win" << "\033[0m" << endl;
    } else {
        cout << endl;
    }

    if (gameMechs->getExitFlagStatus()) {
        cout << "\033[1;33m" << "Game terminated" << "\033[0m" << endl;
    } else {
        cout << endl;
    }

    cout << endl;

    cout << "Score: \033[1;32m" << gameMechs->getScore() << "\033[0m     " << endl
         << "Body Length: " << player->getPlayerBody()->getSize() << "     " << endl
         << "Use WASD for control of the snake" << "     " << endl
         << "\033[1;34mS: -5 body\033[0m; \033[1;36mE: +10 score\033[0m; \033[1;35mH: +50 Score, +10 body\033[0m" << "     " << endl
         << "Press [Space] to quit." << "     " << endl
         << endl;

    // cout << "debug info: " << "     " << endl
    //      << "t to simulate eating food" << "     " << endl
    //      << "Player Position: ";
    // player->getHearPos()->printobjPos();
    // cout << "     " << endl;
    // cout << "Food Position: ";
    // food->getFoodPos()->printobjPos();
    // cout << "     " << endl;

    // cout << "Body: 'o'; Number of body: " << player->getPlayerBody()->getSize() << " First 5 Position(s): " << "     " << endl;
    // for (int i = 0; i < min(player->getsize(), 5); i++) {
    //     cout << "Body part " << i << ' ';
    //     player->getPlayerBody()->getElement(i).getObjPos()->printobjPos();
    // }
}

void LoopDelay(void) {
    MacUILib_Delay(DELAY_CONST);  // 0.1s delay
    // MacUILib_Delay(500000);
}

void CleanUp(void) {
    // Show the cursor
    cout << "\033[?25h";
    delete gameMechs;
    delete player;
    delete food;
    MacUILib_uninit();
}
