#ifndef GAME_H
#define GAME_H

#include "application.h"
#include "shader.h"

#include "dependencies/lodepng.h"

#include <iostream>
#include <vector>

class Game : public Application {
public:
    unsigned int vao, vbo;
    ShaderProgram prog;

    Game(int w, int h);

    void Init();
    void Update(float deltaTime);
    void Draw();
    void Cleanup();
};

#endif