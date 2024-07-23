#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <functional>
#include <string>
#include <memory>

#include "Widget.hpp"
#include "Panel.hpp"
#include "Text.hpp"

namespace Render2D {

class Button : public Widget {
public:
    Button(const std::string &name, std::shared_ptr<Widget> parent = nullptr);

    void initDefaultProperties() override;
    void reset() override;

    void handleEvent(const SDL_Event &evt) override;
    void update(float dt) override;
    void render(const Shader &shader2D) override;

    void setText(const std::string &text);
    void setFont(const std::shared_ptr<Font> &font);
    void setTextColor(const glm::vec4 &color);
    void setBackgroundColor(const glm::vec4 &color);

private:
    std::shared_ptr<Panel> _background;
    std::shared_ptr<Text> _text;
};

}

#endif // BUTTON_HPP

