#include "weapon.h"

Weapon::Weapon() {
    mesh = nullptr;
    position = glm::vec3(0.0f);
    orientation = glm::quat(glm::vec3(0.0f));
    scale = 1.0f;

    obeysGravity = false;
    onGround = false;
    isSolid = false;

    moveDuration = 0.0f;
    lastPosition = position;
    nextPosition = position;

    linearVelocity = glm::vec3(0.0f);

    shootingTimer = 0.0f;
    reloadingTimer = 0.0f;
    reloadTime = 0.0f;
    rof = 1.0f;

    ammo = 0;
    maxAmmo = 0;
}

Weapon_SMG::Weapon_SMG() {

}

Weapon_SMG::Weapon_SMG(Mesh* _mesh, glm::vec3 _position, glm::quat _orientation, float _scale) {
    mesh = _mesh;
    position = _position;
    orientation = _orientation;
    scale = _scale;

    obeysGravity = false;
    onGround = false;
    isSolid = false;

    moveDuration = 0.0f;
    lastPosition = position;
    nextPosition = position;

    linearVelocity = glm::vec3(0.0f);

    shootingTimer = 0.0f;
    reloadingTimer = 0.0f;
    reloadTime = 2.0f;
    rof = 10.0f;

    ammo = 25;
    maxAmmo = 25;
}

void Weapon_SMG::Update(float deltaTime) {
    // ...

    Entity::Update(deltaTime);
}

void Weapon_SMG::Draw(ShaderProgram& prog) {
    // ...

    Entity::Draw(prog);
}

void Weapon_SMG::OnPrimaryFirePressed() {

}

void Weapon_SMG::OnPrimaryFireReleased() {

}

void Weapon_SMG::OnSecondaryFirePressed() {
    SetPosition(glm::vec3(0.0f, -0.2f, -1.0f), 0.15f);
}

void Weapon_SMG::OnSecondaryFireReleased() {
    SetPosition(glm::vec3(0.7f, -0.4f, -1.4f), 0.15f);
}

void Weapon_SMG::OnReload() {

}