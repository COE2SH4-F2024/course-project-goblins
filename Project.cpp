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
objPos* printPointer;

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
    printPointer = new objPos;

    food->generateFood(player->getPlayerBody());

    // MacUILib_Delay(2000000);
    //  gameMechs->incrementScore();
    // MacUILib_clearScreen();
}

void GetInput(void) {
    if (MacUILib_hasChar()) {
        char input = MacUILib_getChar();
        gameMechs->setInput(input);
    }
}

void RunLogic(void) {
    if (gameMechs->getInput() == ' ') {
        gameMechs->setExitTrue();
    }
    player->updatePlayerDir();
    player->movePlayer();
    if (player->getPlayerPos()->isPosEqual(food->getFoodPos())) {
        gameMechs->incrementScore();
        player->increasePlayerBody();
        // player->moveBodyincrease();
        //  food->generateFood(player->getPlayerBody());
    }  // else {
       //  player->increasePlayerBody();
       //  player->moveBody();
    // }

    if (gameMechs->getLoseFlagStatus()) {
        gameMechs->setExitTrue();
    }
    gameMechs->clearInput();
}

void DrawScreen(void) {
    // MacUILib_clearScreen();
    cout << "\033[2J\033[1;1H";
    char board[15][30];

    // Draw the board
    for (int y = 0; y < gameMechs->getBoardSizeY(); ++y) {
        for (int x = 0; x < gameMechs->getBoardSizeX(); ++x) {
            board[y][x] = ' ';

            if (x == 0 || y == 0 || x == gameMechs->getBoardSizeX() - 1 || y == gameMechs->getBoardSizeY() - 1) {
                board[y][x] = '#';
            }
            // for (int i = 0; i < player->getsize(); i++) {
            // if (y == player->getPlayerBody()->getElement(i).getObjPos()->pos->y && x == player->getPlayerBody()->getElement(i).getObjPos()->pos->x) {
            // board[y][x] = player->getPlayerBody()->getElement(i).getObjPos()->symbol;
            //}
            //}
            if (x == player->getPlayerPos()->pos->x && y == player->getPlayerPos()->pos->y) {
                board[y][x] = player->getPlayerPos()->symbol;
            }
            if (y == food->getFoodPos()->pos->y && x == food->getFoodPos()->pos->x) {
                board[y][x] = food->getFoodPos()->symbol;
            }
        }
    }
    for (int y = 0; y < gameMechs->getBoardSizeY(); ++y) {
        for (int x = 0; x < gameMechs->getBoardSizeX(); ++x) {
            cout << board[y][x];
        }
        cout << endl;
    }

    cout << "Food location: " << food->getFoodPos()->getObjPos()->pos->x << ' ' << food->getFoodPos()->getObjPos()->pos->y << endl;
    cout << "Score: " << gameMechs->getScore() << endl;
    cout << "Press [Space] to quit." << endl;
}

void LoopDelay(void) {
    MacUILib_Delay(DELAY_CONST);  // 0.1s delay
}

void CleanUp(void) {
    delete gameMechs;
    delete player;
    delete food;
    delete printPointer;
    MacUILib_uninit();
}
