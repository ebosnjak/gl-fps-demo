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
#include <unordered_map>

struct VertexData {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct OffsetData {
    int offset;
    int count;
    std::string materialName;
};

struct Material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    bool useDiffMap, useBumpMap, useSpecMap;
    Texture2D diffuseMap, bumpMap, specularMap;
};

class Mesh {
private:
    unsigned int vbo, ebo, vao;
    void LoadOBJ(std::string path);
    void LoadMTL(std::string path);
    void InitBuffers();

public:
    bool ignoreMaterials;
    glm::vec3 color;
    
    std::vector< OffsetData > offsets;
    std::vector< VertexData > vertices;
    std::vector< unsigned int > textures;
    std::vector< unsigned int > indices;
    std::unordered_map< std::string, Material > materials;

    Box aabb;

    Mesh();
    Mesh(const Mesh& m);
    Mesh(const std::vector< VertexData >& _vertices, const std::vector< unsigned int >& _textures, const std::vector< unsigned int >& _indices);
    Mesh(const std::string& _path);

    ~Mesh();

    Mesh& operator=(const Mesh& m);
    Mesh& operator=(Mesh&& m);

    void Draw(ShaderProgram& prog);
};

#endif