#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <array>
#include <string>
#include <memory>

class Texture {
public:
    Texture();
    ~Texture();

    bool loadFromFile(const std::string &path);
    static std::array<std::shared_ptr<Texture>, 6> createTilesFromFile(const std::string &path);

    // Méthodes pour créer et modifier une texture arbitraire
    void createEmpty(int width, int height);
    void setPixel(int x, int y, const glm::vec4 &color);
    glm::vec4 getPixel(int x, int y) const;
    void updateTexture();

    void use() const;

    // Méthode pour créer une texture damée rouge et noire par défaut
    void createDefaultCheckerboardTexture();

    // Méthodes d'accès aux propriétés de la texture
    int getWidth() const { return _width; }
    int getHeight() const { return _height; }

    std::string getError() {
        std::string str = _error;
        _error.clear();
        return str;
    }

    bool hasError() const {
        return !_error.empty();
    }

private:
    GLuint _textureID;
    bool _isLoaded;
    int _width, _height;
    std::unique_ptr<glm::vec4[]> _pixels; // Utilisation de std::unique_ptr pour gérer dynamiquement les pixels
    std::string _error;

    // Méthode pour libérer la texture
    void free();
};

#endif // TEXTURE_HPP
