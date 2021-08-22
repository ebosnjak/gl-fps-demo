#include "game.h"

Game::Game(int w, int h) : Application(w, h) {

}

void Game::Init() {
    float vertices[] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.0f, 0.5f
    };

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    const char* vsSource = "\
        #version 420\n\
        layout (location = 0) in vec2 vertex;\n\
        void main() {\n\
            gl_Position = vec4(vertex, 0.0, 1.0);\n\
        }";
    
    const char* fsSource = "\
        #version 420\n\
        out vec4 color;\n\
        void main() {\n\
            color = vec4(0.7, 0.0, 0.0, 1.0);\n\
        }";

    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsSource, NULL);
    glCompileShader(vs);

    char infolog[512];
    glGetShaderInfoLog(vs, 512, NULL, infolog);
    std::cout << infolog << std::endl;

    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fsSource, NULL);
    glCompileShader(fs);

    glGetShaderInfoLog(fs, 512, NULL, infolog);
    std::cout << infolog << std::endl;

    unsigned int prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glLinkProgram(prog);

    glUseProgram(prog);

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