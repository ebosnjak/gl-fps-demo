#ifndef GAME_H
#define GAME_H

#include "window.h"

typedef struct {
    GameWindow *window;
} Game;

static Game *g_gameEngine;

bool Game_Start(int w, int h);
void Game_Init();
void Game_Update(float deltaTime);
void Game_Draw();

bool IsButtonDown(uint8_t button);
bool IsButtonUp(uint8_t button);
bool IsButtonPressed(uint8_t button);
bool IsButtonReleased(uint8_t button);

bool IsKeyDown(Keys key);
bool IsKeyUp(Keys key);
bool IsKeyPressed(Keys key);
bool IsKeyReleased(Keys key);

#endif