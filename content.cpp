#include "content.h"

Content::Content() { }

Content& Content::Instance() {
    static Content inst;
    return inst;    
}

void Content::Load() {
    textures["planks"] = Texture2D("assets/planks.png");

    meshes["backpack"] = Mesh("assets/backpack/backpack.obj");

    meshes["unitcube"] = Mesh("assets/unitcube.obj");
    meshes["unitcube"].ignoreMaterials = true;
    meshes["unitcube"].color = Vector3(1.0f, 0.1f, 0.1f);
    
    //meshes["shotgun"] = Mesh("assets/shotgun_tri.obj");
    //meshes["floor"] = Mesh("assets/floor.obj");
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