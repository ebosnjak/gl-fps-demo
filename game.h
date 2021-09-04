#ifndef GAME_H
#define GAME_H

#include "application.h"
#include "shader.h"
#include "texture2d.h"
#include "mathhelper.h"
#include "mesh.h"
#include "content.h"
#include "camera.h"

#include <iostream>
#include <vector>

#include <iomanip>

class Game : public Application {
public:
    Matrix modelMat;
    Mesh testMesh;
    Mesh backpackMesh;
    Mesh floorMesh;
    Mesh cubeMesh;

    Camera camera;
    ShaderProgram prog;

    Game(int w, int h);

    void Init();
    void Update(float deltaTime);
    void Draw();
    void Cleanup();
};

#endif