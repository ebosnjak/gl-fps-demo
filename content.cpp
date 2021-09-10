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

    // meshes["backpack"] = Mesh("assets/backpack/backpack.obj");

    meshes["smg"] = Mesh("assets/gun2/ump_tri.obj");

    meshes["unitcube"] = Mesh("assets/unitcube.obj");
    meshes["unitcube"].ignoreMaterials = true;
    meshes["unitcube"].color = Vector3(1.0f, 0.1f, 0.1f);

    //meshes["shotgun"] = Mesh("assets/shotgun_tri.obj");
    meshes["floor"] = Mesh("assets/floor.obj");
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