#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>

#include "glfuncs.h"

class Shader {
public:
    unsigned int type;
    unsigned int ID;
    const char* source;

    Shader();
    Shader(unsigned int _type, std::string _path);
    ~Shader();

    bool Compile();
};

#endif