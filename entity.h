#ifndef ENTITY_H
#define ENTITY_H

#include "glfuncs.h"
#include "mesh.h"
#include "mathhelper.h"
#include "camera.h"
#include "animation.h"
#include "healthbar.h"

#include <queue>

class Game;
class Weapon;

enum class EntityType {
    Generic,
    Player,
    Enemy,
    Projectile,
    World
};

class Entity {
protected:
    glm::mat4 modelMatrix;
    glm::vec3 position;
    glm::quat orientation;
    float scale;

    glm::vec3 lastPosition;
    glm::vec3 nextPosition;
    float timer, moveDuration;

    glm::vec3 up;
    glm::vec3 direction;
    glm::vec3 right;

    void ComputeMatrix();

public:
    static Game* gameEngine;
    
    Mesh* mesh;

    glm::vec3 linearVelocity;
    Box customAABB;
    bool obeysGravity;
    bool onGround;
    bool isSolid;
    bool isAlive;
    
    bool isSprinting;
    bool wasSprinting;

    bool useHpBar;
    Healthbar hpBar;
    int health, maxHealth;
    
    glm::vec3 aimDirection;
    glm::vec3 aimPosition;

    EntityType type;
    
    Entity();
    Entity(Mesh* _mesh, glm::vec3 _position = glm::vec3(0.0f), glm::quat _orientation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)), float _scale = 1.0f);

    void Update(float deltaTime);
    void Draw(ShaderProgram& prog);

    Box GetAABB();

    glm::vec3 GetPosition();
    void SetPosition(const glm::vec3& pos, float duration = 0.0f);
    void Move(const glm::vec3& delta, float duration = 0.0f);

    glm::quat GetOrientation();
    glm::vec3 GetOrientationEuler();
    void SetOrientation(const glm::quat& q);
    void SetOrientation(const glm::vec3& v);
    void SetOrientation(const glm::vec3& axis, float angle);
    void Rotate(const glm::quat& q);
    void Rotate(const glm::vec3& axis, float angle);

    float GetScale();
    void SetScale(float sc);

    glm::mat4 GetModelMatrix();
};

class Player : public Entity {
private:
    float yaw, pitch;
    float pitchLimit;

public:
    UI_Healthbar hpBarUI;

    Camera camera;
    Weapon* currentWeapon;

    Player(const Player& player);
    Player(Player&& player);
    Player(glm::vec3 _position = glm::vec3(0.0f), glm::quat _orientation = glm::quat(glm::vec3(0.0f)), float _scale = 1.0f);
    ~Player();

    Player& operator=(const Player& player);
    Player& operator=(Player&& player);

    void Update(float deltaTime);
    void Draw(ShaderProgram& prog, ShaderProgram& prog2D);
};

class Enemy : public Entity {
public:
    Weapon* currentWeapon;

    Enemy();
    Enemy(const Enemy& enemy);
    Enemy(Enemy&& enemy);
    Enemy(Mesh* _mesh, glm::vec3 _position = glm::vec3(0.0f), glm::quat _orientation = glm::quat(glm::vec3(0.0f)), float _scale = 1.0f);

    ~Enemy();

    Enemy& operator=(const Enemy& enemy);
    Enemy& operator=(Enemy&& enemy);

    void Update(float deltaTime);
    void Draw(ShaderProgram& prog);
};

#endif