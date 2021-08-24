#include "shader.h"

Shader::Shader() { }

Shader::Shader(unsigned int _type, std::string _path) {
    std::ifstream fileIn(_path);
    if (fileIn.is_open()) {
        std::string line;
        while (std::getline(fileIn, line)) {
            source += line + "\n";
        }
    }
    else {
        std::cout << "Error: Failed to open file \"" << _path << "\" for reading." << std::endl;
    }

    const char* csource = source.c_str();

    type = _type;
    ID = glCreateShader(type);
    glShaderSource(ID, 1, &csource, nullptr);
    glCompileShader(ID);

    int status;
    glGetShaderiv(ID, GL_COMPILE_STATUS, &status);
    if (!status) {
        char infolog[512];
        glGetShaderInfoLog(ID, 512, nullptr, infolog);
        std::cout << "Shader compilation failed" << std::endl;
        std::cout << infolog << std::endl;
    }
}

void Shader::Delete() {
    glDeleteShader(ID);
}



ShaderProgram::ShaderProgram() {
    ID = glCreateProgram();
}

ShaderProgram::ShaderProgram(std::string _vsPath, std::string _fsPath) {
    ID = glCreateProgram();
    Shader vs(GL_VERTEX_SHADER, _vsPath);
    Shader fs(GL_FRAGMENT_SHADER, _fsPath);
    AttachShader(vs);
    AttachShader(fs);
    Link();

    vs.Delete();
    fs.Delete();
}

ShaderProgram::ShaderProgram(const Shader& vs, const Shader& fs) {
    ID = glCreateProgram();
    AttachShader(vs);
    AttachShader(fs);
    Link();
}

void ShaderProgram::Use() {
    glUseProgram(ID);
}

bool ShaderProgram::Link() {
    glLinkProgram(ID);
    
    int status;
    glGetProgramiv(ID, GL_LINK_STATUS, &status);
    if (!status) {
        char infolog[512];
        glGetProgramInfoLog(ID, 512, nullptr, infolog);
        std::cout << "Program link failed" << std::endl;
        std::cout << infolog << std::endl;
        return false;
    }
    else {
        return true;
    }
}

void ShaderProgram::AttachShader(const Shader& sh) {
    glAttachShader(ID, sh.ID);
}

void ShaderProgram::Delete() {
    glDeleteProgram(ID);
}