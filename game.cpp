#include "game.h"

Game::Game(int w, int h) : Application(w, h) {

}

void Game::Init() {
    Entity::gameEngine = this;
    Healthbar::gameEngine = this;
    Crosshair::gameEngine = this;

    srand(time(0));

    Content::Instance().Load();

    SetCursorLocked(true);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_MULTISAMPLE);

    prog = ShaderProgram("vertex.glsl", "fragment.glsl");
    prog2D = ShaderProgram("vertex2d.glsl", "frag2d.glsl");

    world["floor1"] = Entity(Content::Instance().GetMesh("floor"));
    world["floor1"].SetPosition(glm::vec3(0.0f, -2.0f, 0.0f));
    world["floor1"].type = EntityType::World;

    world["floor2"] = Entity(Content::Instance().GetMesh("floor"));
    world["floor2"].SetPosition(glm::vec3(25.0f, -1.0f, 0.0f));
    world["floor2"].type = EntityType::World;

    world["floor3"] = Entity(Content::Instance().GetMesh("floor"));
    world["floor3"].SetPosition(glm::vec3(50.0f, 0.0f, 0.0f));
    world["floor3"].type = EntityType::World;

    world["wall1"] = Entity(Content::Instance().GetMesh("wall"));
    world["wall1"].SetPosition(glm::vec3(0.0f, 0.0f, -13.0f));
    world["wall1"].type = EntityType::World;

    enemies["test1"] = Enemy(Content::Instance().GetMesh("test"));
    enemies["test1"].SetPosition(glm::vec3(17.0f, 7.0f, 0.0f));
    enemies["test1"].useHpBar = true;
    enemies["test1"].hpBar.size.x = 2.4f;

    enemies["test2"] = Enemy(Content::Instance().GetMesh("test"));
    enemies["test2"].SetPosition(glm::vec3(27.0f, 10.0f, 5.0f));
    enemies["test2"].useHpBar = true;
    enemies["test2"].hpBar.size.x = 2.4f;

    enemies["test3"] = Enemy(Content::Instance().GetMesh("test"));
    enemies["test3"].SetPosition(glm::vec3(20.0f, 15.0f, -4.0f));
    enemies["test3"].useHpBar = true;
    enemies["test3"].hpBar.size.x = 2.4f;

    cnt = 4;

    font = SpriteFont(Content::Instance().GetTexture("fontsheet"));

    // TODO: 
    // - enemies that fight back
    //   - they shouldn't laser the player with 100% accuracy
    //   - they should spawn randomly until a maximum number is reached
    //
    // - (sprinting)                    <--|------- impossible to do, animation code is awful hardcoded radioactive spaghetti 
    // - (meleeing with the gun butt)   <--|

    player = Player(glm::vec3(0.0f, 2.0f, 0.0f), glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)));
    player.maxHealth = 500;
    player.health = player.maxHealth;
    player.hpBarUI.position = glm::vec2(20.0f, 20.0f);

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
    prog.SetMat4("proj", proj);

    glm::mat4 proj2D = glm::ortho(0.0f, (float)windowWidth, (float)windowHeight, 0.0f, -1.0f, 1.0f);
    prog2D.SetMat4("proj", proj2D);

    prog.SetVec4("light.vector", glm::vec4(-1.0f, -5.0f, -2.0f, 0.0f));
    //prog.SetVec4("light.vector", Vector4(3.0f, 2.0f, 4.0f, 1.0f)); // for point light
    prog.SetVec3("light.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
    prog.SetVec3("light.diffuse", glm::vec3(0.7f, 0.7f, 0.7f));
    prog.SetVec3("light.specular", glm::vec3(0.8f, 0.8f, 0.8f));

    prog.SetInt("noiseTex", 10);
    glActiveTexture(GL_TEXTURE10);
    Content::Instance().GetTexture("noise")->Bind();
    prog.SetVec2("noiseResolution", glm::vec2(Content::Instance().GetTexture("noise")->width, Content::Instance().GetTexture("noise")->height));
}

void Game::Update(float deltaTime) {
    if (!IsWindowFocused()) {
        SetCursorLocked(false);
    }
    else {
        SetCursorLocked(true);
    }

    if (!player.isAlive) {
        if (IsKeyPressed(Keys::Escape)) {
            isRunning = false;
        }

        return;
    }

    if (player.GetPosition().y < -25.0f) {
        player.SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));
        player.linearVelocity = glm::vec3(0.0f);
    }

    if (IsKeyPressed(Keys::X)) {
        std::cout << std::fixed << std::setprecision(1);
        std::cout << "gun position: " << player.currentWeapon->GetPosition().x << ", " << player.currentWeapon->GetPosition().y << ", " << player.currentWeapon->GetPosition().z << std::endl;
        std::cout << "player position: " << player.GetPosition().x << ", " << player.GetPosition().y << ", " << player.GetPosition().z << std::endl;
        std::cout << "player rotation: " << player.GetOrientationEuler().x << ", " << player.GetOrientationEuler().y << ", " << player.GetOrientationEuler().z << std::endl;
        std::cout << "player velocity: " << player.linearVelocity.x << ", " << player.linearVelocity.y << ", " << player.linearVelocity.z << std::endl;
        std::cout << "player aabb pos: " << player.GetAABB().position.x << ", " << player.GetAABB().position.y << ", " << player.GetAABB().position.z << std::endl;
        std::cout << "player camera direction: " << player.camera.Direction().x << ", " << player.camera.Direction().y << ", " << player.camera.Direction().z << std::endl;
        std::cout << std::endl;
    }

    if (IsKeyPressed(Keys::L)) {
        std::string id = "test" + std::to_string(cnt++);
        enemies[id] = Enemy(Content::Instance().GetMesh("test"));
        enemies[id].SetPosition(player.camera.position + 10.0f * glm::vec3(player.camera.Direction().x, 0.5f, player.camera.Direction().z));
        enemies[id].useHpBar = true;
        enemies[id].hpBar.size.x = 2.4f;
    }

    player.Update(deltaTime);

    for (auto& x : projectiles) {
        x.Update(deltaTime);
    }

    for (auto it = projectiles.begin(); it != projectiles.end(); ) {
        if (!it->isAlive) {
            projectiles.erase(it++);
        }
        else {
            ++it;
        }
    }

    for (auto& x : enemies) {
        x.second.Update(deltaTime);
    }

    for (auto it = enemies.begin(); it != enemies.end(); ) {
        if (!it->second.isAlive) {
            enemies.erase(it++);
        }
        else {
            ++it;
        }
    }
}   

void Game::Draw() {
    glClearColor(0.529f, 0.808f, 0.922f, 1.0f);
    glStencilMask(0xFF);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    if (!player.isAlive) {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        font.DrawString(prog2D, "Game over!", glm::vec2(20.0f, 20.0f), glm::vec2(0.7f, 0.7f), glm::vec3(1.0f, 0.15f, 0.0f));

        return;
    }

    prog.SetMat4("view", player.camera.LookAt());
    prog.SetVec3("cameraPos", player.camera.position);

    // font.DrawString(prog2D, "the quick brown fox", glm::vec2(0.0f, 0.0f), glm::vec2(0.4f));
    // font.DrawString(prog2D, "jumps over a lazy dog", glm::vec2(0.0f, 100.0f), glm::vec2(0.4f));
    // font.DrawString(prog2D, "THE QUICK BROWN FOX", glm::vec2(0.0f, 200.0f), glm::vec2(0.4f));
    // font.DrawString(prog2D, "JUMPS OVER A LAZY DOG", glm::vec2(0.0f, 300.0f), glm::vec2(0.4f));

    std::string str = "Ammo: " + std::to_string(player.currentWeapon->ammo) + "/" + std::to_string(player.currentWeapon->maxAmmo);
    font.DrawString(prog2D, str, glm::vec2(10.0f, (float)windowHeight - 70.0f), glm::vec2(0.7f, 0.7f), glm::vec3(0.0f, 0.5f, 1.0f));

    player.Draw(prog, prog2D);

    for (auto& x : world) {
        x.second.Draw(prog);
        //DrawBox(prog, it->second.GetAABB(), glm::vec3(1.0f, 0.0f, 0.0f));
    }

    for (auto& x : enemies) {
        x.second.Draw(prog);
        //DrawBox(prog, it->second.GetAABB(), glm::vec3(0.0f, 0.0f, 1.0f));
    }

    for (auto& x : projectiles) {
        x.Draw(prog);
    }
}

void Game::Cleanup() {
    
}

void Game::DrawBox(ShaderProgram& p, const Box& b, glm::vec3 c) {
    p.SetMat4("model", glm::translate(glm::mat4(1.0f), b.position + b.size * 0.5f) * glm::scale(glm::mat4(1.0f), b.size));
    glm::vec3 tmp = Content::Instance().GetMesh("unitcube")->color;
    Content::Instance().GetMesh("unitcube")->color = c;
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    Content::Instance().GetMesh("unitcube")->Draw(p);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    Content::Instance().GetMesh("unitcube")->color = tmp;
}