/**
 *  _____          _   
 * /__   \_____  _| |_ 
 *   / /\/ _ \ \/ / __|
 *  / / |  __/>  <| |_ 
 *  \/   \___/_/\_\\__|
 *
 * @file Text.cpp
 * @author @ClemtoClem
 * @date 09/07/2024
 */

#ifndef TEXT_HPP
#define TEXT_HPP

#include "Widget.hpp"
#include <GL/glew.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <memory>

class Text : public Widget {
public:
    Text(const std::string& fontPath, int fontSize, const std::string& text, const glm::vec4& color);
    ~Text();

    void setText(const std::string& text);
    std::string getText() const { return _text; }

    virtual void handleEvent(SDL_Event& evt) override;
    virtual void update(float dt) override;
    virtual void render() const override;

private:
    std::string _text;
    TTF_Font* _font;
    GLuint _texture;
    glm::ivec2 _textSize;
};

#endif // TEXT_HPP
