#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include "mesh.h"
#include "texture2d.h"
#include "content.h"

class Game;

struct Crosshair {
    static Game* gameEngine;
    
    Texture2D* texture;

    Crosshair();
    Crosshair(Texture2D* _tex);

    void Draw(ShaderProgram& prog);
};

#endif