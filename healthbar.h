#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "glfuncs.h"
#include "mathhelper.h"
#include "shader.h"
#include "content.h"

class Entity;
class Game;

struct Healthbar {
    static Game* gameEngine;
    Entity* owner;

    glm::vec2 size;
    glm::vec3 bgColor, fgColor;

    Healthbar();
    Healthbar(Entity* _owner, glm::vec2 _size, glm::vec3 _fg = glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3 _bg = glm::vec3(1.0f));

    void Draw(ShaderProgram& prog);
};

#endif