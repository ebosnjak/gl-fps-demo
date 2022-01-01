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
    intParams = tex.intParams;

    // ID must not be copied so it doesn't break if tex is destroyed and glDeleteTextures is called
    glGenTextures(1, &ID);
    Bind();
    for (auto it = intParams.begin(); it != intParams.end(); it++) {
        SetParameter(it->first, it->second);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixelData[0]);
}

Texture2D::Texture2D(std::string _path, const std::unordered_map< unsigned int, unsigned int >& _intParams) {
    unsigned int status = lodepng::decode(pixelData, width, height, _path);
    if (status != 0) {
        std::cout << "Failed to load texture from \"" << _path << "\"" << std::endl;
        std::cout << lodepng_error_text(status) << std::endl;
    }

    glGenTextures(1, &ID);
    Bind();
    
    intParams = _intParams;
    if (intParams.empty()) {
        SetDefaultParams();
    }
    else {
        for (auto it = intParams.begin(); it != intParams.end(); it++) {
            SetParameter(it->first, it->second);
        }
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixelData[0]);
}

Texture2D::~Texture2D() {
    glDeleteTextures(1, &ID);
}

Texture2D& Texture2D::operator=(const Texture2D& tex) {
    width = tex.width;
    height = tex.height;
    pixelData = tex.pixelData;
    intParams = tex.intParams;

    glGenTextures(1, &ID);
    Bind();
    for (auto it = intParams.begin(); it != intParams.end(); it++) {
        SetParameter(it->first, it->second);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixelData[0]);

    return (*this);
}

Texture2D& Texture2D::operator=(Texture2D&& tex) {
    ID = tex.ID;
    tex.ID = 0;
    
    width = tex.width;
    height = tex.height;
    pixelData = tex.pixelData;
    intParams = tex.intParams;

    return (*this);
}

void Texture2D::Bind(unsigned int id) {
    if (id != currentlyBoundID) {
        glBindTexture(GL_TEXTURE_2D, id);
        currentlyBoundID = id;
    }
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
    intParams[param] = value;
}

void Texture2D::SetDefaultParams() {
    SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    SetParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    SetParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}