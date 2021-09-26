#include "crosshair.h"
#include "game.h"

Game* Crosshair::gameEngine = nullptr;

Crosshair::Crosshair() {
    texture = nullptr;
}

Crosshair::Crosshair(Texture2D* _texture) {
    texture = _texture;
}

void Crosshair::Draw(ShaderProgram& prog) {
    if (texture == nullptr) {
        return;
    }

    prog.Use();
    prog.SetInt("tex", 0);
    glActiveTexture(GL_TEXTURE0);
    texture->Bind();
    prog.SetMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.05f, 0.05f, 1.0f)));
    Content::Instance().GetMesh("rectangle")->Draw(prog);
}