#ifndef MESH_H
#define MESH_H

#include "glfuncs.h"
#include "mathhelper.h"
#include "texture2d.h"
#include "shader.h"

#include <vector>

struct VertexData {
    Vector3 position;
    Vector3 normal;
    Vector2 texCoords;
};

class Mesh {
private:
    unsigned int vbo, vao;

public:
    std::vector< VertexData > vertices;
    std::vector< unsigned int > textures;

    Mesh();
    Mesh(const Mesh& m);
    Mesh(const std::vector< VertexData >& _vertices, const std::vector< unsigned int >& _textures);

    ~Mesh();

    Mesh& operator=(const Mesh& m);
    Mesh& operator=(Mesh&& m);

    void Draw();
};

#endif