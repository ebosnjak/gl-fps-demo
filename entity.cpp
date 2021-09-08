#include "entity.h"
#include "game.h"

Game* Entity::gameEngine = nullptr;

Entity::Entity() {
    scale = 1.0f;
    obeysGravity = false;
    onGround = false;
    isSolid = true;
}

Entity::Entity(Mesh* _mesh, Vector3 _position, Vector3 _rotation, float _scale) {
    mesh = _mesh;
    position = _position;
    rotation = _rotation;
    scale = _scale;

    obeysGravity = false;
    onGround = false;
    isSolid = true;
}

void Entity::Update(float deltaTime) {
    Vector3 nextPos = position + linearVelocity * deltaTime;
    if (isSolid) {
        for (auto it = gameEngine->world.begin(); it != gameEngine->world.end(); it++) {
            Box other = it->second.GetAABB();
            Box newAABB = GetAABB();
            newAABB.position = nextPos - GetAABB().size / 2.0f;

            if (!Box::CheckAABB(newAABB, other)) {
                continue;
            }

            Box newAABB_X = GetAABB();
            Box newAABB_Y = GetAABB();
            Box newAABB_Z = GetAABB();
            newAABB_X.position.X = nextPos.X - GetAABB().size.X / 2.0f * scale;
            newAABB_Y.position.Y = nextPos.Y - GetAABB().size.Y / 2.0f * scale;
            newAABB_Z.position.Z = nextPos.Z - GetAABB().size.Z / 2.0f * scale;

            bool badX = false, badY = false, badZ = false;
            if (Box::CheckAABB(newAABB_X, other)) {
                badX = true;
            }
            if (Box::CheckAABB(newAABB_Y, other)) {
                badY = true;
            }
            if (Box::CheckAABB(newAABB_Z, other)) {
                badZ = true;
            }

            Vector3 diff = Box::AABBDistance(newAABB, other);
            float dx = diff.X, dy = diff.Y, dz = diff.Z;
            
            if (badX) {
                if (position.X <= other.position.X) nextPos.X -= dx;
                else nextPos.X += dx;

                //std::cout << "bad X" << std::endl;
            }
            if (badY) {
                if (position.Y <= other.position.Y) nextPos.Y -= dy;
                else nextPos.Y += dy;

                if (linearVelocity.Y < 0.0f && !onGround) {
                    onGround = true;
                    linearVelocity.Y = 0.0f;
                }

                //std::cout << "bad Y" << std::endl;
            }
            if (badZ) {
                if (position.Z <= other.position.Z) nextPos.Z -= dz;
                else nextPos.Z += dz;

                //std::cout << "bad Z" << std::endl;
            }

            // std::cout << "newAABB_X: " << newAABB_X.position.X << ", " << newAABB_X.position.Y << ", " << newAABB_X.position.Z << ", (" <<
            //             newAABB_X.size.X << ", " << newAABB_X.size.Y << ", " << newAABB_X.size.Z << ")" << std::endl;
            // std::cout << "newAABB_Y: " << newAABB_Y.position.X << ", " << newAABB_Y.position.Y << ", " << newAABB_Y.position.Z << ", (" <<
            //             newAABB_Y.size.X << ", " << newAABB_Y.size.Y << ", " << newAABB_Y.size.Z << ")" << std::endl;
            // std::cout << "newAABB_Z: " << newAABB_Z.position.X << ", " << newAABB_Z.position.Y << ", " << newAABB_Z.position.Z << ", (" <<
            //             newAABB_Z.size.X << ", " << newAABB_Z.size.Y << ", " << newAABB_Z.size.Z << ")" << std::endl;
        }

        if (obeysGravity && onGround) {
            Box AABB_ = GetAABB();
            AABB_.position = nextPos - GetAABB().size / 2.0f;
            AABB_.position.Y -= 0.1f;

            onGround = false;
            for (auto it = gameEngine->world.begin(); it != gameEngine->world.end(); it++) {
                if (Box::CheckAABB(AABB_, it->second.GetAABB())) {
                    onGround = true;
                    break;
                }
            }
        }
    }

    position = nextPos;

    ComputeMatrix();
}

void Entity::Draw(ShaderProgram& prog) {
    prog.Use();
    prog.SetMat4("model", modelMatrix);
    mesh->Draw(prog);
}

Box Entity::GetAABB() {
    // i'm not sure this will work with custom scaling
    if (mesh == nullptr) {
        return Box(customAABB.position * scale + position, customAABB.size * scale);
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
    customAABB = Box(Vector3(-0.5f, -1.0f, -0.5f), Vector3(1.0f, 2.0f, 1.0f));
    camera = Camera(position);

    obeysGravity = true;
}

void Player::Update(float deltaTime) {
    Entity::Update(deltaTime);

    camera.position = position;
    camera.position.Y += 1.0f;
    camera.yaw = rotation.Y;
    camera.pitch = rotation.X;
}

void Player::Draw(ShaderProgram& prog) {
    // do nothing
}