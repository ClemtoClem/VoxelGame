#include "Texture.hpp"
#include <iostream>

Texture::Texture(): _textureID(0), _isLoaded(false), _width(0), _height(0) {}

Texture::~Texture() {
    free();
}

void Texture::free() {
    if (_isLoaded) {
        glDeleteTextures(1, &_textureID);
        _textureID = 0;
        _isLoaded = false;
    }
}

bool Texture::loadFromFile(const std::string &path) {
    free();

    SDL_Surface *surface = IMG_Load(path.c_str());
    if (!surface) {
        std::cerr << "Failed to load texture: " << IMG_GetError() << std::endl;
        return false;
    }

    glGenTextures(1, &_textureID);
    glBindTexture(GL_TEXTURE_2D, _textureID);

    GLint format = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
    _width = surface->w;
    _height = surface->h;
    glTexImage2D(GL_TEXTURE_2D, 0, format, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, 0);
    SDL_FreeSurface(surface);

    _isLoaded = true;
    return true;
}

void Texture::use() const {
    if (_isLoaded) {
        glBindTexture(GL_TEXTURE_2D, _textureID);
    }
}

std::array<std::shared_ptr<Texture>, 6> Texture::createTilesFromFile(const std::string &path) {
    std::array<std::shared_ptr<Texture>, 6> textures;

    std::string basePath = path.substr(0, path.find_last_of('.'));
    std::array<std::string, 6> suffixes = {"_front", "_back", "_left", "_right", "_top", "_bottom"};
    std::string extension = path.substr(path.find_last_of('.'));

    for (size_t i = 0; i < 6; ++i) {
        std::string tilePath = basePath + suffixes[i] + extension;
        textures[i] = std::make_shared<Texture>();
        if (!textures[i]->loadFromFile(tilePath)) {
            std::cerr << "Failed to load texture: " << tilePath << std::endl;
        }
    }

    return textures;
}
