#ifndef GAME_H
#define GAME_H

#include "application.h"
#include "shader.h"
#include "texture2d.h"
#include "mathhelper.h"
#include "mesh.h"
#include "content.h"
#include "camera.h"
#include "entity.h"
#include "weapon.h"
#include "projectile.h"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>

#include <iomanip>

class Game : public Application {
public:
    Player player;

    Weapon_SMG smg;

    std::unordered_map< std::string, Entity > world;
    std::unordered_map< std::string, Entity > enemies;
    std::list< Projectile > projectiles;

    int cnt;

    Camera camera;
    ShaderProgram prog;

    Game(int w, int h);

    void Init();
    void Update(float deltaTime);
    void Draw();
    void Cleanup();

    static void DrawBox(ShaderProgram& p, const Box& b, glm::vec3 c);
};

#endif