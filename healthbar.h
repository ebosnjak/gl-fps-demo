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
    float currentValue;

    Healthbar();
    Healthbar(Entity* _owner, glm::vec2 _size, glm::vec3 _fg = glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3 _bg = glm::vec3(1.0f));

    void Update(float deltaTime);
    void Draw(ShaderProgram& prog);
};

struct UI_Healthbar : public Healthbar {
    glm::vec2 position;

    UI_Healthbar();
    UI_Healthbar(Entity* _owner, glm::vec2 _size, glm::vec2 _pos = glm::vec2(0.0f), glm::vec3 _fg = glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3 _bg = glm::vec3(1.0f));

    void Update(float deltaTime);
    void Draw(ShaderProgram& prog);
};

#endif