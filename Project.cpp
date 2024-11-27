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
    MacUILib_clearScreen();

    gameMechs = new GameMechs(30, 15);
    player = new Player(gameMechs);
    food = new Food(gameMechs);
    printPointer = new objPos;

    food->generateFood(player->getPlayerBody());

    MacUILib_Delay(2000000);
    // gameMechs->incrementScore();
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

    if (player->getPlayerPos()->isPosEqual(food->getFoodPos())) {
        gameMechs->incrementScore();
        player->increasePlayerBody();
        food->generateFood(player->getPlayerBody());
    }

    player->updatePlayerDir();
    player->movePlayer();

    if (gameMechs->getLoseFlagStatus()) {
        gameMechs->setExitTrue();
    }
    gameMechs->clearInput();
}

void DrawScreen(void) {
    MacUILib_clearScreen();

    // Draw the board
    for (int y = 0; y < gameMechs->getBoardSizeY(); ++y) {
        for (int x = 0; x < gameMechs->getBoardSizeX(); ++x) {
            if (x == 0 || y == 0 || x == gameMechs->getBoardSizeX() - 1 || y == gameMechs->getBoardSizeY() - 1) {
                cout << '#';
            } else {
                printPointer->setObjPos(x, y);
                char symbol[] = {
                    player->getPlayerPos()->getSymbolIfPosEqual(printPointer->getObjPos()), food->getFoodPos()->getSymbolIfPosEqual(printPointer->getObjPos())};
                bool flag = 1;
                char draw = ' ';
                for (int i = 0; i < 2; ++i) {
                    if (symbol[i] != 0) {
                        draw = symbol[i];
                    }
                }
                cout << draw;
            }
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
