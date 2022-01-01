#include "mesh.h"

Mesh::Mesh() {

}

Mesh::Mesh(const Mesh& m) {
    ignoreMaterials = m.ignoreMaterials;
    color = m.color;
    offsets = m.offsets;
    textures = m.textures;
    vertices = m.vertices;
    indices = m.indices;
    materials = m.materials;
    aabb = m.aabb;

    InitBuffers();
}

Mesh::Mesh(const std::vector< VertexData >& _vertices, const std::vector< unsigned int >& _textures, const std::vector< unsigned int >& _indices) {
    ignoreMaterials = true;
    color = glm::vec3(1.0f, 1.0f, 1.0f);
    textures = _textures;
    vertices = _vertices;
    indices = _indices;

    float left = vertices[0].position.x, bottom = vertices[0].position.y, back = vertices[0].position.z;
    float right = left, top = bottom, front = back;

    for (int i = 1; i < vertices.size(); i++) {
        left = std::min(left, vertices[i].position.x);
        bottom = std::min(bottom, vertices[i].position.y);
        back = std::min(back, vertices[i].position.z);

        right = std::max(right, vertices[i].position.x);
        top = std::max(top, vertices[i].position.y);
        front = std::max(front, vertices[i].position.z);
    }

    aabb.position = glm::vec3(left, bottom, back);
    aabb.size = glm::vec3(right - left, top - bottom, front - back);

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
    ignoreMaterials = false;
    color = glm::vec3(1.0f, 1.0f, 1.0f);
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

    ignoreMaterials = m.ignoreMaterials;
    color = m.color;
    offsets = m.offsets;
    textures = m.textures;
    vertices = m.vertices;
    indices = m.indices;
    materials = m.materials;
    aabb = m.aabb;

    InitBuffers();

    return (*this);
}

Mesh& Mesh::operator=(Mesh&& m) {
    vbo = m.vbo;
    vao = m.vao;

    ignoreMaterials = m.ignoreMaterials;
    color = m.color;
    offsets = m.offsets;
    textures = m.textures;
    vertices = m.vertices;
    indices = m.indices;
    materials = m.materials;
    aabb = m.aabb;

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
    
    if (!ignoreMaterials) {
        prog.SetInt("solidColor", 0);
        for (int i = 0; i < offsets.size(); i++) {
            prog.SetVec3("material.ambient", materials[offsets[i].materialName].ambient);
            prog.SetVec3("material.diffuse", materials[offsets[i].materialName].diffuse);
            prog.SetVec3("material.specular", materials[offsets[i].materialName].specular);
            prog.SetFloat("material.shininess", materials[offsets[i].materialName].shininess);
            prog.SetInt("material.useDiffMap", materials[offsets[i].materialName].useDiffMap);
            prog.SetInt("material.useBumpMap", materials[offsets[i].materialName].useBumpMap);
            prog.SetInt("material.useSpecMap", materials[offsets[i].materialName].useSpecMap);
            
            if (materials[offsets[i].materialName].useDiffMap) {
                prog.SetInt("material.diffuseMap", 0);
                glActiveTexture(GL_TEXTURE0);
                materials[offsets[i].materialName].diffuseMap.Bind();
            }
            if (materials[offsets[i].materialName].useBumpMap) {
                prog.SetInt("material.bumpMap", 1);
                glActiveTexture(GL_TEXTURE1);
                materials[offsets[i].materialName].bumpMap.Bind();
            }
            if (materials[offsets[i].materialName].useSpecMap) {
                prog.SetInt("material.specularMap", 2);
                glActiveTexture(GL_TEXTURE2);
                materials[offsets[i].materialName].specularMap.Bind();
            }

            glDrawElements(GL_TRIANGLES, offsets[i].count, GL_UNSIGNED_INT, (void*)(offsets[i].offset * sizeof(unsigned int)));
        }
    }
    else {
        prog.SetInt("solidColor", 1);
        prog.SetVec3("color", color);

        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    }

    glBindVertexArray(0);
}

void Mesh::LoadOBJ(std::string path) {
    std::vector< glm::vec3 > objVertices, objNormals;
    std::vector< glm::vec2 > objUVs;

    int idx = 0;
    int pieceStart = 0, pieceVCount = 0;
    std::string currentMat = "-";
    
    bool warn = false;

    bool flag = true;
    float left, right, bottom, top, back, front;
    
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

                objVertices.push_back(glm::vec3(x, y, z));

                if (flag) {
                    flag = false;
                    left = x; right = x;
                    bottom = y; top = y;
                    back = z; front = z;
                }
                else {
                    left = std::min(left, x);
                    bottom = std::min(bottom, y);
                    back = std::min(back, z);

                    right = std::max(right, x);
                    top = std::max(top, y);
                    front = std::max(front, z);
                }
            }
            else if (first == "vn") {
                float x, y, z;
                ss >> x >> y >> z;

                objNormals.push_back(glm::vec3(x, y, z));
            }
            else if (first == "vt") {
                float u, v;
                ss >> u >> v;

                objUVs.push_back(glm::vec2(u, v));
            } 
            else if (first == "f") {
                std::string v;
                int count = 0;
                while (ss >> v) {
                    int vi = -1, vti = -1, vni = -1;
                    sscanf(v.c_str(), "%d/%d/%d", &vi, &vti, &vni);
                    sscanf(v.c_str(), "%d//%d", &vi, &vni);
                    vertices.push_back({ objVertices[vi - 1], (vni == -1 ? glm::vec3(0.0f) : objNormals[vni - 1]), (vti == -1 ? glm::vec2(0.0f) : objUVs[vti - 1]) });
                    ++count;
                }

                if (count > 3) {
                    warn = true;
                }

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

    aabb.position = glm::vec3(left, bottom, back);
    aabb.size = glm::vec3(right - left, top - bottom, front - back);

    std::cout << "Success: Loaded 3D model from " << path << std::endl;
    //std::cout << "pos " << left << ", " << bottom << ", " << back << std::endl;
    //std::cout << "size " << aabb.size.X << ", " << aabb.size.Y << ", " << aabb.size.Z << std::endl;
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
                materials[currentName].ambient = glm::vec3(0.1f, 0.1f, 0.1f);
                materials[currentName].diffuse = glm::vec3(0.3f, 0.3f, 0.3f);
                materials[currentName].specular = glm::vec3(0.8f, 0.8f, 0.8f);
                materials[currentName].shininess = 16.0f;
                materials[currentName].useDiffMap = false;
                materials[currentName].useBumpMap = false;
                materials[currentName].useSpecMap = false;
            }
            else if (first == "Ka") {
                float r, g, b;
                ss >> r >> g >> b;
                materials[currentName].ambient = glm::vec3(r, g, b);
            }
            else if (first == "Kd") {
                float r, g, b;
                ss >> r >> g >> b;
                materials[currentName].diffuse = glm::vec3(r, g, b);
            }
            else if (first == "Ks") {
                float r, g, b;
                ss >> r >> g >> b;
                materials[currentName].specular = glm::vec3(r, g, b);
            }
            else if (first == "Ns") {
                float coeff;
                ss >> coeff;
                materials[currentName].shininess = (coeff == 0.0f ? 1.0f : coeff);
            }
            else if (first == "Ke") {
                // emission, not supported
            }
            else if (first == "d") {
                // transparency, not supported
            }
            else if (first == "Ni") {
                // refractive index, not supported
            }
            else if (first == "illum") {
                // illumination model, not supported
            }
            else if (first == "map_Kd") {
                std::string mapPath, folder = path;
                ss >> mapPath;
                materials[currentName].useDiffMap = true;
                while (folder.back() != '/') {
                    folder.pop_back();
                }
                materials[currentName].diffuseMap = Texture2D(folder + mapPath);
            }
            else if (first == "map_Bump") {
                std::string mapPath, folder = path;
                ss >> mapPath;
                materials[currentName].useBumpMap = true;
                while (folder.back() != '/') {
                    folder.pop_back();
                }
                materials[currentName].bumpMap = Texture2D(folder + mapPath);
            }
            else if (first == "map_Ks") {
                std::string mapPath, folder = path;
                ss >> mapPath;
                materials[currentName].useSpecMap = true;
                while (folder.back() != '/') {
                    folder.pop_back();
                }
                materials[currentName].specularMap = Texture2D(folder + mapPath);
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