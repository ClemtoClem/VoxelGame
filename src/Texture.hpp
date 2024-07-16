#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <array>
#include <memory>

class Texture {
public:
    Texture();
    ~Texture();

    bool loadFromFile(const std::string &path);
    static std::array<std::shared_ptr<Texture>, 6> createTilesFromFile(const std::string &path);

    // Méthodes pour créer et modifier une texture arbitraire
    void createEmpty(int width, int height);
    void setPixel(int x, int y, const SDL_Color &color);
    void updateTexture();

    void use() const;

private:
    GLuint _textureID;
    bool _isLoaded;
    int _width, _height;
    std::vector<SDL_Color> _pixels;

    void free();
};

#endif // TEXTURE_HPP
