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

    test = Entity(Content::Instance().GetMesh("smg"));
    test.SetPosition(Vector3(1.0f, 0.0f, -3.0f));
    test.SetScale(0.2f);

    world["floor1"] = Entity(Content::Instance().GetMesh("floor"));
    world["floor1"].SetPosition(Vector3(0.0f, -2.0f, 0.0f));

    world["floor2"] = Entity(Content::Instance().GetMesh("floor"));
    world["floor2"].SetPosition(Vector3(25.0f, -1.0f, 0.0f));

    world["floor3"] = Entity(Content::Instance().GetMesh("floor"));
    world["floor3"].SetPosition(Vector3(50.0f, 0.0f, 0.0f));

    // TODO: 
    // - implement custom Quaternions
    // - improve Entity class (reduce amount of spaghetti)
    // - gun viewmodel
    // - actual shooting and hit detection

    player = Player(Vector3(0.0f, 2.0f, 0.0f), glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)));

    Matrix proj = Matrix::CreatePerspective(45.0f, (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
    prog.SetMat4("proj", proj);

    prog.SetVec4("light.vector", Vector4(-1.0f, -5.0f, -2.0f, 0.0f));
    //prog.SetVec4("light.vector", Vector4(3.0f, 2.0f, 4.0f, 1.0f)); // for point light
    prog.SetVec3("light.ambient", Vector3(0.1f, 0.1f, 0.1f));
    prog.SetVec3("light.diffuse", Vector3(0.7f, 0.7f, 0.7f));
    prog.SetVec3("light.specular", Vector3(0.8f, 0.8f, 0.8f));

    prog.SetInt("noiseTex", 10);
    glActiveTexture(GL_TEXTURE10);
    Content::Instance().GetTexture("noise")->Bind();
    prog.SetVec2("noiseResolution", Vector2(Content::Instance().GetTexture("noise")->width, Content::Instance().GetTexture("noise")->height));
}

void Game::Update(float deltaTime) {
    if (IsKeyPressed(Keys::X)) {
        std::cout << std::fixed << std::setprecision(1);
        std::cout << "player position: " << player.GetPosition().X << ", " << player.GetPosition().Y << ", " << player.GetPosition().Z << std::endl;
        std::cout << "player rotation: " << player.GetOrientationEuler().X << ", " << player.GetOrientationEuler().Y << ", " << player.GetOrientationEuler().Z << std::endl;
        std::cout << "player velocity: " << player.linearVelocity.X << ", " << player.linearVelocity.Y << ", " << player.linearVelocity.Z << std::endl;
        std::cout << "player aabb pos: " << player.GetAABB().position.X << ", " << player.GetAABB().position.Y << ", " << player.GetAABB().position.Z << std::endl;
        std::cout << "player camera direction: " << player.camera.Direction().X << ", " << player.camera.Direction().Y << ", " << player.camera.Direction().Z << std::endl;
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