#include "entity.h"

Entity::Entity() {
    scale = 1.0f;
}

Entity::Entity(Mesh* _mesh, Vector3 _position, Vector3 _rotation, float _scale) {
    mesh = _mesh;
    position = _position;
    rotation = _rotation;
    scale = _scale;
}

void Entity::Update(float deltaTime) {
    
}

void Entity::Draw(ShaderProgram& prog) {
    prog.Use();
    prog.SetMat4("model", modelMatrix);
    mesh->Draw(prog);
}

Box Entity::GetAABB() {
    // i'm not sure this will work with custom scaling
    return Box(mesh->aabb.position * scale + position, mesh->aabb.size * scale);
}

void Entity::ComputeMatrix() {
    // no rotations for now
    modelMatrix = Matrix::CreateTranslation(position) * Matrix::CreateScale(Vector3(scale, scale, scale));
}

Vector3 Entity::GetPosition() {
    return position;
}

void Entity::SetPosition(const Vector3& pos) {
    position = pos;
    ComputeMatrix();   
}

void Entity::Move(const Vector3& delta) {
    position += delta;
    ComputeMatrix();
}

Vector3 Entity::GetRotation() {
    return rotation;
}

void Entity::SetRotation(const Vector3& rot) {
    rotation = rot;
    ComputeMatrix();
}

void Entity::Rotate(const Vector3& delta) {
    rotation += delta;
    ComputeMatrix();
}

float Entity::GetScale() {
    return scale;
}

void Entity::SetScale(float sc) {
    scale = sc;
    ComputeMatrix();
}