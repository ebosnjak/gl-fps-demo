#include "game.h"

Game::Game(int w, int h) : Application(w, h) {

}

void Game::Init() {
    float vertices[] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.0f, 0.5f
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    Shader vs(GL_VERTEX_SHADER, "vertex.glsl");
    vs.Compile();

    Shader fs(GL_FRAGMENT_SHADER, "fragment.glsl");
    fs.Compile();

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vs.ID);
    glAttachShader(shaderProgram, fs.ID);
    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), NULL);
}

void Game::Update(float deltaTime) {
    
}

void Game::Draw() {
    glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Game::Cleanup() {
    glDeleteProgram(shaderProgram);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}