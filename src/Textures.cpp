#include "Texture.hpp"
#include "Logger.hpp"

Texture::Texture()
    : _textureID(0), _isLoaded(false), _width(0), _height(0), _pixels(nullptr) {}

Texture::~Texture() {
    free();
}

bool Texture::loadFromFile(const std::string &path) {
    free();

    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        LOG(Error) << "Failed to load image: " << path << " - " << IMG_GetError();
        createDefaultCheckerboardTexture(); // Créer une texture damée par défaut
        updateTexture();
        return false;
    }

    // Extraire les informations de l'image
    _width = surface->w;
    _height = surface->h;
    _pixels = std::make_unique<glm::vec4[]>(_width * _height);

    // Copier les pixels de l'image dans _pixels
    SDL_LockSurface(surface);
    Uint32* pixels = static_cast<Uint32*>(surface->pixels);
    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x) {
            Uint32 pixel = pixels[y * _width + x];
            Uint8 r, g, b, a;
            SDL_GetRGBA(pixel, surface->format, &r, &g, &b, &a);
            _pixels[y * _width + x] = glm::vec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
        }
    }
    SDL_UnlockSurface(surface);
    SDL_FreeSurface(surface);

    updateTexture();
    _isLoaded = true;

    return true;
}

std::array<std::shared_ptr<Texture>, 6> Texture::createTilesFromFile(const std::string &path) {
    std::array<std::shared_ptr<Texture>, 6> textures;
    std::string basePath = path.substr(0, path.find_last_of('/\\') + 1);
    std::string fileName = path.substr(path.find_last_of('/\\') + 1);

    // Charger l'image
    std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    if (!texture->loadFromFile(path)) {
        LOG(Error) << "Failed to load tiles texture: " << path;
        return textures;
    }

    // Diviser l'image en tuiles
    int tileWidth = texture->getWidth() / 4; // Supposer que l'image est divisée en 4x4 tuiles
    int tileHeight = texture->getHeight() / 4;

    textures[0] = std::make_shared<Texture>();
    textures[0]->createEmpty(tileWidth, tileHeight);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            textures[i * 4 + j] = std::make_shared<Texture>();
            textures[i * 4 + j]->createEmpty(tileWidth, tileHeight);
            for (int y = 0; y < tileHeight; ++y) {
                for (int x = 0; x < tileWidth; ++x) {
                    glm::vec4 pixel = texture->getPixel(j * tileWidth + x, i * tileHeight + y);
                    textures[i * 4 + j]->setPixel(x, y, pixel);
                }
            }
            textures[i * 4 + j]->updateTexture();
        }
    }

    return textures;
}

void Texture::createEmpty(int width, int height) {
    free();
    _width = width;
    _height = height;
    _pixels = std::make_unique<glm::vec4[]>(width * height);
    createDefaultCheckerboardTexture(); // Remplir avec une texture damée par défaut
    updateTexture();
}

void Texture::setPixel(int x, int y, const glm::vec4 &color) {
    if (x >= 0 && x < _width && y >= 0 && y < _height) {
        _pixels[y * _width + x] = color;
    }
}

glm::vec4 Texture::getPixel(int x, int y) const {
    if (x >= 0 && x < _width && y >= 0 && y < _height) {
        return _pixels[y * _width + x];
    }
    return glm::vec4(0.0f);
}

void Texture::updateTexture() {
    glGenTextures(1, &_textureID);
    glBindTexture(GL_TEXTURE_2D, _textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_FLOAT, _pixels.get());
    glGenerateMipmap(GL_TEXTURE_2D);

    // Options de filtrage et d'enroulement de texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Libérer la mémoire des pixels après les avoir chargés dans la texture OpenGL
    //_pixels.reset();
}

void Texture::use() const {
    glBindTexture(GL_TEXTURE_2D, _textureID);
}

void Texture::free() {
    if (_textureID != 0) {
        glDeleteTextures(1, &_textureID);
        _textureID = 0;
    }
    _pixels.reset();
}

void Texture::createDefaultCheckerboardTexture() {
    _pixels = std::make_unique<glm::vec4[]>(16 * 16);
    for (int y = 0; y < 16; ++y) {
        for (int x = 0; x < 16; ++x) {
            if ((x / 8 + y / 8) % 2 == 0) {
                _pixels[y * 16 + x] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); // Rouge
            } else {
                _pixels[y * 16 + x] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f); // Noir
            }
        }
    }
}
