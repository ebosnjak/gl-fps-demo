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

    std::vector< unsigned char > image;
    unsigned int texW, texH;
    unsigned int status = lodepng::decode(image, texW, texH, "assets/planks.png");
    if (status != 0) {
        std::cout << "Error: " << lodepng_error_text(status) << std::endl;
    }

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texW, texH, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
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