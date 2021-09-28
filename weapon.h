#ifndef WEAPON_H
#define WEAPON_H

#include "entity.h"
#include "projectile.h"
#include "crosshair.h"

#include <cstdlib>

class Player;

class Weapon : public Entity {
protected:
    float shootingTimer;
    float reloadingTimer;
    bool isFiring;
    bool isReloading;

public:
    bool ads;
    Crosshair crosshair;

    Player* owner;

    glm::vec3 defaultPosition;

    int ammo, maxAmmo;
    float reloadTime;
    float rof;

    float maxSpreadDegrees;
    float maxSprintSpreadDegrees;
    float recoilRecoveryTime;

    Weapon();

    virtual void Update(float deltaTime) = 0;
    virtual void Draw(ShaderProgram& prog) = 0;
    virtual void Draw(ShaderProgram& prog, ShaderProgram& progCrosshair) = 0;

    virtual void OnPrimaryFirePressed() = 0;
    virtual void OnPrimaryFireDown() = 0;
    virtual void OnPrimaryFireReleased() = 0;
    virtual void OnPrimaryFireUp() = 0;

    virtual void OnSecondaryFirePressed() = 0;
    virtual void OnSecondaryFireDown() = 0;
    virtual void OnSecondaryFireReleased() = 0;
    virtual void OnSecondaryFireUp() = 0;

    virtual void OnReload() = 0;

    virtual void OnOwnerSprintStart() = 0;
    virtual void OnOwnerSprintEnd() = 0;
};

class Weapon_SMG : public Weapon {
private:
    std::queue< Animation > anim;
    Animation animADS;

    glm::vec3 posHip, posADS;
    glm::quat defaultOrientation;

public:
    Weapon_SMG();
    Weapon_SMG(Mesh* _mesh, glm::vec3 _position = glm::vec3(0.0f), glm::quat _orientation = glm::quat(glm::vec3(0.0f)), float _scale = 1.0f);

    void Update(float deltaTime);
    void Draw(ShaderProgram& prog);
    void Draw(ShaderProgram& prog, ShaderProgram& progCrosshair);

    void OnPrimaryFirePressed();
    void OnPrimaryFireDown();
    void OnPrimaryFireReleased();
    void OnPrimaryFireUp();

    void OnSecondaryFirePressed();
    void OnSecondaryFireDown();
    void OnSecondaryFireReleased();
    void OnSecondaryFireUp();
    
    void OnReload();

    void OnOwnerSprintStart();
    void OnOwnerSprintEnd();
};

#endif