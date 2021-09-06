#include "game.h"

Game::Game(int w, int h) : Application(w, h) {

}

void Game::Init() {
    Content::Instance().Load();

    SetCursorLocked(true);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    prog = ShaderProgram("vertex.glsl", "fragment.glsl");

    test = Entity(Content::Instance().GetMesh("backpack"));

    camera = Camera(Vector3(0.0f, 2.0f, 4.0f), 90.0f, 0.0f);

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
    camera.yaw -= (mouseDelta.X / 2000.0f) * 360.0f;
    camera.pitch -= (mouseDelta.Y / 2000.0f) * 360.0f;

    if (IsKeyDown(Keys::W)) {
        camera.position += camera.Direction() * 2.0f * deltaTime;
    }
    if (IsKeyDown(Keys::S)) {
        camera.position -= camera.Direction() * 2.0f * deltaTime;
    }
    if (IsKeyDown(Keys::A)) {
        camera.position -= camera.Right() * 2.0f * deltaTime;
    }
    if (IsKeyDown(Keys::D)) {
        camera.position += camera.Right() * 2.0f * deltaTime;
    }

    if (IsKeyPressed(Keys::X)) {
        std::cout << std::fixed << std::setprecision(1);
        std::cout << "cameraYaw: " << camera.yaw << std::endl;
        std::cout << "cameraPos: " << camera.position.X << ", " << camera.position.Y << ", " << camera.position.Z << std::endl;
        std::cout << "cameraDirection: " << camera.Direction().X << ", " << camera.Direction().Y << ", " << camera.Direction().Z << std::endl;
        std::cout << "cameraUp: " << camera.Up().X << ", " << camera.Up().Y << ", " << camera.Up().Z << std::endl;
        std::cout << "cameraRight: " << camera.Right().X << ", " << camera.Right().Y << ", " << camera.Right().Z << std::endl;
        std::cout << std::endl;
    }
}   

void Game::Draw() {
    glClearColor(0.529f, 0.808f, 0.922f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    prog.SetMat4("view", camera.LookAt());
    prog.SetVec3("cameraPos", camera.position);

    test.Draw(prog);

    DrawBox(prog, test.GetAABB());
}

void Game::Cleanup() {
    
}

void Game::DrawBox(ShaderProgram& p, const Box& b) {
    p.SetMat4("model", Matrix::CreateTranslation(b.position + b.size * 0.5f) * Matrix::CreateScale(b.size));
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    Content::Instance().GetMesh("unitcube")->Draw(p);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}