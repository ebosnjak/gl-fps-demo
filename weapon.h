#ifndef WEAPON_H
#define WEAPON_H

#include "entity.h"

class Weapon : public Entity {
protected:
    float shootingTimer;
    float reloadingTimer;

public:
    Player* owner;
    
    int ammo, maxAmmo;
    float reloadTime;
    float rof;

    Weapon();

    virtual void Update(float deltaTime) = 0;
    virtual void Draw(ShaderProgram& prog) = 0;
    virtual void OnPrimaryFirePressed() = 0;
    virtual void OnPrimaryFireReleased() = 0;
    virtual void OnSecondaryFirePressed() = 0;
    virtual void OnSecondaryFireReleased() = 0;
    virtual void OnReload() = 0;
};

class Weapon_SMG : public Weapon {
public:
    Weapon_SMG();
    Weapon_SMG(Mesh* _mesh, glm::vec3 _position = glm::vec3(0.0f), glm::quat _orientation = glm::quat(glm::vec3(0.0f)), float _scale = 1.0f);

    void Update(float deltaTime);
    void Draw(ShaderProgram& prog);
    void OnPrimaryFirePressed();
    void OnPrimaryFireReleased();
    void OnSecondaryFirePressed();
    void OnSecondaryFireReleased();
    void OnReload();
};

#endif