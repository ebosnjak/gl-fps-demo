#include "game.h"

Game::Game(int w, int h) : Application(w, h) {

}

void Game::Init() {
    Entity::gameEngine = this;

    Content::Instance().Load();

    SetCursorLocked(true);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    prog = ShaderProgram("vertex.glsl", "fragment.glsl");

    test = Entity(Content::Instance().GetMesh("backpack"));
    test.SetPosition(Vector3(1.0f, 3.0f, -3.0f));

    world["floor"] = Entity(Content::Instance().GetMesh("floor"));
    world["floor"].SetPosition(Vector3(0.0f, -2.0f, 0.0f));

    // TODO: 
    // - tie player camera to an entity which obeys gravity and can't fall through the ground
    // - also jumping
    // - obstacles through which the player cannot move
    // - gun viewmodel
    // - actual shooting and hit detection

    player = Player(Vector3(0.0f, 2.0f, 0.0f));
    //camera = Camera(Vector3(0.0f, 2.0f, 4.0f), 90.0f, 0.0f);

    Matrix proj = Matrix::CreatePerspective(45.0f, (float)windowWidth / (float)windowHeight, 1.0f, 100.0f);
    prog.SetMat4("proj", proj);

    prog.SetVec4("light.vector", Vector4(-1.0f, -5.0f, -2.0f, 0.0f));
    //prog.SetVec4("light.vector", Vector4(3.0f, 2.0f, 4.0f, 1.0f)); // for point light
    prog.SetVec3("light.ambient", Vector3(0.1f, 0.1f, 0.1f));
    prog.SetVec3("light.diffuse", Vector3(0.7f, 0.7f, 0.7f));
    prog.SetVec3("light.specular", Vector3(0.8f, 0.8f, 0.8f));
}

void Game::Update(float deltaTime) {
    Vector2 mouseDelta = GetMouseDelta();
    //camera.yaw -= (mouseDelta.X / 2000.0f) * 360.0f;
    //camera.pitch -= (mouseDelta.Y / 2000.0f) * 360.0f;

    player.Rotate(Vector3(-mouseDelta.Y / 2000.0f * 360.0f, -mouseDelta.X / 2000.0f * 360.0f, 0.0f));

    Vector3 velocity;
    if (IsKeyDown(Keys::W)) {
        velocity += Vector3(player.camera.Direction().X, 0.0f, player.camera.Direction().Z).Normalize() * 3.0f;
    }
    if (IsKeyDown(Keys::S)) {
        velocity -= Vector3(player.camera.Direction().X, 0.0f, player.camera.Direction().Z).Normalize() * 3.0f;
    }
    if (IsKeyDown(Keys::A)) {
        velocity -= player.camera.Right() * 3.0f;
    }
    if (IsKeyDown(Keys::D)) {
        velocity += player.camera.Right() * 3.0f;
    }
    if (IsKeyPressed(Keys::Space)) {
        if (player.onGround) {
            player.onGround = false;
            player.linearVelocity.Y = 5.0f;
        }
    }

    if (velocity.Length() > 3.0f) {
        velocity = velocity / velocity.Length() * 3.0f;
    }

    player.linearVelocity.X = velocity.X;

    if (!player.onGround) {
        player.linearVelocity.Y -= 9.81f * deltaTime;
    }
    else {
        player.linearVelocity.Y = 0.0f;
    }

    player.linearVelocity.Z = velocity.Z;

    if (IsKeyPressed(Keys::X)) {
        std::cout << std::fixed << std::setprecision(1);
        //std::cout << "cameraYaw: " << player.camera.yaw << std::endl;
        //std::cout << "cameraPos: " << player.camera.position.X << ", " << player.camera.position.Y << ", " << player.camera.position.Z << std::endl;
        //std::cout << "cameraDirection: " << player.camera.Direction().X << ", " << player.camera.Direction().Y << ", " << player.camera.Direction().Z << std::endl;
        //std::cout << "cameraUp: " << player.camera.Up().X << ", " << player.camera.Up().Y << ", " << player.camera.Up().Z << std::endl;
        //std::cout << "cameraRight: " << player.camera.Right().X << ", " << player.camera.Right().Y << ", " << player.camera.Right().Z << std::endl;
        std::cout << "player position: " << player.GetPosition().X << ", " << player.GetPosition().Y << ", " << player.GetPosition().Z << std::endl;
        std::cout << "player velocity: " << player.linearVelocity.X << ", " << player.linearVelocity.Y << ", " << player.linearVelocity.Z << std::endl;
        std::cout << "player aabb pos: " << player.GetAABB().position.X << ", " << player.GetAABB().position.Y << ", " << player.GetAABB().position.Z << std::endl;
        std::cout << std::endl;
    }

    player.Update(deltaTime);
}   

void Game::Draw() {
    glClearColor(0.529f, 0.808f, 0.922f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    prog.SetMat4("view", player.camera.LookAt());
    prog.SetVec3("cameraPos", player.camera.position);

    test.Draw(prog);
    //DrawBox(prog, test.GetAABB());

    for (auto it = world.begin(); it != world.end(); it++) {
        it->second.Draw(prog);
        //DrawBox(prog, it->second.GetAABB());
    }
}

void Game::Cleanup() {
    
}

void Game::DrawBox(ShaderProgram& p, const Box& b) {
    p.SetMat4("model", Matrix::CreateTranslation(b.position + b.size * 0.5f) * Matrix::CreateScale(b.size));
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    Content::Instance().GetMesh("unitcube")->Draw(p);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}