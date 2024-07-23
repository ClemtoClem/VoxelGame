#include "Font.hpp"
#include <iostream>
#include <sstream>

#include "Font.hpp"
#include <iostream>
#include <sstream>

Font::Font() : _font(nullptr), _fontSize(24) {
}

Font::~Font() {
    free();
}

void Font::free() {
    if (_font) {
        TTF_CloseFont(_font);
        _font = nullptr;
    }
}

bool Font::hasError() const {
    return !_error.empty();
}

const std::string &Font::getError() const {
    return _error;
}

bool Font::loadFromFile(const std::string &path) {
    free();
    _font = TTF_OpenFont(path.c_str(), _fontSize);
    if (!_font) {
        _error = "Failed to load font: " + std::string(TTF_GetError());
        return false;
    }
    return true;
}

std::shared_ptr<Texture> Font::update() {
    if (!_font) {
        _error = "Font not loaded!";
        return nullptr;
    }

    SDL_Color sdlForegroundColor = {
        static_cast<Uint8>(_foregroundColor.r * 255),
        static_cast<Uint8>(_foregroundColor.g * 255),
        static_cast<Uint8>(_foregroundColor.b * 255),
        static_cast<Uint8>(_foregroundColor.a * 255)
    };

    SDL_Surface* surface = TTF_RenderText_Blended(_font, _text.c_str(), sdlForegroundColor);
    if (!surface) {
        _error = "Failed to render text: " + std::string(TTF_GetError());
        return nullptr;
    }

    _texture = std::make_shared<Texture>(surface);
    SDL_FreeSurface(surface);

    return _texture;
}

std::shared_ptr<Texture> Font::getTexture() {
    return _texture;
}

void Font::text(const std::string &str) {
    _text = str;
}

const std::string &Font::text() const {
    return _text;
}

void Font::fontSize(int size) {
    _fontSize = size;
    if (_font) {
        TTF_SetFontSize(_font, _fontSize);
    }
}

int Font::fontSize() const {
    return _fontSize;
}