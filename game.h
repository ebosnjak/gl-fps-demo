#ifndef GAME_H
#define GAME_H

#include "application.h"
#include "shader.h"
#include "texture2d.h"
#include "mathhelper.h"
#include "mesh.h"
#include "content.h"

#include <iostream>
#include <vector>

#include <iomanip>

class Game : public Application {
public:
    Matrix modelMat;
    Mesh testMesh;
    Mesh backpackMesh;
    ShaderProgram prog;

    Vector3 cameraPos, cameraDirection, cameraUp, cameraRight;
    float cameraYaw, cameraPitch;

    Game(int w, int h);

    void Init();
    void Update(float deltaTime);
    void Draw();
    void Cleanup();
};

#endif