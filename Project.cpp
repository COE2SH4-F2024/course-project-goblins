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

    food->generateFood(player->getPlayerBody());

    MacUILib_Delay(1500000);
    //  gameMechs->incrementScore();
    cout << "\033[2J\033[1;1H";
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

    if (player->getHearPos()->isPosEqual(food->getFoodPos())) {
        // if player ate food
        gameMechs->incrementScore();
        // player->increasePlayerBody();
        player->moveBody();
        food->generateFood(player->getPlayerBody());

    } else if (player->getsize() > 0) {
        // if player did not ate food
        // player->increasePlayerBody();
        player->moveBody();
        player->cuttail();
    }

    player->movePlayer();

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
            for (int i = 0; i < player->getsize(); i++) {
                if (y == player->getPlayerBody()->getElement(i).getObjPos()->pos->y && x == player->getPlayerBody()->getElement(i).getObjPos()->pos->x) {
                    board[y][x] = 'o';
                }
            }
            if (x == player->getHearPos()->pos->x && y == player->getHearPos()->pos->y) {
                board[y][x] = player->getHearPos()->symbol;
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

    cout << endl;

    cout << "Score: " << gameMechs->getScore() << endl;
    cout << "Press [Space] to quit." << endl;
    cout << endl;

    cout << "debug info: " << endl;
    cout << "Player: '@'; Position: ";
    player->getHearPos()->printobjPos();
    cout << endl;
    cout << "Food: '*'; Position: ";
    food->getFoodPos()->printobjPos();
    cout << endl;

    cout << "Body: 'o'; Number of body: " << player->getPlayerBody()->getSize() << " Position(s): " << endl;
    for (int i = 0; i < player->getsize(); i++) {
        cout << "Body part " << i;
        cout << " x: " << player->getPlayerBody()->getElement(i).getObjPos()->pos->x << " y: " << player->getPlayerBody()->getElement(i).getObjPos()->pos->y;
        cout << endl;
    }
}

void LoopDelay(void) {
    MacUILib_Delay(DELAY_CONST);  // 0.1s delay
}

void CleanUp(void) {
    delete gameMechs;
    delete player;
    delete food;
    MacUILib_uninit();
}
