#ifndef FONT_HPP
#define FONT_HPP

#include <string>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <glm/glm.hpp>

class Font {
public:
    Font();
    ~Font();

    bool loadFromFile(const std::string &path, int fontSize);
    GLuint createText(const std::string &text, const glm::vec4 &color, int &width, int &height);

    std::string getError();
    bool hasError() const;

private:
    TTF_Font* _font;
    GLuint _textureID;
    std::string _error;

    void free();
};

#endif // FONT_HPP
