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
    Vector3 rotation;   // euler angles
    float scale;

    Vector3 up;
    Vector3 direction;
    Vector3 right;

    void ComputeMatrix();

public:
    static Game* gameEngine;
    
    Mesh* mesh;

    Vector3 linearVelocity;

    Box aabb;
    
    Entity();
    Entity(Mesh* _mesh, Vector3 _position = Vector3(), Vector3 _rotation = Vector3(), float _scale = 1.0f);

    void Update(float deltaTime);
    void Draw(ShaderProgram& prog);

    Box GetAABB();

    Vector3 GetPosition();
    void SetPosition(const Vector3& pos);
    void Move(const Vector3& delta);

    Vector3 GetRotation();
    void SetRotation(const Vector3& rot);
    void Rotate(const Vector3& delta);

    float GetScale();
    void SetScale(float sc);
};

class Player : public Entity {
public:
    Camera camera;

    Player(Vector3 _position = Vector3(), Vector3 _rotation = Vector3(), float _scale = 1.0f);

    void Update(float deltaTime);
    void Draw(ShaderProgram& prog);
};

#endif