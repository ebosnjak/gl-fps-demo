#ifndef GAME_H
#define GAME_H

#include "application.h"
#include "shader.h"

class Game : public Application {
public:
    unsigned int shaderProgram;
    unsigned int vao, vbo;

    Game(int w, int h);

    void Init();
    void Update(float deltaTime);
    void Draw();
    void Cleanup();
};

#endif