#include "Button.hpp"
#include "Text.hpp"
#include "../Core/Color.hpp"
#include <iostream>

namespace Render2D {

Button::Button(const std::string &name, WidgetPtr parent)
 : Widget(name, parent), _background(std::make_shared<Panel>(name + "_background", shared_from_this())), _text(std::make_shared<Text>(name + "_text", shared_from_this())) {
	initProperties();
}

void Button::initProperties() {
	Widget::initProperties();
	addChild(_background);
	addChild(_text);
	createProperty("background_color", Property::Access::READ_WRITE,
		[this](const Property::Value &value) {
			_background->setProperty("color", value);
		},
		[this]() -> Property::Value& {
			return _background->getProperty("color");
		}
	);
	createProperty("border_color", Property::Access::READ_WRITE,
		[this](const Property::Value &value) {
			_background->setProperty("border_color", value);
		},
		[this]() -> Property::Value& {
			return _background->getProperty("border_color");
		}
	);
	createProperty("border_width", Property::Access::READ_WRITE,
		[this](const Property::Value &value) {
			_background->setProperty("border_width", value);
		},
		[this]() -> Property::Value& {
			return _background->getProperty("border_width");
		}
	);
	createProperty("text_color", Property::Access::READ_WRITE,
		[this](const Property::Value &value) {
			_text->setProperty("color", value);
		},
		[this]() -> Property::Value& {
			return _text->getProperty("color");
		}
	);
}

void Button::reset() {
	Widget::reset();
	_background->reset();
	_text->reset();
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

void Button::handleEvent(const SDL_Event &evt) {
	if (!_enable) return;
	// Gérer les événements spécifiques au bouton ici
}

void Button::update(float dt) {
	if (!_enable) return;
	updateChildren(dt);
}

void Button::render(const Shader &shader2D) const {
	if (!_enable) return;

	_background->render(shader2D);
	_text->render(shader2D);

	renderChildren(shader2D);
}

}