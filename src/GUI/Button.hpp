#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Widget.hpp"
#include <functional>
#include <string>
#include <memory>

class Button : public Widget {
public:
    Button(const std::string& fontPath, int fontSize, const std::string& text, const glm::vec4& color);
    ~Button();

    void setCallback(std::function<void()> callback);
    virtual void handleEvent(SDL_Event& evt) override;
    virtual void update(float dt) override;
    virtual void render() const override;

private:
    std::string _text;
    std::function<void()> _callback;
    std::shared_ptr<Widget> _textWidget;
    bool _isHovered = false;
};

#endif // BUTTON_HPP

