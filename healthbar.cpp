#include "healthbar.h"
#include "entity.h"
#include "game.h"

Game* Healthbar::gameEngine = nullptr;

Healthbar::Healthbar() {
    owner = nullptr;

    size = glm::vec2(1.0f, 0.2f);
    bgColor = glm::vec3(1.0f, 1.0f, 1.0f);
    fgColor = glm::vec3(1.0f, 0.0f, 0.0f);
}

Healthbar::Healthbar(Entity* _owner, glm::vec2 _size, glm::vec3 _fg, glm::vec3 _bg) {
    owner = _owner;

    size = _size;
    fgColor = _fg;
    bgColor = _bg;
}

void Healthbar::Draw(ShaderProgram& prog) {
    if (owner == nullptr || !owner->isAlive) {
        return;
    }

    glm::vec4 tmp = gameEngine->player.camera.LookAt() * glm::vec4(owner->GetPosition() + glm::vec3(0.0f, owner->GetAABB().size.y / 2.0f + 0.7f, 0.0f), 1.0f);
    glm::vec3 position(tmp.x, tmp.y, tmp.z);
    glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), position) * 
                         glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

    prog.SetInt("isViewmodel", 1);
    prog.SetMat4("model", modelMat);
    Content::Instance().GetMesh("rectangle")->color = bgColor;
    Content::Instance().GetMesh("rectangle")->Draw(prog);

    float width = size.x * (float)owner->health / (float)owner->maxHealth;
    modelMat = glm::translate(glm::mat4(1.0f), position + glm::vec3(-0.5f * (size.x - width), 0.0f, 0.007f)) * 
               glm::scale(glm::mat4(1.0f), glm::vec3(width, size.y, 1.0f));

    prog.SetMat4("model", modelMat);
    Content::Instance().GetMesh("rectangle")->color = fgColor;
    Content::Instance().GetMesh("rectangle")->Draw(prog);
    prog.SetInt("isViewmodel", 0);
}
