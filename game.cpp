#include "game.h"

Game::Game(int w, int h) : Application(w, h) {

}

void Game::Init() {
    Content::Instance().Load();

    SetCursorLocked(true);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    prog = ShaderProgram("vertex.glsl", "fragment.glsl");

    testMesh = Mesh("assets/shotgun_tri.obj");
    backpackMesh = Mesh("assets/backpack/backpack.obj");    // loading takes a while

    cameraPos = Vector3(0.0f, 0.0f, 4.0f);
    cameraYaw = 3.1415f / 2.0f;
    cameraPitch = 0.0f;

    Matrix proj = Matrix::CreatePerspective(45.0f, (float)windowWidth / (float)windowHeight, 1.0f, 15.0f);
    prog.SetMat4("proj", proj);
}

void Game::Update(float deltaTime) {
    Vector2 mouseDelta = GetMouseDelta();
    cameraYaw -= (mouseDelta.X / 2000.0f) * 2.0f * 3.14159f;
    cameraPitch -= (mouseDelta.Y / 2000.0f) * 2.0f * 3.14159f;

    if (cameraPitch > 3.12f / 2.0f) cameraPitch = 3.12f / 2.0f;
    if (cameraPitch < -3.12f / 2.0f) cameraPitch = -3.12f / 2.0f; 

    cameraDirection = Vector3(cosf(cameraYaw) * cosf(cameraPitch), sinf(cameraPitch), -sinf(cameraYaw) * cosf(cameraPitch)).Normalize();
    cameraRight = Vector3::Cross(cameraDirection, Vector3(0.0f, 1.0f, 0.0f)).Normalize();
    cameraUp = Vector3::Cross(cameraRight, cameraDirection).Normalize();

    if (IsKeyDown(Keys::W)) {
        cameraPos += cameraDirection * 2.0f * deltaTime;
    }
    if (IsKeyDown(Keys::S)) {
        cameraPos -= cameraDirection * 2.0f * deltaTime;
    }
    if (IsKeyDown(Keys::A)) {
        cameraPos -= cameraRight * 2.0f * deltaTime;
    }
    if (IsKeyDown(Keys::D)) {
        cameraPos += cameraRight * 2.0f * deltaTime;
    }

    if (IsKeyPressed(Keys::X)) {
        std::cout << std::fixed << std::setprecision(1);
        std::cout << "cameraYaw: " << cameraYaw << std::endl;
        std::cout << "cameraPos: " << cameraPos.X << ", " << cameraPos.Y << ", " << cameraPos.Z << std::endl;
        std::cout << "cameraDirection: " << cameraDirection.X << ", " << cameraDirection.Y << ", " << cameraDirection.Z << std::endl;
        std::cout << "cameraUp: " << cameraUp.X << ", " << cameraUp.Y << ", " << cameraUp.Z << std::endl;
        std::cout << "cameraRight: " << cameraRight.X << ", " << cameraRight.Y << ", " << cameraRight.Z << std::endl;
        std::cout << std::endl;
    }

    modelMat = Matrix::CreateTranslation(cameraPos + 2.0f * cameraDirection + cameraRight - 0.5f * cameraUp);
    modelMat = modelMat * Matrix::CreateFromAxisAngle(Vector3(cameraRight), cameraPitch * 180.0f / 3.1415f);
    modelMat = modelMat * Matrix::CreateFromAxisAngle(Vector3(0.0f, 1.0f, 0.0f), cameraYaw * 180.0f / 3.1415f + 90.0f);
    modelMat = modelMat * Matrix::CreateScale(Vector3(20.0f, 20.0f, 20.0f));
}   

void Game::Draw() {
    glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    prog.SetMat4("view", Matrix::CreateLookAt(cameraPos, cameraPos + cameraDirection, cameraUp));
    prog.SetVec3("cameraPos", cameraPos);

    prog.SetMat4("model", modelMat);
    testMesh.Draw(prog);

    prog.SetMat4("model", Matrix());
    backpackMesh.Draw(prog);
}

void Game::Cleanup() {
    
}