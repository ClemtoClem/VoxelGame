#include "Button.hpp"
#include "Text.hpp"
#include "../Core/Color.hpp"
#include <iostream>

namespace Render2D {

Button::Button(const std::string &name, std::shared_ptr<Widget> parent)
    : Widget(name, parent), _background(std::make_shared<Panel>(name + "_background", shared_from_this())), _text(std::make_shared<Text>(name + "_text", shared_from_this())) {
    initDefaultProperties();
}

void Button::initDefaultProperties() {
	Widget::initDefaultProperties();
    addChild(_background);
    addChild(_text);
    _background->setProperty("color", glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), [this](const Property::Value &value) {
		_background->setProperty("color", std::get<glm::vec4>(value));
	});
}

void Button::reset() {
    _background->reset();
    _text->reset();
}

void Button::handleEvent(const SDL_Event &evt) {
    if (!_enable) return;
    // Gérer les événements spécifiques au bouton ici
}

void Button::update(float dt) {
    if (!_enable) return;
    // Mettre à jour les propriétés spécifiques au bouton ici
}

void Button::render(const Shader &shader2D) {
    if (!_enable) return;

    _background->render(shader2D);
    _text->render(shader2D);

    renderChildren(shader2D);
}

void Button::setText(const std::string &text) {
    _text->setText(text);
}

void Button::setFont(const std::shared_ptr<Font> &font) {
    _text->setFont(font);
}

void Button::setTextColor(const glm::vec4 &color) {
    _text->setColor(color);
}

void Button::setBackgroundColor(const glm::vec4 &color) {
    _background->setProperty("color", color);
}

}