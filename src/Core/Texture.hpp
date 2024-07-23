/**
 *  _____          _                  
 * /__   \_____  _| |_ _   _ _ __ ___ 
 *   / /\/ _ \ \/ / __| | | | '__/ _ \
 *  / / |  __/>  <| |_| |_| | | |  __/
 *  \/   \___/_/\_\\__|\__,_|_|  \___|
 *
 * @file Texture.hpp
 * @author @ClemtoClem (https://github.com/ClemtoClem)
 * @date 09/07/2024
 * @brief Texture class
 */

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <memory>
#include "Color.hpp"

class Texture {
public:
    Texture();
    Texture(int width, int height, const std::vector<glm::vec4> &pixels);
    Texture(SDL_Surface *surface);
    ~Texture();

    bool loadFromFile(const std::string &path);
    bool createFromSurface(SDL_Surface *surface);

    // Méthodes pour créer et modifier une texture arbitraire
    void setPixel(int x, int y, const glm::vec4 &color);
    glm::vec4 getPixel(int x, int y) const;
    void updateTexture();

    void use() const;

    // Méthodes d'accès aux propriétés de la texture
    void create(int width, int height, const glm::vec4 &color = glm::vec4::WHITE);
    int getWidth() const { return _width; }
    int getHeight() const { return _height; }
    GLuint getTextureID() const { return _textureID; }

private:
    GLuint _textureID;
    bool _isLoaded;
    int _width, _height;
    std::vector<glm::vec4> _pixels;
    
    // Méthode pour libérer la texture
    void free();
};

#endif // TEXTURE_HPP
