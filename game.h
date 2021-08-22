#ifndef GAME_H
#define GAME_H

#include "application.h"

class Game : public Application {
public:
    Game(int w, int h);

    void Init();
    void Update(float deltaTime);
    void Draw();
};

#endif