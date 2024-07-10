#include "Button.hpp"
#include "Text.hpp"
#include "Color.hpp"
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
			int x = evt.motion.x;
			int y = evt.motion.y;
			if (x > pos.x && x < pos.x + _size.x && y > pos.y && y < pos.y + _size.y) {
				_isHovered = true;
			} else {
				_isHovered = false;
			}
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
		glm::vec2 pos = getScreenPosition();
		glm::vec4 bgColor = (_isHovered && _hoverBackgroundColorIsSet) ? _hoverBackgroundColor : _backgroundColor;

		// Render the button background
		
		if (bgColor.a > 0.0f) {
			shader2D.setVec4("color", bgColor); // Assurez-vous que cette ligne est correcte
			glColor4f(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
			glBegin(GL_QUADS);
			glVertex2f(pos.x, pos.y);
			glVertex2f(pos.x + _size.x, pos.y);
			glVertex2f(pos.x + _size.x, pos.y + _size.y);
			glVertex2f(pos.x, pos.y + _size.y);
			glEnd();
		}

		// Render the border
		if (_borderWidth > 0.0f && _borderColor.a > 0.0f) {
			shader2D.setVec4("color", _borderColor); // Assurez-vous que cette ligne est correcte
			glColor4f(_borderColor.r, _borderColor.g, _borderColor.b, _borderColor.a);
			glLineWidth(_borderWidth);
			glBegin(GL_LINE_LOOP);
			glVertex2f(pos.x, pos.y);
			glVertex2f(pos.x + _size.x, pos.y);
			glVertex2f(pos.x + _size.x, pos.y + _size.y);
			glVertex2f(pos.x, pos.y + _size.y);
			glEnd();
		}

		// Render the text widget
		_textWidget->render(shader2D);

		renderChildren(shader2D);
	}
}
