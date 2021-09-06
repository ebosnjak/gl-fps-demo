#ifndef GAME_H
#define GAME_H

#include "application.h"
#include "shader.h"
#include "texture2d.h"
#include "mathhelper.h"
#include "mesh.h"
#include "content.h"
#include "camera.h"
#include "entity.h"

#include <iostream>
#include <vector>

#include <iomanip>

class Game : public Application {
public:
    Entity test;

    Camera camera;
    ShaderProgram prog;

    Game(int w, int h);

    void Init();
    void Update(float deltaTime);
    void Draw();
    void Cleanup();

    static void DrawBox(ShaderProgram& p, const Box& b);
};

#endif