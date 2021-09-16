#include "entity.h"
#include "game.h"

Game* Entity::gameEngine = nullptr;

Entity::Entity() {
    scale = 1.0f;
    obeysGravity = false;
    onGround = false;
    isSolid = true;
    orientation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
}

Entity::Entity(Mesh* _mesh, glm::vec3 _position, glm::quat _orientation, float _scale) {
    mesh = _mesh;
    position = _position;
    orientation = _orientation;
    scale = _scale;

    obeysGravity = false;
    onGround = false;
    isSolid = true;
}

void Entity::Update(float deltaTime) {
    glm::vec3 nextPos = position + linearVelocity * deltaTime;
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
            newAABB_X.position.x = nextPos.x - GetAABB().size.x / 2.0f * scale;
            newAABB_Y.position.y = nextPos.y - GetAABB().size.y / 2.0f * scale;
            newAABB_Z.position.z = nextPos.z - GetAABB().size.z / 2.0f * scale;

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

            glm::vec3 diff = Box::AABBDistance(newAABB, other);
            float dx = diff.x, dy = diff.y, dz = diff.z;
            
            if (badX) {
                if (position.x <= other.position.x) nextPos.x -= dx;
                else nextPos.x += dx;

                //std::cout << "bad X" << std::endl;
            }
            if (badY) {
                if (position.y <= other.position.y) nextPos.y -= dy;
                else nextPos.y += dy;

                if (linearVelocity.y < 0.0f && !onGround) {
                    onGround = true;
                    linearVelocity.y = 0.0f;
                }

                //std::cout << "bad Y" << std::endl;
            }
            if (badZ) {
                if (position.z <= other.position.z) nextPos.z -= dz;
                else nextPos.z += dz;

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
            AABB_.position.y -= 0.1f;

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
    // add rotations
    modelMatrix = glm::translate(glm::mat4(1.0f), position) *
                  glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, scale));
}

glm::vec3 Entity::GetPosition() {
    return position;
}

void Entity::SetPosition(const glm::vec3& pos) {
    position = pos;
    ComputeMatrix();   
}

void Entity::Move(const glm::vec3& delta) {
    position += delta;
    ComputeMatrix();
}

glm::quat Entity::GetOrientation() {
    return orientation;
}

glm::vec3 Entity::GetOrientationEuler() {
    glm::vec3 tmp = glm::eulerAngles(orientation);
    return glm::vec3(glm::degrees(tmp.x), glm::degrees(tmp.y), glm::degrees(tmp.z));
}

void Entity::SetOrientation(const glm::quat& q) {
    orientation = q;
}

void Entity::SetOrientation(const glm::vec3& v) {
    orientation = glm::quat(glm::vec3(glm::radians(v.x), glm::radians(v.y), glm::radians(v.z)));
}

void Entity::SetOrientation(const glm::vec3& axis, float angle) {
    orientation = glm::angleAxis(glm::radians(angle), glm::vec3(axis.x, axis.y, axis.z));
}

void Entity::Rotate(const glm::quat& rot) {
    orientation = rot * orientation;
}

void Entity::Rotate(const glm::vec3& axis, float angle) {
    orientation = glm::angleAxis(glm::radians(angle), glm::vec3(axis.x, axis.y, axis.z)) * orientation;
}

float Entity::GetScale() {
    return scale;
}

void Entity::SetScale(float sc) {
    scale = sc;
    ComputeMatrix();
}


Player::Player(glm::vec3 _position, glm::quat _orientation, float _scale) {
    position = _position;
    orientation = _orientation;
    scale = _scale;

    mesh = nullptr;
    customAABB = Box(glm::vec3(-0.5f, -1.0f, -0.5f), glm::vec3(1.0f, 2.0f, 1.0f));
    camera = Camera(position);

    obeysGravity = true;
    pitchLimit = 87.0f * 3.14159f / 180.0f;
    yaw = 0.0f; pitch = 0.0f;
}

void Player::Update(float deltaTime) {
    glm::vec2 mouseDelta = gameEngine->GetMouseDelta();
    float deltaYaw = -mouseDelta.x / 1000.0f * 3.14159f;
    float deltaPitch = -mouseDelta.y / 1000.0f * 3.14159f;

    yaw += deltaYaw;
    pitch += deltaPitch;

    if (pitch >= pitchLimit) pitch = pitchLimit;
    if (pitch <= -pitchLimit) pitch = -pitchLimit;

    orientation = glm::quat(glm::vec3(pitch, yaw, 0.0f));
    
    glm::vec3 velocity;
    if (gameEngine->IsKeyDown(Keys::W)) {
        velocity += glm::normalize(glm::vec3(camera.Direction().x, 0.0f, camera.Direction().z)) * 3.0f;
    }
    if (gameEngine->IsKeyDown(Keys::S)) {
        velocity -= glm::normalize(glm::vec3(camera.Direction().x, 0.0f, camera.Direction().z)) * 3.0f;
    }
    if (gameEngine->IsKeyDown(Keys::A)) {
        velocity -= camera.Right() * 3.0f;
    }
    if (gameEngine->IsKeyDown(Keys::D)) {
        velocity += camera.Right() * 3.0f;
    }
    if (gameEngine->IsKeyPressed(Keys::Space)) {
        if (onGround) {
            onGround = false;
            linearVelocity.y = 5.0f;
        }
    }

    if (glm::length(velocity) > 3.0f) {
        velocity = glm::normalize(velocity) * 3.0f;
    }

    linearVelocity.x = velocity.x;

    if (!onGround) {
        linearVelocity.y -= 9.81f * deltaTime;
    }
    else {
        linearVelocity.y = 0.0f;
    }

    linearVelocity.z = velocity.z;

    camera.position = position;
    camera.position.y += 1.0f;

    camera.orientation = orientation;

    camera.Update(deltaTime);

    Entity::Update(deltaTime);
}

void Player::Draw(ShaderProgram& prog) {
    // do nothing
}