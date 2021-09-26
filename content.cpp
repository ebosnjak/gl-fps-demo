#include "content.h"

Content::Content() { }

Content& Content::Instance() {
    static Content inst;
    return inst;    
}

void Content::Load() {
    textures["planks"] = Texture2D("assets/planks.png");
    textures["noise"] = Texture2D(
                            "assets/noise.png",
                            { 
                                { GL_TEXTURE_MIN_FILTER, GL_NEAREST }, 
                                { GL_TEXTURE_MAG_FILTER, GL_NEAREST }, 
                                { GL_TEXTURE_WRAP_S, GL_REPEAT },
                                { GL_TEXTURE_WRAP_T, GL_REPEAT } 
                            });
    
    textures["crosshair"] = Texture2D(
                            "assets/crosshair.png",
                            {
                                { GL_TEXTURE_MIN_FILTER, GL_NEAREST },
                                { GL_TEXTURE_MAG_FILTER, GL_NEAREST },
                                { GL_TEXTURE_WRAP_S, GL_REPEAT },
                                { GL_TEXTURE_WRAP_T, GL_REPEAT }
                            });

    textures["fontsheet"] = Texture2D(
                            "assets/font.png",
                            {
                                { GL_TEXTURE_MIN_FILTER, GL_NEAREST },
                                { GL_TEXTURE_MAG_FILTER, GL_NEAREST },
                                { GL_TEXTURE_WRAP_S, GL_REPEAT },
                                { GL_TEXTURE_WRAP_T, GL_REPEAT }
                            });

    // meshes["backpack"] = Mesh("assets/backpack/backpack.obj");

    //meshes["shotgun"] = Mesh("assets/shotgun_tri.obj");
    meshes["smg"] = Mesh("assets/gun2/ump_tri.obj");

    meshes["unitcube"] = Mesh("assets/unitcube.obj");
    meshes["unitcube"].ignoreMaterials = true;
    meshes["unitcube"].color = glm::vec3(1.0f, 0.1f, 0.1f);

    meshes["floor"] = Mesh("assets/floor.obj");
    meshes["wall"] = Mesh("assets/wall.obj");

    meshes["test"] = Mesh("assets/test.obj");
    meshes["test"].ignoreMaterials = true;
    meshes["test"].color = glm::vec3(0.92f, 0.62f, 0.21f);

    std::vector< VertexData > rectVertices = {
        { glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
        { glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f) },
        { glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
        { glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f) }
    };

    meshes["rectangle"] = Mesh(rectVertices, { }, { 0, 1, 2, 2, 3, 0 });
    meshes["rectangle"].ignoreMaterials = true;
    meshes["rectangle"].color = glm::vec3(1.0f, 1.0f, 1.0f);

    rectVertices = {
        { glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
        { glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f) },
        { glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
        { glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f) }
    };

    meshes["rectangle_topleft"] = Mesh(rectVertices, { }, { 0, 1, 2, 2, 3, 0 });
    meshes["rectangle_topleft"].ignoreMaterials = true;
    meshes["rectangle_topleft"].color = glm::vec3(1.0f, 1.0f, 1.0f);
}

Texture2D* Content::GetTexture(const std::string& name) {
    return &textures[name];
}

unsigned int Content::GetTextureID(const std::string& name) {
    return textures[name].ID;
}

Mesh* Content::GetMesh(const std::string& name) {
    return &meshes[name];
}