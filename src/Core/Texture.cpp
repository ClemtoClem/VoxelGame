#include "Texture.hpp"
#include "Logger.hpp"

Texture::Texture() : _textureID(0), _isLoaded(false), _width(0), _height(0) {}

Texture::Texture(int width, int height, const std::vector<glm::vec4> &pixels)
    : _textureID(0), _isLoaded(false), _width(width), _height(height), _pixels(pixels) {
    updateTexture();
}

Texture::Texture(SDL_Surface *surface) : _textureID(0), _isLoaded(false), _width(0), _height(0) {
    createFromSurface(surface);
}

Texture::~Texture() {
    free();
}

void Texture::free() {
    if (_textureID != 0) {
        glDeleteTextures(1, &_textureID);
        _textureID = 0;
    }
    _isLoaded = false;
    _pixels.clear();
}

bool Texture::loadFromFile(const std::string &path) {
    free();
    
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (!surface) {
        LOG(Error) << "Failed to load texture: " << path << " " << IMG_GetError();
        return false;
    }

	glGenTextures(1, &_textureID);

	glBindTexture(GL_TEXTURE_2D, _textureID);

    int mode = surface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

    _pixels.resize(surface->w * surface->h);
    float alpha = 1.0f;
    for (int i = 0; i < _width * _height; i++) {
        if (mode == GL_RGBA) {
            alpha = static_cast<float>(_pixels[i].a) / 255.0f;
        }
        _pixels[i] = glm::vec4(
            static_cast<float>(_pixels[i].r) / 255.0f,
            static_cast<float>(_pixels[i].g) / 255.0f,
            static_cast<float>(_pixels[i].b) / 255.0f,
            alpha
        );
    }
    
    // Filtrage
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glGenerateMipmap(GL_TEXTURE_2D);

    SDL_FreeSurface(surface);

    LOG(Debug) << "Load texture success";
    _isLoaded = true;
    return true;
}

bool Texture::createFromSurface(SDL_Surface *surface) {
    if (!surface) {
        LOG(Error) << "Failed to create texture from surface: " << IMG_GetError();
        return false;
    }

    free();

    glGenTextures(1, &_textureID);

	glBindTexture(GL_TEXTURE_2D, _textureID);

    int mode = surface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

    _pixels.resize(surface->w * surface->h);
    float alpha = 1.0f;
    for (int i = 0; i < _width * _height; i++) {
        if (mode == GL_RGBA) {
            alpha = static_cast<float>(_pixels[i].a) / 255.0f;
        }
        _pixels[i] = glm::vec4(
            static_cast<float>(_pixels[i].r) / 255.0f,
            static_cast<float>(_pixels[i].g) / 255.0f,
            static_cast<float>(_pixels[i].b) / 255.0f,
            alpha
        );
    }
    
    // Filtrage
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glGenerateMipmap(GL_TEXTURE_2D);

    LOG(Debug) << "Load texture success";
    _isLoaded = true;
    return true;
}

void Texture::create(int width, int height, const glm::vec4 &color) {
    free();

    _width = width;
    _height = height;
    _pixels.resize(_width * _height, color);

    updateTexture();
    _isLoaded = true;
}

void Texture::setPixel(int x, int y, const glm::vec4 &color) {
    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        LOG(Error) << "Pixel coordinates out of bounds: (" << x << ", " << y << ")";
        return;
    }
    _pixels[(y * _width) + x] = color;
}

glm::vec4 Texture::getPixel(int x, int y) const {
    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        LOG(Error) << "Pixel coordinates out of bounds: (" << x << ", " << y << ")";
        return glm::vec4(0.0f, 0.0f, 0.0f, 1.0f); // Return default color if out of bounds
    }
    return _pixels[(y * _width) + x];
}

void Texture::updateTexture() {
    if (_width == 0 || _height == 0) {
        LOG(Error) << "Cannot update texture: texture is not initialized";
        return;
    }

    if (_textureID == 0) {
        glGenTextures(1, &_textureID);
    }
    
    glBindTexture(GL_TEXTURE_2D, _textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_FLOAT, _pixels.data());
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::use() const {
    glBindTexture(GL_TEXTURE_2D, _textureID);
}
