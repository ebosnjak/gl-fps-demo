#include "game.h"

Game::Game(int w, int h) : Application(w, h) {
    
}

void Game::Init() {
    Content::Instance().Load();

    SetCursorLocked(true);

    glEnable(GL_DEPTH_TEST);

    prog = ShaderProgram("vertex.glsl", "fragment.glsl");

    glUseProgram(0);

    /*std::vector< VertexData > vertices;
    vertices = { 
        { Vector3(-0.5f, -0.5f, 0.0f), Vector3(), Vector2(0.0f, 0.0f) }, 
        { Vector3(0.5f, -0.5f, 0.0f), Vector3(), Vector2(1.0f, 0.0f) },
        { Vector3(0.5f, 0.5f, 0.0f), Vector3(), Vector2(1.0f, 1.0f) },
        { Vector3(-0.5f, 0.5f, 0.0f), Vector3(), Vector2(0.0f, 1.0f) } 
    };

    testMesh = Mesh(vertices, { Content::Instance().GetTextureID("planks") }, { 0, 1, 2, 2, 3, 0 });*/

    testMesh = Mesh("assets/shotgun.obj");
    prog.SetVec3("material.ambient", Vector3(0.24725f, 0.1995f, 0.0745f));
    prog.SetVec3("material.diffuse", Vector3(0.75164f, 0.60648f, 0.22648f));
    prog.SetVec3("material.specular", Vector3(0.62828f, 0.55580f, 0.36607f));
    prog.SetFloat("material.shininess", 51.2f);

    cameraPos = Vector3(0.0f, 0.0f, 4.0f);
    cameraYaw = 3.1415f / 2.0f;
    cameraPitch = 0.0f;

    Matrix model;
    Matrix view;
    Matrix proj = Matrix::CreatePerspective(45.0f, (float)windowWidth / (float)windowHeight, 1.0f, 15.0f);

    prog.SetMat4("model", model);
    prog.SetMat4("view", view);
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

    Matrix model = Matrix::CreateTranslation(cameraPos + 2.0f * cameraDirection + cameraRight - 0.5f * cameraUp);
    model = model * Matrix::CreateFromAxisAngle(Vector3(cameraRight), cameraPitch * 180.0f / 3.1415f);
    model = model * Matrix::CreateFromAxisAngle(Vector3(0.0f, 1.0f, 0.0f), cameraYaw * 180.0f / 3.1415f + 90.0f);
    model = model * Matrix::CreateScale(Vector3(20.0f, 20.0f, 20.0f));
    prog.SetMat4("model", model);
    prog.SetMat4("view", Matrix::CreateLookAt(cameraPos, cameraPos + cameraDirection, cameraUp));
    prog.SetVec3("cameraPos", cameraPos);
}   

void Game::Draw() {
    glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    prog.Use();
    testMesh.Draw();
}

void Game::Cleanup() {
    
}