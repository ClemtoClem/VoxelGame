#include "Button.hpp"
#include "Text.hpp"
#include <iostream>

Button::Button(const std::string& fontPath, int fontSize, const std::string& text, const glm::vec4& backgroundColor, const glm::vec4& textColor)
    : _callback(nullptr) {
    setBackgroundColor(backgroundColor);
    _textWidget = std::make_shared<Text>(fontPath, fontSize, text, glm::vec4(0.0f)); // Text color is set separately
    _textWidget->setColor(textColor);
}

Button::~Button() {}

std::shared_ptr<Widget> Button::getTextWidget() const {
    return _textWidget;
}

void Button::setCallback(std::function<void()> callback) {
    _callback = callback;
}

void Button::handleEvent(SDL_Event& evt) {
    if (_visible) {
        if (evt.type == SDL_MOUSEMOTION) {
            int x = evt.motion.x;
            int y = evt.motion.y;
            if (x > _position.x && x < _position.x + _size.x && y > _position.y && y < _position.y + _size.y) {
                _isHovered = true;
            } else {
                _isHovered = false;
            }
        }

        if (evt.type == SDL_MOUSEBUTTONDOWN) {
            int x = evt.button.x;
            int y = evt.button.y;
            if (x > _position.x && x < _position.x + _size.x && y > _position.y && y < _position.y + _size.y) {
                if (_callback) {
                    _callback();
                }
            }
        }
    }
}

void Button::update(float dt) {
    if (_visible) {
        glm::vec2 textSize = _textWidget->getSize();
        _textWidget->setPosition(_position.x + (_size.x - textSize.x) / 2.0f, _position.y + (_size.y - textSize.y) / 2.0f);
    }
}

void Button::render() const {
    if (_visible) {
        glm::vec4 bgColor = _isHovered ? _hoverBackgroundColor : _backgroundColor;

        // Render the button background
        glColor4f(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        glBegin(GL_QUADS);
        glVertex2f(_position.x, _position.y);
        glVertex2f(_position.x + _size.x, _position.y);
        glVertex2f(_position.x + _size.x, _position.y + _size.y);
        glVertex2f(_position.x, _position.y + _size.y);
        glEnd();

        // Render the border
        if (_borderWidth > 0.0f) {
            glColor4f(_borderColor.r, _borderColor.g, _borderColor.b, _borderColor.a);
            glLineWidth(_borderWidth);
            glBegin(GL_LINE_LOOP);
            glVertex2f(_position.x, _position.y);
            glVertex2f(_position.x + _size.x, _position.y);
            glVertex2f(_position.x + _size.x, _position.y + _size.y);
            glVertex2f(_position.x, _position.y + _size.y);
            glEnd();
        }

        // Render the text widget
        _textWidget->render();
    }
}
