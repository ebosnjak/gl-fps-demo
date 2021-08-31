#include "texture2d.h"

unsigned int Texture2D::currentlyBoundID = 0;

Texture2D::Texture2D() {
    glGenTextures(1, &ID);
    Bind();
    SetDefaultParams();
}

Texture2D::Texture2D(const Texture2D& tex) {
    pixelData = tex.pixelData;
    width = tex.width;
    height = tex.height;

    // ID must not be copied so it doesn't break if tex is destroyed and glDeleteTextures is called
    glGenTextures(1, &ID);
    Bind();
    SetDefaultParams(); // for now all textures use the same parameters
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixelData[0]);
}

Texture2D::Texture2D(std::string _path) {
    unsigned int status = lodepng::decode(pixelData, width, height, _path);
    if (status != 0) {
        std::cout << "Failed to load texture from \"" << _path << "\"" << std::endl;
        std::cout << lodepng_error_text(status) << std::endl;
    }

    glGenTextures(1, &ID);
    Bind();
    SetDefaultParams();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixelData[0]);
}

Texture2D::~Texture2D() {
    glDeleteTextures(1, &ID);
}

Texture2D& Texture2D::operator=(const Texture2D& tex) {
    width = tex.width;
    height = tex.height;
    pixelData = tex.pixelData;

    glGenTextures(1, &ID);
    Bind();
    SetDefaultParams();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixelData[0]);

    return (*this);
}

Texture2D& Texture2D::operator=(Texture2D&& tex) {
    ID = tex.ID;
    tex.ID = 0;
    
    width = tex.width;
    height = tex.height;
    pixelData = tex.pixelData;

    return (*this);
}

void Texture2D::Bind() {
    if (ID != currentlyBoundID) {
        glBindTexture(GL_TEXTURE_2D, ID);
        currentlyBoundID = ID;
    }
}

void Texture2D::SetParameter(unsigned int param, int value) {
    Bind();
    glTexParameteri(GL_TEXTURE_2D, param, value);
}

void Texture2D::SetDefaultParams() {
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}