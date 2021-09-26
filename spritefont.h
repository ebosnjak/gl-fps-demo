#ifndef SPRITEFONT_H
#define SPRITEFONT_H

#include "texture2d.h"
#include "content.h"

struct SpriteFont {
    Texture2D* sheet;

    SpriteFont();
    SpriteFont(Texture2D* _sheet);

    void DrawString(ShaderProgram& prog, const std::string& text, glm::vec2 position, glm::vec2 scale, glm::vec3 color = glm::vec3(0.0f));
};

#endif