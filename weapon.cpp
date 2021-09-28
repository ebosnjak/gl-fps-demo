#include "weapon.h"
#include "game.h"

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

    ads = false;
    crosshair = Crosshair();

    maxSpreadDegrees = 0.0f;
    maxSprintSpreadDegrees = 0.0f;
    recoilRecoveryTime = 0.35f;
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
    reloadTime = 1.4f;
    rof = 10.0f;

    ammo = 25;
    maxAmmo = 25;

    isFiring = false;
    isReloading = false;

    defaultPosition = glm::vec3(0.7f, -0.4f, -1.4f);
    posHip = glm::vec3(0.7f, -0.4f, -1.4f);
    posADS = glm::vec3(0.0f, -0.2f, -1.0f);

    defaultOrientation = glm::angleAxis(glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    ads = false;
    crosshair = Crosshair(Content::Instance().GetTexture("crosshair"));

    maxSpreadDegrees = 4.0f;
    maxSprintSpreadDegrees = 8.0f;
    recoilRecoveryTime = 0.17f;
}

void Weapon_SMG::Update(float deltaTime) {
    if (isReloading) {
        if (!anim.empty()) {
            anim.front().Update(deltaTime);
            position = anim.front().position;
            orientation = anim.front().quat * defaultOrientation;

            if (anim.front().finished) {
                anim.pop();
            }
        }

        reloadingTimer += deltaTime;
        if (reloadingTimer >= reloadTime) {
            position = posHip;
            orientation = defaultOrientation;
            ads = false;

            isReloading = false;
            reloadingTimer = 0.0f;
            ammo = maxAmmo;
            while (!anim.empty()) {
                anim.pop();
            }
        }
    }
    else {
        if (animADS.started && !animADS.finished) {
            animADS.Update(deltaTime);
            defaultPosition = animADS.position;

            if (animADS.finished && defaultPosition == posADS) {
                ads = true;
            }
        }

        if (!anim.empty() && isFiring) {
            anim.front().Update(deltaTime);
            position = defaultPosition + anim.front().position;
            orientation = anim.front().quat * defaultOrientation;

            if (anim.front().finished) {
                anim.pop();
            }
        }
        else if (!anim.empty() && owner->isSprinting) {
            
        }
        else {
            position = defaultPosition;
        }
    }

    shootingTimer += deltaTime;

    Entity::Update(deltaTime);
}

void Weapon_SMG::Draw(ShaderProgram& prog) {
    // ...

    Entity::Draw(prog);
}

void Weapon_SMG::Draw(ShaderProgram& prog, ShaderProgram& progCrosshair) {
    if (!ads) {
        crosshair.Draw(progCrosshair);
    }

    Entity::Draw(prog);
}

void Weapon_SMG::OnPrimaryFirePressed() {

}

void Weapon_SMG::OnPrimaryFireDown() {
    if (ammo == 0) {
        // auto reload if empty
        if (!isReloading) {
            OnReload();
        }
        return;
    }

    if (isReloading) {
        /* don't reload cancel for now
        isReloading = false;
        while (!anim.empty()) {
            anim.pop();
        while (!anim.empty()) {
        }

        position = posHip;
        orientation = defaultOrientation; */

        return;
    }

    if (shootingTimer >= 1.0f / rof) {
        glm::vec3 dir = glm::normalize(owner->camera.Direction());
        if (!ads) {
            float downtime = shootingTimer - 1.0f / rof;
            if (downtime > recoilRecoveryTime) {
                downtime = recoilRecoveryTime;
            }

            float spread = glm::mix((owner->isSprinting ? maxSprintSpreadDegrees : maxSpreadDegrees), 0.5f, downtime / recoilRecoveryTime);

            glm::vec3 axis = glm::normalize(glm::cross(
                                dir, 
                                glm::vec3((float)(rand() % 100) * 2.0f / 100.0f - 1.0f, 
                                          (float)(rand() % 100) * 2.0f / 100.0f - 1.0f, 
                                          (float)(rand() % 100) * 2.0f / 100.0f - 1.0f)
                            ));

            float angle = glm::radians((float)(rand() % 100) * 2.0f * spread / 100.0f - spread);
            dir = glm::angleAxis(angle, axis) * dir;
        }

        glm::vec3 pos = owner->camera.position + 2.0f * dir;
        gameEngine->projectiles.push_back(Projectile(pos, 50.0f, dir)); // usual speed is 50.0f
        --ammo;
        anim.push(Animation(0.05f, glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 0.08f),
                            glm::angleAxis(glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::angleAxis(glm::radians(3.0f), glm::vec3(1.0f, 0.0f, 0.0f))));

        anim.push(Animation(0.04f, glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, -0.08f), 
                            glm::angleAxis(glm::radians(3.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::angleAxis(glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f))));

        isFiring = true;
        shootingTimer = 0.0f;
    }
}

void Weapon_SMG::OnPrimaryFireReleased() {
    if (isReloading) {
        return;
    }

    isFiring = false;
    if (!animADS.started || animADS.finished) {
        SetPosition(defaultPosition, 0.05f);
    }
    orientation = defaultOrientation;
}

void Weapon_SMG::OnPrimaryFireUp() {
    
}

void Weapon_SMG::OnSecondaryFirePressed() {
    if (isReloading) {
        return;
    }

    animADS = Animation(0.15f, defaultPosition, posADS);
}

void Weapon_SMG::OnSecondaryFireDown() {

}

void Weapon_SMG::OnSecondaryFireReleased() {
    if (isReloading) {
        return;
    }

    ads = false;
    animADS = Animation(0.15f, defaultPosition, posHip);
}

void Weapon_SMG::OnSecondaryFireUp() {
    
}

void Weapon_SMG::OnReload() {
    if (ammo == maxAmmo || isReloading) {
        return;
    }

    while (!anim.empty()) {
        anim.pop();
    }
    animADS = Animation();

    isReloading = true;
    reloadingTimer = 0.0f;

    if (!ads) {
        position = posHip;
        defaultPosition = posHip;

        anim.push(Animation(0.3f * reloadTime, posHip, posHip + glm::vec3(-0.7f, -0.4f, 0.0f), 
                            glm::angleAxis(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)), glm::angleAxis(glm::radians(70.0f), glm::vec3(0.0f, 1.0f, 0.0f))));
        anim.push(Animation(0.4f * reloadTime, posHip + glm::vec3(-0.7f, -0.4f, 0.0f), posHip + glm::vec3(-0.7f, -0.4f, 0.0f), 
                            glm::angleAxis(glm::radians(70.0f), glm::vec3(0.0f, 1.0f, 0.0f)), glm::angleAxis(glm::radians(70.0f), glm::vec3(0.0f, 1.0f, 0.0f))));
        anim.push(Animation(0.3f * reloadTime, posHip + glm::vec3(-0.7f, -0.4f, 0.0f), posHip, 
                            glm::angleAxis(glm::radians(70.0f), glm::vec3(0.0f, 1.0f, 0.0f)), glm::angleAxis(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f))));
    }
    else {
        ads = false;
        position = posHip;
        defaultPosition = posHip;

        anim.push(Animation(0.3f * reloadTime, posADS, posADS + glm::vec3(0.0f, -0.6f, -0.4f), 
                            glm::angleAxis(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)), glm::angleAxis(glm::radians(70.0f), glm::vec3(0.0f, 1.0f, 0.0f))));
        anim.push(Animation(0.4f * reloadTime, posADS + glm::vec3(0.0f, -0.6f, -0.4f), posADS + glm::vec3(0.0f, -0.6f, -0.4f), 
                            glm::angleAxis(glm::radians(70.0f), glm::vec3(0.0f, 1.0f, 0.0f)), glm::angleAxis(glm::radians(70.0f), glm::vec3(0.0f, 1.0f, 0.0f))));
        anim.push(Animation(0.3f * reloadTime, posADS + glm::vec3(0.0f, -0.6f, -0.4f), posHip, 
                            glm::angleAxis(glm::radians(70.0f), glm::vec3(0.0f, 1.0f, 0.0f)), glm::angleAxis(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f))));
    }
}

void Weapon_SMG::OnOwnerSprintStart() {
    std::cout << "anim start" << std::endl;
}

void Weapon_SMG::OnOwnerSprintEnd() {
    std::cout << "anim end" << std::endl;
}