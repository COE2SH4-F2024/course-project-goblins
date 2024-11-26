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

    while (gameMechs->getExitFlagStatus()) {
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
    food = new Food();

    gameMechs->incrementScore();
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

    if (gameMechs->getLoseFlagStatus()) {
        gameMechs->setExitTrue();
    }
}

void DrawScreen(void) {
    MacUILib_clearScreen();

    // Draw the board
    for (int y = 0; y < gameMechs->getBoardSizeY(); ++y) {
        for (int x = 0; x < gameMechs->getBoardSizeX(); ++x) {
            if (player->getPlayerPos().pos->x == x && player->getPlayerPos().pos->y == y) {
                cout << player->getPlayerPos().getSymbol();
            } else if (food->getFoodPos().getObjPos().pos->x == x && food->getFoodPos().getObjPos().pos->x == y) {
                cout << food->getFoodPos().getSymbol();
            } else {
                cout << ' ';
            }
        }
        cout << endl;
    }

    cout << "Score: " << gameMechs->getScore() << endl;
    cout << "Press Q to quit." << endl;
}

void LoopDelay(void) {
    MacUILib_Delay(DELAY_CONST);  // 0.1s delay
}

void CleanUp(void) {
    MacUILib_clearScreen();

    MacUILib_uninit();
}
