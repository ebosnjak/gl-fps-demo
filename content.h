#ifndef CONTENT_H
#define CONTENT_H

#include "glfuncs.h"
#include "texture2d.h"
#include "mesh.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

class Content {
private:
    std::unordered_map< std::string, Texture2D > textures;
    std::unordered_map< std::string, Mesh > meshes;

    Content();
    Content(const Content& c) = delete;
    Content(Content&& c) = delete;

    Content& operator=(const Content& c) = delete;
    Content& operator=(Content&& c) = delete;

public:
    static Content& Instance();
    void Load();
    
    Texture2D* GetTexture(const std::string& name);
    unsigned int GetTextureID(const std::string& name);

    Mesh* GetMesh(const std::string& name);
};

#endif