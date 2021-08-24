#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "dependencies/lodepng.h"
#include "glfuncs.h"

#include <iostream>
#include <vector>

class Texture2D {
public:
    static unsigned int currentlyBoundID;
    unsigned int ID;
    std::vector< unsigned char > pixelData;
    unsigned int width, height;

    Texture2D();
    Texture2D(const Texture2D& tex) = delete;
    Texture2D(std::string _path);
    
    ~Texture2D();

    Texture2D& operator=(const Texture2D& tex) = delete;
    Texture2D& operator=(Texture2D&& tex);

    void Bind();
    void SetParameter(unsigned int param, int value); // if necessary add functions for other types like glTexParameterfv etc.
    void SetDefaultParams();
};

#endif