#include "Button.hpp"
#include "Text.hpp"
#include "../Core/Color.hpp"
#include <iostream>

namespace Render2D {
std::shared_ptr<Button> Button::create(const std::string &name, WidgetPtr parent,
	const glm::vec2 &position, const glm::vec2 &scale,
	const std::string &text, const glm::vec4 &textColor, const glm::vec4 &backgroundColor) {
	auto button_ptr = std::make_shared<Button>(name, parent, position, scale, text, textColor, backgroundColor);
	button_ptr->initialize();
	return button_ptr;
}

Button::Button(const std::string &name, WidgetPtr parent, 
	const glm::vec2 &position, const glm::vec2 &scale,
	const std::string &text, const glm::vec4 &textColor, const glm::vec4 &backgroundColor)
 : Widget(name, parent, position, scale),
   _background(std::make_shared<Panel>("", nullptr, position, scale)), _text(std::make_shared<Text>("", nullptr, position, scale, text)) {
	_background->setColor(backgroundColor);
	_text->setColor(textColor);
 }

Button::~Button() {
}

void Button::setPosition(const glm::vec2 &position) {
	Widget::setPosition(position);
	_background->setPosition(position);
	glm::vec2 text_position = (position + _scale/2.0f - _text->getScale()/2.0f);
	_text->setPosition(text_position);
}

void Button::setScale(const glm::vec2 &scale) {
	Widget::setScale(scale);
	_background->setScale(scale);
	//_text->setScale(scale);
}

void Button::setRotate(float rotation) {
	Widget::setRotate(rotation);
	_background->setRotate(rotation);
	_text->setRotate(rotation);
}

void Button::setRotateOrigin(const glm::vec2 &origin) {
	Widget::setRotateOrigin(origin);
	_background->setRotateOrigin(origin);
	_text->setRotateOrigin(origin);
}

void Button::setText(const std::string &text) {
	_text->setText(text);
}

void Button::setFontName(const std::string &font_name) {
	_text->setFontName(font_name);
}

void Button::setTextColor(const glm::vec4 &color) {
	_text->setColor(color);
}

void Button::setHoverTextColor(const glm::vec4 &color) {
	_text->setHoverColor(color);
}

void Button::setBackgroundColor(const glm::vec4 &color) {
	_background->setColor(color);
}

void Button::setHoverBackgroundColor(const glm::vec4 &color) {
	_background->setHoverColor(color);
}

void Button::setBorderColor(const glm::vec4 &color) {
	_background->setBorderColor(color);
}

void Button::setHoverBorderColor(const glm::vec4 &color) {
	_background->setHoverBorderColor(color);
}

void Button::setBorderWidth(float width) {
	_background->setBorderWidth(width);
}

void Button::setBorderRadius(float radius) {
	_background->setBorderRadius(radius);
}

const std::string &Button::getText() const {
    return _text->getText();
}

const std::string &Button::getFontName() const {
	return _text->getFontName();
}

const glm::vec4 &Button::getTextColor() const {
	return _text->getColor();
}

const glm::vec4 &Button::getHoverTextColor() const {
	return _text->getHoverColor();
}

const glm::vec4 &Button::getBackgroundColor() const {
	return _background->getColor();
}

const glm::vec4 &Button::getHoverBackgroundColor() const {
	return _background->getHoverColor();
}

const glm::vec4 &Button::getBorderColor() const {
	return _background->getBorderColor();
}

const glm::vec4 &Button::getHoverBorderColor() const {
	return _background->getHoverBorderColor();
}

float Button::getBorderWidth() const {
	return _background->getBorderWidth();
}

float Button::getBorderRadius() const {
	return _background->getBorderRadius();
}

void Button::handleEvent(SDL_Event& evt) {
	if (!_enabled) return;
	// Gérer les événements spécifiques au bouton ici

	_background->handleEvent(evt);
	_text->handleEvent(evt);
	if (_background->isHovered() || _text->isHovered()) {
		_is_hovered = true;
	} else {
		_is_hovered = false;
	}
	handleEventChildren(evt);
}

void Button::update(float dt) {
	if (!_enabled) return;

	_background->update(dt);
	_text->update(dt);
	updateChildren(dt);
}

void Button::render(const Shader &shader2D) const {
	if (!_enabled) return;

	_background->render(shader2D);
	_text->render(shader2D);

	renderChildren(shader2D);
}

}