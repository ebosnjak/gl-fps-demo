#include "shader.h"

Shader::Shader() { }

Shader::Shader(unsigned int _type, std::string _path) {
    std::ifstream fileIn(_path);
    std::string tmp;
    if (fileIn.is_open()) {
        std::string line;
        while (std::getline(fileIn, line)) {
            tmp += line + "\n";
        }

        source = tmp.c_str();
    }
    else {
        std::cout << "Error: Failed to open file \"" << _path << "\" for reading." << std::endl;
    }

    type = _type;
    ID = glCreateShader(type);
    glShaderSource(ID, 1, &source, nullptr);
}

Shader::~Shader() {
    glDeleteShader(ID);
}

bool Shader::Compile() {
    glCompileShader(ID);

    int status;
    glGetShaderiv(ID, GL_COMPILE_STATUS, &status);
    if (!status) {
        char infolog[512];
        glGetShaderInfoLog(ID, 512, nullptr, infolog);
        std::cout << infolog << std::endl;

        return false;
    }
    else {
        return true;
    }
}