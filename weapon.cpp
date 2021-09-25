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

    isFiring = false;
    isReloading = false;

    defaultPosition = glm::vec3(0.0f);
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

    isFiring = false;
    isReloading = false;

    defaultPosition = glm::vec3(0.7f, -0.4f, -1.4f);
    posHip = glm::vec3(0.7f, -0.4f, -1.4f);
    posADS = glm::vec3(0.0f, -0.2f, -1.0f);

    defaultOrientation = glm::angleAxis(glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Weapon_SMG::Update(float deltaTime) {
    if (animADS.started && !animADS.finished) {
        animADS.Update(deltaTime);
        defaultPosition = animADS.position;
    }

    if (!anim.empty() && isFiring) {
        anim.front().Update(deltaTime);
        position = defaultPosition + anim.front().position;
        orientation = anim.front().quat * defaultOrientation;

        if (anim.front().finished) {
            anim.pop();
        }
    }
    else {
        position = defaultPosition;
    }

    shootingTimer += deltaTime;

    Entity::Update(deltaTime);
}

void Weapon_SMG::Draw(ShaderProgram& prog) {
    // ...

    Entity::Draw(prog);
}

void Weapon_SMG::OnPrimaryFirePressed() {

}

void Weapon_SMG::OnPrimaryFireDown() {
    if (shootingTimer >= 1.0f / rof) {
        std::cout << "boom" << std::endl;
        anim.push(Animation(0.05f, glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 0.08f),
                            glm::angleAxis(glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::angleAxis(glm::radians(3.0f), glm::vec3(1.0f, 0.0f, 0.0f))));

        anim.push(Animation(0.04f, glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, -0.08f), 
                            glm::angleAxis(glm::radians(3.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::angleAxis(glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f))));

        isFiring = true;
        shootingTimer = 0.0f;
    }
}

void Weapon_SMG::OnPrimaryFireReleased() {
    isFiring = false;
    if (!animADS.started || animADS.finished) {
        SetPosition(defaultPosition, 0.05f);
    }
    orientation = defaultOrientation;
}

void Weapon_SMG::OnPrimaryFireUp() {
    
}

void Weapon_SMG::OnSecondaryFirePressed() {
    //defaultPosition = glm::vec3(0.0f, -0.2f, -1.0f);
    //SetPosition(glm::vec3(0.0f, -0.2f, -1.0f), 0.15f);

    animADS = Animation(0.15f, posHip, posADS);
}

void Weapon_SMG::OnSecondaryFireDown() {

}

void Weapon_SMG::OnSecondaryFireReleased() {
    //defaultPosition = glm::vec3(0.7f, -0.4f, -1.4f);
    //SetPosition(glm::vec3(0.7f, -0.4f, -1.4f), 0.15f);

    animADS = Animation(0.15f, posADS, posHip);
}

void Weapon_SMG::OnSecondaryFireUp() {
    
}

void Weapon_SMG::OnReload() {

}