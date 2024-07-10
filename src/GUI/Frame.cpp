#include "Frame.hpp"

#include "Frame.hpp"
#include <GL/glew.h>

Frame::Frame(const std::string &name) : Widget(name) {}

Frame::Frame(const std::string &name, const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &backgroundColor, const glm::vec4 &borderColor, float borderWidth)
  : Widget(name) {
	_position = position;
	_size = size;
	_backgroundColor = backgroundColor;
	_borderColor = borderColor;
	_borderWidth = borderWidth;
}

Frame::~Frame() {}

void Frame::handleEvent(SDL_Event& evt) {
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

		handleEventChildren(evt);
	}
}

void Frame::update(float dt) {
	if (_visible) {
		updateChildren(dt);
	}
}

void Frame::render(const Shader &shader2D) const {
	if (_visible) {
		glm::vec2 pos = getScreenPosition();
		glm::vec4 bgColor = (_isHovered && _hoverBackgroundColorIsSet) ? _hoverBackgroundColor : _backgroundColor;

		// Render the frame (e.g., as a colored rectangle)
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

		// Render all child widgets
		renderChildren(shader2D);
	}
}

