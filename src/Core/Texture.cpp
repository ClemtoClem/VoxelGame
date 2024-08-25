#include "Texture.hpp"
#include <stdexcept>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "Logger.hpp"
#include "Utils.hpp"

Texture::Texture()
    : _isLoaded(false), _textureID(0), _size(0, 0) {
}

Texture::Texture(const glm::ivec2 &size, const std::vector<glm::vec4> &pixels, bool linearOrNearestFilter)
    : Texture() {
    createFromPixels(size, pixels, linearOrNearestFilter);
}

Texture::Texture(SDL_Surface *surface, bool linearOrNearestFilter)
    : Texture() {
    createFromSDLSurface(surface, linearOrNearestFilter);
}

Texture::~Texture() {
    free();
}

void Texture::free() {
    if (_isLoaded) {
        glDeleteTextures(1, &_textureID);
        _isLoaded = false;
    }
}

bool Texture::loadFromFile(const std::string &path) {
    free(); // Free any existing texture

    SDL_Surface *surface = IMG_Load(path.c_str());
    if (!surface) {
        LOG(Error) << "Failed to load image: " << IMG_GetError();
        return false;
    }

    bool success = createFromSDLSurface(surface);
    SDL_FreeSurface(surface); // Free SDL surface after creating texture
    return success;
}

bool Texture::createFromPixels(const glm::ivec2 &size, const std::vector<glm::vec4> &pixels, bool linearOrNearestFilter) {
    if (size.x <= 0 || size.y <= 0) {
        LOG(Error) << "Invalid texture size";
        return false;
    }
    if (pixels.size() != static_cast<size_t>(size.x * size.y)) {
        LOG(Error) << "Pixel data size does not match texture size";
        return false;
    }
    if (pixels.empty()) {
        LOG(Error) << "Pixel data is empty";
        return false;
    }
    free(); // Free any existing texture

    _size = size;
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glGenTextures(1, &_textureID);
    glBindTexture(GL_TEXTURE_2D, _textureID);

    if (!_textureID) {
        LOG(Error) << "Failed to create texture from pixels";
        return false;
    }

    GLenum format = GL_RGBA;
    GLenum type = GL_FLOAT;

    glTexImage2D(GL_TEXTURE_2D, 0, format, size.x, size.y, 0, format, type, pixels.data());

    if (linearOrNearestFilter) {
        // interpolation linéaire entre les niveaux de mipmap et utilise un filtrage bilinéaire pour la couleur
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        // choisit une valeur résultant de l’interpolation des texels voisins, donnant une couleur approchante
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {
        // choisit la mipmap la plus proche pour la taille du pixel et utilise un filtrage bilinéaire pour la couleur
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        // choisit le pixel dont le centre est le plus proche de la coordonnée de texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    // Limite les coordonnées entre 0 et 1 sur les axes S et T.
    // Les coordonnées plus grandes seront limitées aux bords, résultant en une forme étendue jusqu’aux bords.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, 0);

    _isLoaded = true;
    return true;
}

bool Texture::createFromSDLSurface(SDL_Surface *surface, bool linearOrNearestFilter) {
    if (!surface) {
        LOG(Error) << "Invalid SDL surface";
        return false;
    }
    free(); // Free any existing texture

    _size = glm::ivec2(surface->w, surface->h);

    GLenum format;
    if (surface->format->BytesPerPixel == 4) {
        format = (surface->format->Rmask == 0x000000ff) ? GL_RGBA : GL_BGRA;
    } else {
        format = GL_RGB;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glGenTextures(1, &_textureID);
    glBindTexture(GL_TEXTURE_2D, _textureID);

    if (!_textureID) {
        LOG(Error) << "Failed to create texture from SDL surface";
        return false;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    if (linearOrNearestFilter) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    _isLoaded = true;
    return true;
}

void Texture::setPixel(const glm::ivec2 &position, const glm::vec4 &color) {
    if (!_isLoaded) {
        LOG(Error) << "Texture is not loaded";
        return;
    }

    // Update texture pixel
    glBindTexture(GL_TEXTURE_2D, _textureID);
    glTexSubImage2D(GL_TEXTURE_2D, 0, position.x, position.y, 1, 1, GL_RGBA, GL_FLOAT, &color);
    glBindTexture(GL_TEXTURE_2D, 0);
}

glm::vec4 Texture::getPixel(const glm::ivec2 &position) const {
    if (!_isLoaded) {
        LOG(Error) << "Texture is not loaded";
        return glm::vec4(0.0f);
    }

    // Read pixel from texture (only works if the texture is set to GL_READ_WRITE)
    glBindTexture(GL_TEXTURE_2D, _textureID);
    glm::vec4 color;
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_FLOAT, glm::value_ptr(color));
    glBindTexture(GL_TEXTURE_2D, 0);

    return color;
}

glm::ivec2 Texture::getSize() const {
    return _size;
}

void Texture::use() const {
    if (!_isLoaded) {
        LOG(Error) << "Texture is not loaded";
        return;
    }
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, _textureID);
}

void Texture::bind() const {
    if (!_isLoaded) {
        LOG(Error) << "Texture is not loaded";
        return;
    }
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, _textureID);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}
