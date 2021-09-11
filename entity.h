#ifndef ENTITY_H
#define ENTITY_H

#include "glfuncs.h"
#include "mesh.h"
#include "mathhelper.h"
#include "camera.h"

class Game;

class Entity {
protected:
    Matrix modelMatrix;
    Vector3 position;
    glm::quat orientation;
    float scale;

    Vector3 up;
    Vector3 direction;
    Vector3 right;

    void ComputeMatrix();

public:
    static Game* gameEngine;
    
    Mesh* mesh;

    Vector3 linearVelocity;
    Box customAABB;
    bool obeysGravity;
    bool onGround;
    bool isSolid;
    
    Entity();
    Entity(Mesh* _mesh, Vector3 _position = Vector3(), glm::quat _orientation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)), float _scale = 1.0f);

    void Update(float deltaTime);
    void Draw(ShaderProgram& prog);

    Box GetAABB();

    Vector3 GetPosition();
    void SetPosition(const Vector3& pos);
    void Move(const Vector3& delta);

    glm::quat GetOrientation();
    Vector3 GetOrientationEuler();
    void SetOrientation(const glm::quat& q);
    void SetOrientation(const Vector3& v);
    void SetOrientation(const Vector3& axis, float angle);
    void Rotate(const glm::quat& q);
    void Rotate(const Vector3& axis, float angle);

    float GetScale();
    void SetScale(float sc);
};

class Player : public Entity {
private:
    float yaw, pitch;
    float pitchLimit;

public:
    Camera camera;

    Player(Vector3 _position = Vector3(), glm::quat _rotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)), float _scale = 1.0f);

    void Update(float deltaTime);
    void Draw(ShaderProgram& prog);
};

#endif