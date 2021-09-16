#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>

#include "glfuncs.h"
#include "mathhelper.h"

class Shader {
public:
    unsigned int type;
    unsigned int ID;
    std::string source;

    Shader();
    Shader(const Shader& sh) = delete;
    Shader(unsigned int _type, std::string _path);
    
    ~Shader();

    Shader& operator=(const Shader& sh) = delete;
    Shader& operator=(Shader&& sh);
};

class ShaderProgram {
public:
    unsigned int ID;

    ShaderProgram();
    ShaderProgram(const ShaderProgram& prog) = delete;
    ShaderProgram(const std::string& _vsPath, const std::string& _fsPath); 
    ShaderProgram(const Shader& _vs, const Shader& _fs);     
    
    ~ShaderProgram();

    ShaderProgram& operator=(const ShaderProgram& prog) = delete;
    ShaderProgram& operator=(ShaderProgram&& prog);

    void Use();
    void AttachShader(const Shader& sh);    // if attaching to linked program, relink is required to apply this!
    bool Link();

    void SetInt(const std::string& name, int val);
    void SetFloat(const std::string& name, float val);
    void SetMat4(const std::string& name, const glm::mat4& mat);
    void SetVec2(const std::string& name, const glm::vec2& vec);
    void SetVec3(const std::string& name, const glm::vec3& vec);
    void SetVec4(const std::string& name, const glm::vec4& vec);
};

#endif