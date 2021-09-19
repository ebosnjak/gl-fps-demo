#ifndef ENTITY_H
#define ENTITY_H

#include "glfuncs.h"
#include "mesh.h"
#include "mathhelper.h"
#include "camera.h"

class Game;

class Entity {
protected:
    glm::mat4 modelMatrix;
    glm::vec3 position;
    glm::quat orientation;
    float scale;

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
    
    Entity();
    Entity(Mesh* _mesh, glm::vec3 _position = glm::vec3(), glm::quat _orientation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)), float _scale = 1.0f);

    void Update(float deltaTime);
    void Draw(ShaderProgram& prog);

    Box GetAABB();

    glm::vec3 GetPosition();
    void SetPosition(const glm::vec3& pos);
    void Move(const glm::vec3& delta);

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
    Camera camera;

    Player(glm::vec3 _position = glm::vec3(), glm::quat _orientation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)), float _scale = 1.0f);

    void Update(float deltaTime);
    void Draw(ShaderProgram& prog);
};

#endif