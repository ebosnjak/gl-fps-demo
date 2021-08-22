#include "game.h"

bool Game_Start(int w, int h) {
    g_gameEngine = (Game *) malloc(sizeof(Game));

    g_gameEngine->window = GameWindow_Create(1280, 720);
    if (g_gameEngine->window == NULL) {
        return false;
    }

    GameWindow_Run(g_gameEngine->window, Game_Init, Game_Update, Game_Draw);
    GameWindow_Destroy(g_gameEngine->window);

    free(g_gameEngine);
}

void Game_Init() {
    
}

void Game_Update(float deltaTime) {
    if (IsKeyPressed(Key_A)) {
        printf("A pressed\n");
    }
    if (IsKeyReleased(Key_A)) {
        printf("A released\n");
    }
    if (IsButtonPressed(Mouse_Left)) {
        printf("lmb pressed\n");
    }
    if (IsButtonReleased(Mouse_Left)) {
        printf("lmb released\n");
    }
}

void Game_Draw() {
    glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}



bool IsButtonDown(uint8_t button) {
    if (button < 0 || button > 2) 
        return false; 

    return g_gameEngine->window->mouseState & (1 << button);
}

bool IsButtonPressed(uint8_t button) {
    if (button < 0 || button > 2) 
        return false; 

    return (g_gameEngine->window->mouseState & (1 << button)) && !(g_gameEngine->window->mouseState & (1 << (button + 3)));
}

bool IsButtonUp(uint8_t button) {
    if (button < 0 || button > 2)
        return false;
    
    return !(g_gameEngine->window->mouseState & (1 << button));
}

bool IsButtonReleased(uint8_t button) {
    if (button < 0 || button > 2) 
        return false; 

    return !(g_gameEngine->window->mouseState & (1 << button)) && (g_gameEngine->window->mouseState & (1 << (button + 3)));
}

bool IsKeyDown(Keys key) {
    KeyCode kcode = XKeysymToKeycode(g_gameEngine->window->dpy, key);
    return g_gameEngine->window->keyState[kcode / 8] & (1 << (kcode % 8));
}

bool IsKeyPressed(Keys key) {
    KeyCode kcode = XKeysymToKeycode(g_gameEngine->window->dpy, key);
    return (g_gameEngine->window->keyState[kcode / 8] & (1 << (kcode % 8))) && !(g_gameEngine->window->lastKeyState[kcode / 8] & (1 << (kcode % 8)));
}

bool IsKeyUp(Keys key) {
    KeyCode kcode = XKeysymToKeycode(g_gameEngine->window->dpy, key);
    return !(g_gameEngine->window->keyState[kcode / 8] & (1 << (kcode % 8)));
}

bool IsKeyReleased(Keys key) {
    KeyCode kcode = XKeysymToKeycode(g_gameEngine->window->dpy, key);
    return !(g_gameEngine->window->keyState[kcode / 8] & (1 << (kcode % 8))) && (g_gameEngine->window->lastKeyState[kcode / 8] & (1 << (kcode % 8)));
}