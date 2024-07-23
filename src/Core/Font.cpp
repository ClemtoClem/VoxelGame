#include "Font.hpp"
#include <iostream>
#include <sstream>

Font::Font() : _font(nullptr) {
}

Font::~Font() {
    free();
}

bool Font::hasError() const {
    return !_error.empty();
}

const std::string &Font::getError() const
{
    std::string err = _error;
    _error.clear();
    return err;
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
        std::stringstream ss;
        ss << "Failed to load font: " << TTF_GetError();
        _error = ss.str();
        return false;
    }
    return true;
}

GLuint Font::createText(const std::string &text, const glm::vec4 &color, int &width, int &height) {
    if (!_font) {
        std::stringstream ss;
        ss << "Font not loaded!";
        _error = ss.str();
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
        std::stringstream iss;
        iss << "Failed to render text: " << TTF_GetError();
        _error = iss.str();
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
    return _textureID;
}

void Font::setSize(int size) {
    if (!_font) {
        LOG(Error) << "Font not loaded!";
        return;
    }
    TTF_SetFontSize(_font, size);
}
