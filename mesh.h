#ifndef MESH_H
#define MESH_H

#include "glfuncs.h"
#include "mathhelper.h"
#include "texture2d.h"
#include "shader.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>

struct VertexData {
    Vector3 position;
    Vector3 normal;
    Vector2 texCoords;
};

class Mesh {
private:
    unsigned int vbo, ebo, vao;
    void LoadFromOBJ(std::string path);
    void InitBuffers();

public:
    std::vector< VertexData > vertices;
    std::vector< unsigned int > textures;
    std::vector< unsigned int > indices;

    Mesh();
    Mesh(const Mesh& m);
    Mesh(const std::vector< VertexData >& _vertices, const std::vector< unsigned int >& _textures, const std::vector< unsigned int >& _indices);
    Mesh(const std::string& _path);

    ~Mesh();

    Mesh& operator=(const Mesh& m);
    Mesh& operator=(Mesh&& m);

    void Draw();
};

#endif