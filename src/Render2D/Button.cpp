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
	setProperty("background_color", glm::vec4(Color::LIGHT_GRAY2), Property::Access::READ_WRITE,
		[this](const Property::Value &value) {
			_background->setProperty("color", std::get<glm::vec4>(value));
		},
		[this]() {
			return _background->getProperty("color");
		}
	);
	setProperty("border_color", glm::vec4(Color::Black), Property::Access::READ_WRITE,
		[this](const Property::Value &value) {
			_background->setProperty("border_color", std::get<glm::vec4>(value));
		},
		[this]() {
			return _background->getProperty("border_color");
		}
	);
	setProperty("border_width", 1, Property::Access::READ_WRITE,
		[this](const Property::Value &value) {
			_background->setProperty("border_width", std::get<int>(value));
		},
		[this]() {
			return _background->getProperty("border_width");
		}
	);
	setProperty("text_color", Color::BLACK, Property::Access::READ_WRITE,
		[this](const Property::Value &value) {
			_text->setProperty("color", std::get<glm::vec4>>(value));
		},
		[this]() {
			return _text->getProperty("color");
		}
	);
}

void Button::reset() {
	Widget::reset();
	_background->reset();
	_text->reset();
}

void Button::handleEvent(const SDL_Event &evt) {
	if (!_enable) return;
	// Gérer les événements spécifiques au bouton ici
}

void Button::update(float dt) {
	if (!_enable) return;
	// Update properties
	updateProperties();
	updateChildren(dt);
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