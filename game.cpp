#include "game.h"

Game::Game(int w, int h) : Application(w, h) {

}

void Game::Init() {
    SetCursorLocked(true);

    glEnable(GL_DEPTH_TEST);

    float square[] = {
        // xy               uv
        -0.5f, -0.5f,       0.0f, 0.0f,
        0.5f, -0.5f,        1.0f, 0.0f,
        0.5f, 0.5f,         1.0f, 1.0f,

        0.5f, 0.5f,         1.0f, 1.0f,
        -0.5f, 0.5f,        0.0f, 1.0f,
        -0.5f, -0.5f,       0.0f, 0.0f
    };

    float cube[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

    prog = ShaderProgram("vertex.glsl", "fragment.glsl");
    prog.Use();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    tex = Texture2D("assets/planks.png");

    cameraPos = Vector3(0.0f, 0.0f, 4.0f);
    cameraYaw = 3.1415f / 2.0f;
    cameraPitch = 0.0f;

    Matrix model;
    Matrix view;
    Matrix proj = Matrix::CreatePerspective(45.0f, (float)windowWidth / (float)windowHeight, 1.0f, 15.0f);

    prog.SetMat4("model", model);
    prog.SetMat4("view", view);
    prog.SetMat4("proj", proj);

    angle = 0.0f;
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

    prog.SetMat4("view", Matrix::CreateLookAt(cameraPos, cameraPos + cameraDirection, cameraUp));

    angle += 30.0f * deltaTime;
    if (angle > 360.0f) {
        angle -= 360.0f;
    }

    prog.SetMat4("model", Matrix::CreateFromAxisAngle(Vector3(0.0f, 1.0f, 0.0f), angle));
}

void Game::Draw() {
    glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Game::Cleanup() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}