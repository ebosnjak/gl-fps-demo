#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "dependencies/lodepng.h"
#include "glfuncs.h"

#include <iostream>
#include <vector>
#include <unordered_map>

class Texture2D {
public:
    static unsigned int currentlyBoundID;
    unsigned int ID;
    std::vector< unsigned char > pixelData;
    unsigned int width, height;

    std::unordered_map< unsigned int, unsigned int > intParams;

    Texture2D();
    Texture2D(const Texture2D& tex);
    Texture2D(std::string _path, const std::unordered_map< unsigned int, unsigned int >& _intParams = {});
    
    ~Texture2D();

    Texture2D& operator=(const Texture2D& tex);
    Texture2D& operator=(Texture2D&& tex);

    static void Bind(unsigned int id);
    void Bind();
    void SetParameter(unsigned int param, int value); // if necessary add functions for other types like glTexParameterfv etc.
    void SetDefaultParams();
};

#endif