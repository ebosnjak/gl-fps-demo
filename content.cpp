#include "content.h"

Content::Content() { }

Content& Content::Instance() {
    static Content inst;
    return inst;    
}

void Content::Load() {
    textures["planks"] = Texture2D("assets/planks.png");
}

Texture2D* Content::GetTexture(const std::string& name) {
    return &textures[name];
}

unsigned int Content::GetTextureID(const std::string& name) {
    return textures[name].ID;
}