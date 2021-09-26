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
    prog.SetMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3((float)gameEngine->windowWidth / 2.0f - 20.0f, (float)gameEngine->windowHeight / 2.0f - 20.0f, 1.0f)) *
                          glm::scale(glm::mat4(1.0f), glm::vec3(40.0f, 40.0f, 1.0f)));
    Content::Instance().GetMesh("rectangle_topleft")->Draw(prog);
}