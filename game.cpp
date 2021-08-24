#include "game.h"

Game::Game(int w, int h) : Application(w, h) {

}

void Game::Init() {
    float vertices[] = {
        // xy               uv
        -0.5f, -0.5f,       0.0f, 0.0f,
        0.5f, -0.5f,        1.0f, 0.0f,
        0.5f, 0.5f,         1.0f, 1.0f,

        0.5f, 0.5f,         1.0f, 1.0f,
        -0.5f, 0.5f,        0.0f, 1.0f,
        -0.5f, -0.5f,       0.0f, 0.0f
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    prog = ShaderProgram("vertex.glsl", "fragment.glsl");
    prog.Use();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), NULL);

    tex = Texture2D("assets/planks.png");
}

void Game::Update(float deltaTime) {
    
}

void Game::Draw() {
    glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Game::Cleanup() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}