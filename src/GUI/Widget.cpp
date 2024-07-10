#include "Widget.hpp"

Widget::Widget() : _position(0.0f, 0.0f), _size(100.0f, 100.0f) {}

Widget::~Widget() {}

void Widget::setPosition(const glm::vec2& position) {
    _position = position;
}

glm::vec2 Widget::getPosition() const {
    return _position;
}

void Widget::setSize(const glm::vec2& size) {
    _size = size;
}

glm::vec2 Widget::getSize() const {
    return _size;
}

void Widget::setColor(const glm::vec4& color) { 
    _color = color;
}

glm::vec4 Widget::getColor() const {
    return _color;
}

void Widget::setHoverColor(const glm::vec4 &color) {
    _hoverColor = color;
}

glm::vec4 Widget::getHoverColor() const {
    return _hoverColor;
}

void Widget::setBackgroundColor(const glm::vec4& color) {
    _backgroundColor = color;
}

glm::vec4 Widget::getBackgroundColor() const {
    return _backgroundColor;
}

void Widget::setHoverBackgroundColor(const glm::vec4& color) {
    _hoverBackgroundColor = color;
}

glm::vec4 Widget::getHoverBackgroundColor() const {
    return _hoverBackgroundColor;
}

void Widget::setBorderColor(const glm::vec4& color) {
    _borderColor = color;
}

glm::vec4 Widget::getBorderColor() const {
    return _borderColor;
}

void Widget::setBorderWidth(float width) {
    _borderWidth = width;
}

float Widget::getBorderWidth() const {
    return _borderWidth;
}

void Widget::setVisible(bool visible) {
    _visible = visible;
}

bool Widget::isVisible() const {
    return _visible;
}
