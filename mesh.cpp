#include "mesh.h"

Mesh::Mesh() {

}

Mesh::Mesh(const Mesh& m) {
    offsets = m.offsets;
    textures = m.textures;
    vertices = m.vertices;
    indices = m.indices;
    materials = m.materials;

    InitBuffers();
}

Mesh::Mesh(const std::vector< VertexData >& _vertices, const std::vector< unsigned int >& _textures, const std::vector< unsigned int >& _indices) {
    textures = _textures;
    vertices = _vertices;
    indices = _indices;

    int removed = 0;
    while (textures.size() > GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS) {
        textures.pop_back();
        ++removed;
    }

    if (removed > 0) {
        std::cout << "Warning: Texture array too large, last " << removed << " elements were erased." << std::endl;
    }

    InitBuffers();
}

Mesh::Mesh(const std::string& _path) {
    LoadOBJ(_path);
    InitBuffers();
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

Mesh& Mesh::operator=(const Mesh& m) {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    vao = 0; vbo = 0;

    offsets = m.offsets;
    textures = m.textures;
    vertices = m.vertices;
    indices = m.indices;
    materials = m.materials;

    InitBuffers();

    return (*this);
}

Mesh& Mesh::operator=(Mesh&& m) {
    vbo = m.vbo;
    vao = m.vao;

    offsets = m.offsets;
    textures = m.textures;
    vertices = m.vertices;
    indices = m.indices;
    materials = m.materials;

    m.vbo = 0; m.vao = 0;

    InitBuffers();

    return (*this);
}

void Mesh::Draw(ShaderProgram& prog) {
    prog.Use();
    glBindVertexArray(vao);
    
    /*for (int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        Texture2D::Bind(textures[i]);
    }*/
    
    for (int i = 0; i < offsets.size(); i++) {
        prog.SetVec3("material.ambient", materials[offsets[i].materialName].ambient);
        prog.SetVec3("material.diffuse", materials[offsets[i].materialName].diffuse);
        prog.SetVec3("material.specular", materials[offsets[i].materialName].specular);
        prog.SetFloat("material.shininess", 8.0f);

        glDrawElements(GL_TRIANGLES, offsets[i].count, GL_UNSIGNED_INT, (void*)(offsets[i].offset * sizeof(unsigned int)));
    }

    glBindVertexArray(0);
}

void Mesh::LoadOBJ(std::string path) {
    std::vector< Vector3 > objVertices, objNormals;
    std::vector< Vector2 > objUVs;

    int idx = 0;
    int pieceStart = 0, pieceVCount = 0;
    std::string currentMat = "-";
    
    bool warn = false;
    
    std::ifstream objFile(path);
    if (objFile.is_open()) {
        std::string line;
        while (std::getline(objFile, line)) {
            std::stringstream ss(line);
            std::string first;
            ss >> first;

            if (first == "v") {
                float x, y, z;
                ss >> x >> y >> z;

                objVertices.push_back(Vector3(x, y, z));
            }
            else if (first == "vn") {
                float x, y, z;
                ss >> x >> y >> z;

                objNormals.push_back(Vector3(x, y, z));
            }
            else if (first == "vt") {
                float u, v;
                ss >> u >> v;

                objUVs.push_back(Vector2(u, v));
            } 
            else if (first == "f") {
                std::string v;
                int count = 0;
                while (ss >> v) {
                    int vi = -1, vti = -1, vni = -1;
                    sscanf(v.c_str(), "%d/%d/%d", &vi, &vti, &vni);
                    sscanf(v.c_str(), "%d//%d", &vi, &vni);
                    vertices.push_back({ objVertices[vi - 1], objNormals[vni - 1], objUVs[vti - 1] });
                    ++count;
                }

                if (count > 3) {
                    warn = true;
                }

                // for now, indexing is used only on individual faces
                for (int i = 1; i < count - 1; i++) {
                    indices.push_back(idx);
                    indices.push_back(idx + i);
                    indices.push_back(idx + i + 1);
                    pieceVCount += 3;
                }

                idx += count;
            }
            else if (first == "mtllib") {
                std::string mtlPath, folder = path;
                while (folder.back() != '/') {
                    folder.pop_back();
                }

                ss >> mtlPath;
                LoadMTL(folder + mtlPath);
            }
            else if (first == "usemtl") {
                if (pieceVCount > 0) {
                    offsets.push_back({ pieceStart, pieceVCount, currentMat });
                }

                ss >> currentMat;
                pieceStart = indices.size();
                pieceVCount = 0;
            }
        }
    }
    else {
        std::cout << "Error: Cannot open file \"" << path << "\" for reading." << std::endl;
        return;
    }

    if (pieceVCount > 0) {
        offsets.push_back({ pieceStart, pieceVCount, currentMat });
    }

    if (warn) {
        std::cout << "Warning: \"" << path << "\" doesn't have triangulated faces, this may cause issues" << std::endl;
    }
}

void Mesh::LoadMTL(std::string path) {
    std::ifstream mtlFile(path);
    if (mtlFile.is_open()) {
        std::string line;
        std::string currentName;
        while (std::getline(mtlFile, line)) {
            std::stringstream ss(line);
            std::string first;
            ss >> first;

            if (first == "newmtl") {
                ss >> currentName;
            }
            else if (first == "Ka") {
                float r, g, b;
                ss >> r >> g >> b;
                materials[currentName].ambient = Vector3(r, g, b);
            }
            else if (first == "Kd") {
                float r, g, b;
                ss >> r >> g >> b;
                materials[currentName].diffuse = Vector3(r, g, b);
            }
            else if (first == "Ks") {
                float r, g, b;
                ss >> r >> g >> b;
                materials[currentName].specular = Vector3(r, g, b);
            }
        }
    }
    else {
        std::cout << "Error: Cannot open mtllib \"" << path << "\"" << std::endl;
        return;
    }
}

void Mesh::InitBuffers() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexData), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glBindVertexArray(0);
}