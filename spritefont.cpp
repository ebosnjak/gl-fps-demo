#include "spritefont.h"

SpriteFont::SpriteFont() {
    sheet = nullptr;
}

SpriteFont::SpriteFont(Texture2D* _sheet) {
    sheet = _sheet;
}

void SpriteFont::DrawString(ShaderProgram& prog, const std::string& text, glm::vec2 position, glm::vec2 scale, glm::vec3 color) {
    // ...
    prog.Use();

    Content::Instance().GetMesh("rectangle_topleft")->color = color;
    
    float tw = 70.0f / 1120.0f, th = 80.0f / 640.0f;
    float xpos = position.x;
    
    for (int i = 0; i < text.size(); i++) {
        char c = text[i];
        prog.SetMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(xpos, position.y, 0.0f)) * 
                              glm::scale(glm::mat4(1.0f), glm::vec3(70.0f * scale.x, 80.0f * scale.y, 1.0f)));
        
        if (c == '!' || c == '\'' || c == ',' || c == '.' || c == ':' || c == ';' || c == '`' || c == 'i' || c == 'l' || c == '|') {
            xpos += 20.0f * scale.x;
        }
        else if (c == '#' || c == '&' || c == 'M' || c == 'W' || c == 'm' || c == 'w') {
            xpos += 60.0f * scale.x;
        }
        else {
            xpos += 40.0f * scale.x;
        }

        int row = (int)c / 16;
        int col = (int)c % 16;
        prog.SetVec4("textureRect", glm::vec4(col * tw, row * th, tw, th));
        
        prog.SetInt("tex", 0);
        glActiveTexture(GL_TEXTURE0);
        sheet->Bind();
        Content::Instance().GetMesh("rectangle_topleft")->Draw(prog);
    }

    Content::Instance().GetMesh("rectangle_topleft")->color = glm::vec3(1.0f);
    prog.SetVec4("textureRect", glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
}