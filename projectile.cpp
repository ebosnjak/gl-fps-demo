#include "projectile.h"
#include "game.h"

Projectile::Projectile() {
    type = EntityType::Projectile;

    mesh = Content::Instance().GetMesh("unitcube");
    mesh->color = glm::vec3(1.0f, 0.0f, 0.0f);
    
    position = glm::vec3(0.0f);
    orientation = glm::quat(glm::vec3(0.0f));
    scale = 0.02f;

    obeysGravity = false;
    onGround = false;
    isSolid = false;

    linearVelocity = glm::vec3(0.0f);

    damage = 10;
    speed = 10.0f;
}

Projectile::Projectile(glm::vec3 _position, float _speed, glm::vec3 _direction) {
    type = EntityType::Projectile;

    mesh = Content::Instance().GetMesh("unitcube");
    mesh->color = glm::vec3(1.0f, 0.0f, 0.0f);
    
    position = _position;
    orientation = glm::quat(glm::vec3(0.0f));
    scale = 0.02f;

    obeysGravity = false;
    onGround = false;
    isSolid = false;

    damage = 10;
    speed = _speed;

    linearVelocity = _direction * speed;
}

void Projectile::Update(float deltaTime) {
    if (glm::length(position - gameEngine->player.GetPosition()) > 200.0f) {
        isAlive = false;
    }

    for (auto it = gameEngine->world.begin(); it != gameEngine->world.end(); it++) {
        if (Box::CheckAABB(GetAABB(), it->second.GetAABB())) {
            OnHit(&(it->second));
        }
    }

    for (auto it = gameEngine->enemies.begin(); it != gameEngine->enemies.end(); it++) {
        if (Box::CheckAABB(GetAABB(), it->second.GetAABB())) {
            OnHit(&(it->second));
        }
    }

    if (Box::CheckAABB(GetAABB(), gameEngine->player.GetAABB())) {
        OnHit(&(gameEngine->player));
    }

    Entity::Update(deltaTime);
}

void Projectile::Draw(ShaderProgram& prog) {

    Entity::Draw(prog);
}

void Projectile::OnHit(Entity* target) {
    if (target->type == EntityType::Enemy) {
        target->health -= damage;
        isAlive = false;
        //std::cout << "hit" << std::endl;
    }
    else if (target->type == EntityType::World) {
        isAlive = false;
    }
    else if (target->type == EntityType::Player) {
        target->health -= damage;
        isAlive = false;
        //std::cout << "hit player" << std::endl;
    }
}