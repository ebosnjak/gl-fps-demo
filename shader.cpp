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

Shader::~Shader() {
    glDeleteShader(ID);
}

Shader& Shader::operator=(Shader&& sh) {
    ID = sh.ID;
    type = sh.type;
    source = sh.source;
    sh.ID = 0;
    return (*this);
}


ShaderProgram::ShaderProgram() {
    ID = glCreateProgram();
}

ShaderProgram::ShaderProgram(const std::string& _vsPath, const std::string& _fsPath) {
    ID = glCreateProgram();
    Shader vs(GL_VERTEX_SHADER, _vsPath);
    Shader fs(GL_FRAGMENT_SHADER, _fsPath);
    AttachShader(vs);
    AttachShader(fs);
    Link();
}

ShaderProgram::ShaderProgram(const Shader& vs, const Shader& fs) {
    ID = glCreateProgram();
    AttachShader(vs);
    AttachShader(fs);
    Link();
}

ShaderProgram::~ShaderProgram() {
    if (ID != 0) glUseProgram(0);
    glDeleteProgram(ID);
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& prog) {
    ID = prog.ID;
    prog.ID = 0;
    return (*this);
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

void ShaderProgram::SetMat4(const std::string& name, const Matrix& mat) {
    Use();

    // transpose is true because glUniformMatrix assumes column major order,
    // but Matrix class in mathhelper.h uses row major order
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, &mat.M[0][0]);
}

void ShaderProgram::SetFloat(const std::string& name, float val) {
    Use();
    glUniform1f(glGetUniformLocation(ID, name.c_str()), val);
}

void ShaderProgram::SetVec2(const std::string& name, const Vector2& vec) {
    Use();
    glUniform2f(glGetUniformLocation(ID, name.c_str()), vec.X, vec.Y);
}

void ShaderProgram::SetVec3(const std::string& name, const Vector3& vec) {
    Use();
    glUniform3f(glGetUniformLocation(ID, name.c_str()), vec.X, vec.Y, vec.Z);
}

void ShaderProgram::SetVec4(const std::string& name, const Vector4& vec) {
    Use();
    glUniform4f(glGetUniformLocation(ID, name.c_str()), vec.X, vec.Y, vec.Z, vec.W);
}