#include "Font.hpp"
#include <iostream>

Font::Font() : _font(nullptr) {
    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
    }
}

Font::~Font() {
    free();
    TTF_Quit();
}

void Font::free() {
    if (_font) {
        TTF_CloseFont(_font);
        _font = nullptr;
    }
}

bool Font::loadFromFile(const std::string &path, int fontSize) {
    free();
    _font = TTF_OpenFont(path.c_str(), fontSize);
    if (!_font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}

GLuint Font::createText(const std::string &text, const glm::vec4 &color, int &width, int &height) {
    if (!_font) {
        std::cerr << "Font not loaded!" << std::endl;
        return 0;
    }

    SDL_Color sdlColor = {
        static_cast<Uint8>(color.r * 255),
        static_cast<Uint8>(color.g * 255),
        static_cast<Uint8>(color.b * 255),
        static_cast<Uint8>(color.a * 255)
    };
    SDL_Surface* surface = TTF_RenderText_Blended(_font, text.c_str(), sdlColor);
    if (!surface) {
        std::cerr << "Failed to render text: " << TTF_GetError() << std::endl;
        return 0;
    }

    width = surface->w;
    height = surface->h;

    glGenTextures(1, &_textureID);
    glBindTexture(GL_TEXTURE_2D, _textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, 0);
    SDL_FreeSurface(surface);

    return textureID;
}
