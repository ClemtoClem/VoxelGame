/**
 *  _____          _   
 * /__   \_____  _| |_ 
 *   / /\/ _ \ \/ / __|
 *  / / |  __/>  <| |_ 
 *  \/   \___/_/\_\\__|
 *
 * @file Text.cpp
 * @author @ClemtoClem (https://github.com/ClemtoClem)
 * @date 09/07/2024
 */

#ifndef TEXT_HPP
#define TEXT_HPP

#include <GL/glew.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <memory>
#include "Widget.hpp"
#include "../Core/Font.hpp"
#include "../Core/Texture.hpp"
#include "../Core/Color.hpp"

namespace Render2D {

class Text : public Widget {
public:
    Text(const std::string &name, std::shared_ptr<Font> font, const std::string& text, const glm::vec4& color = Color::WHITE);
    ~Text();

    void initDefaultProperties() override;
    void reset() override;

    void setText(const std::string& text);
    std::string getText() const { return _text; }

    void handleEvent(const SDL_Event& evt) override;
    void update(float dt) override;
    void render(const Shader &shader2D) const override;

private:
    std::string _text;
    glm::vec4 _color;
    std::shared_ptr<Font> _font;
    std::shared_ptr<Texture> _texture;
};

} // namespace Render2D

#endif // TEXT_HPP

