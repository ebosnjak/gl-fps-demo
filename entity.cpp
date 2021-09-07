#include "entity.h"
#include "game.h"

Game* Entity::gameEngine = nullptr;

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
    if (linearVelocity.Length() > 0.1f) {
        position += linearVelocity * deltaTime;
        ComputeMatrix();
    }
}

void Entity::Draw(ShaderProgram& prog) {
    prog.Use();
    prog.SetMat4("model", modelMatrix);
    mesh->Draw(prog);
}

Box Entity::GetAABB() {
    // i'm not sure this will work with custom scaling
    if (mesh == nullptr) {
        return Box(aabb.position * scale + position, aabb.size * scale);
    }
    else {
        return Box(mesh->aabb.position * scale + position, mesh->aabb.size * scale);
    }
}

void Entity::ComputeMatrix() {
    // only y rotation for now
    modelMatrix = Matrix::CreateTranslation(position) *
                  Matrix::CreateFromAxisAngle(Vector3(0.0f, 1.0f, 0.0f), rotation.Y) *
                  Matrix::CreateScale(Vector3(scale, scale, scale));
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


Player::Player(Vector3 _position, Vector3 _rotation, float _scale) {
    position = _position;
    rotation = _rotation;
    scale = _scale;

    mesh = nullptr;
    aabb = Box(Vector3(-0.5f, -1.0f, -0.5f), Vector3(1.0f, 2.0f, 1.0f));
    camera = Camera(position);
}

void Player::Update(float deltaTime) {
    Entity::Update(deltaTime);

    camera.position = position;
    camera.yaw = rotation.Y;
    camera.pitch = rotation.X;
}

void Player::Draw(ShaderProgram& prog) {
    // do nothing
}