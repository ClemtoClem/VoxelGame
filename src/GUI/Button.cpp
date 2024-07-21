#include "Button.hpp"
#include "Text.hpp"
#include "../Core/Color.hpp"
#include <iostream>

Button::Button(const std::string &name, const std::string& fontPath, int fontSize, const std::string& text, const glm::vec4& backgroundColor, const glm::vec4& textColor)
	: Widget(name), _callback(nullptr) {
	setBackgroundColor(backgroundColor);
	_textWidget = std::make_shared<Text>("", fontPath, fontSize, text, glm::vec4(0.0f)); // Text color is set separately
	_textWidget->setParent(this);
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
		glm::vec2 pos = getScreenPosition();
		if (evt.type == SDL_MOUSEMOTION) {
			checkMouseHovered(glm::vec2(evt.motion.x, evt.motion.y));
		}

		if (evt.type == SDL_MOUSEBUTTONDOWN) {
			int x = evt.button.x;
			int y = evt.button.y;
			if (x > pos.x && x < pos.x + _size.x && y > pos.y && y < pos.y + _size.y) {
				if (_callback) {
					_callback();
				}
			}
		}

		handleEventChildren(evt);
	}
}

void Button::update(float dt) {
	if (_visible) {
		glm::vec2 textSize = _textWidget->getSize();
		_textWidget->setPosition((_size.x - textSize.x) / 2.0f, (_size.y - textSize.y) / 2.0f);

		updateChildren(dt);
	}
}

void Button::render(const Shader &shader2D) const {
	if (_visible) {
		//glm::vec2 pos = getScreenPosition();
		glm::vec4 bgColor = (_isHovered && _hoverBackgroundColorIsSet) ? _hoverBackgroundColor : _backgroundColor;

		// Render the button background
		
		if (bgColor.a > 0.0f) {
			shader2D.setVec4("color", bgColor); // Assurez-vous que cette ligne est correcte
			drawFillRectangle(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), bgColor);
		}

		// Render the border
		if (_borderWidth > 0.0f && _borderColor.a > 0.0f) {
			shader2D.setVec4("color", _borderColor); // Assurez-vous que cette ligne est correcte
			drawRectangle(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), _borderColor, 1/_borderWidth);
		}

		// Render the text widget
		_textWidget->render(shader2D);

		renderChildren(shader2D);
	}
}
