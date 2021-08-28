#ifndef GAME_H
#define GAME_H

#include "application.h"
#include "shader.h"
#include "texture2d.h"
#include "mathhelper.h"

#include <iostream>
#include <vector>

class Game : public Application {
public:
    unsigned int vao, vbo;
    ShaderProgram prog;
    Texture2D tex;

    float angle;

    Vector3 cameraPos, cameraDirection;

    Game(int w, int h);

    void Init();
    void Update(float deltaTime);
    void Draw();
    void Cleanup();
};

#endif