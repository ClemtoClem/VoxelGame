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
    Texture(const glm::ivec2 &size, const std::vector<glm::vec4> &pixels, bool linearOrNearestFilter = false);
    Texture(SDL_Surface *surface, bool linearOrNearestFilter = false);
    ~Texture();
    
    // Méthode pour libérer la texture
    void free();

    bool loadFromFile(const std::string &path);
    
    bool createFromPixels(const glm::ivec2 &size, const std::vector<glm::vec4> &pixels, bool linearOrNearestFilter = false);
    bool createFromSDLSurface(SDL_Surface *surface, bool linearOrNearestFilter = false);

    // Méthodes pour créer et modifier une texture arbitraire
    void setPixel(const glm::ivec2 &position, const glm::vec4 &color);
    glm::vec4 getPixel(const glm::ivec2 &position) const;

    glm::ivec2 getSize() const;

    void use() const;
    void bind() const;
    void unbind() const;

private:
    bool _isLoaded;
    GLuint _textureID;
    glm::ivec2 _size;
};

using TexturePtr = std::shared_ptr<Texture>;

#endif // TEXTURE_HPP
