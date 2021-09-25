#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "entity.h"
#include "content.h"

class Projectile : public Entity {
public:
    int damage;
    float speed;

    Projectile();
    Projectile(glm::vec3 _position, float _speed, glm::vec3 _direction);

    void Update(float deltaTime);
    void Draw(ShaderProgram& prog);

    void OnHit(Entity* target);
};

#endif