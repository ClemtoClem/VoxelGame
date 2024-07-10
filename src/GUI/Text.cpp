#include "Text.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <iostream>

Text::Text(const std::string& fontPath, int fontSize, const std::string& text, const glm::vec4& color)
    : _text(text) {
    _color = color;
    _font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!_font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        exit(1);
    }
    setText(text);
}

Text::~Text() {
    if (_font) {
        TTF_CloseFont(_font);
    }
    if (_texture) {
        glDeleteTextures(1, &_texture);
    }
}

void Text::setText(const std::string& text) {
    _text = text;
    if (_texture) {
        glDeleteTextures(1, &_texture);
    }

    SDL_Color sdlColor = { 
        static_cast<Uint8>(_color.r * 255), 
        static_cast<Uint8>(_color.g * 255), 
        static_cast<Uint8>(_color.b * 255), 
        static_cast<Uint8>(_color.a * 255) 
    };
    SDL_Surface* surface = TTF_RenderText_Blended(_font, text.c_str(), sdlColor);
    if (!surface) {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        return;
    }

    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    _textSize = glm::ivec2(surface->w, surface->h);
    _size = glm::vec2(_textSize); // Update widget size

    SDL_FreeSurface(surface);
}

void Text::handleEvent(SDL_Event& evt) {
    // Text widget doesn't handle events directly
}

void Text::update(float dt) {
    // Update logic for text if needed
}

void Text::render() const {
    // Render background
    glColor4f(_backgroundColor.r, _backgroundColor.g, _backgroundColor.b, _backgroundColor.a);
    glBegin(GL_QUADS);
    glVertex2f(_position.x, _position.y);
    glVertex2f(_position.x + _size.x, _position.y);
    glVertex2f(_position.x + _size.x, _position.y + _size.y);
    glVertex2f(_position.x, _position.y + _size.y);
    glEnd();

    // Render border
    if (_borderWidth > 0.0f) {
        glColor4f(_borderColor.r, _borderColor.g, _borderColor.b, _borderColor.a);
        glLineWidth(_borderWidth);
        glBegin(GL_LINE_LOOP);
        glVertex2f(_position.x, _position.y);
        glVertex2f(_position.x + _size.x, _position.y);
        glVertex2f(_position.x + _size.x, _position.y + _size.y);
        glVertex2f(_position.x, _position.y + _size.y);
        glEnd();
    }

    // Render text
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _texture);

    glColor4f(_color.r, _color.g, _color.b, _color.a);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(_position.x, _position.y);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(_position.x + _textSize.x, _position.y);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(_position.x + _textSize.x, _position.y + _textSize.y);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(_position.x, _position.y + _textSize.y);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
