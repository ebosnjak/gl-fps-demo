#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>

#include "glfuncs.h"

class Shader {
public:
    unsigned int type;
    unsigned int ID;
    std::string source;

    Shader();
    Shader(unsigned int _type, std::string _path);

    void Delete();
};

class ShaderProgram {
public:
    unsigned int ID;

    ShaderProgram();                                            // creates program
    ShaderProgram(std::string _vsPath, std::string _fsPath);    // creates and links program
    ShaderProgram(const Shader& _vs, const Shader& _fs);        // creates and links program

    void Use();
    void AttachShader(const Shader& sh);    // if attaching to linked program, relink is required to apply this!
    bool Link();
    void Delete();
};

#endif