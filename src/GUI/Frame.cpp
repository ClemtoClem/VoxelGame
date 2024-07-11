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
		//glm::vec2 pos = getScreenPosition();
		if (evt.type == SDL_MOUSEMOTION) {
			checkMouseHovered(glm::vec2(evt.motion.x, evt.motion.y));
		}

		handleEventChildren(evt);
	}
}

void Frame::update(float dt) {
	if (_visible) {
		updateTransform(dt);
		updateChildren(dt);
	}
}

void Frame::render(const Shader &shader2D) const {
	if (_visible) {
		shader2D.setMat4("transform", _transform);

		glm::vec2 pos = getScreenPosition();
		glm::vec4 bgColor = (_isHovered && _hoverBackgroundColorIsSet) ? _hoverBackgroundColor : _backgroundColor;

		// Render the frame (e.g., as a colored rectangle)
		if (bgColor.a > 0.0f) {
			shader2D.setVec4("color", bgColor); // Assurez-vous que cette ligne est correcte
			drawFillRectangle(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), bgColor);
		}

		// Render the border
		if (_borderWidth > 0.0f && _borderColor.a > 0.0f) {
			shader2D.setVec4("color", _borderColor); // Assurez-vous que cette ligne est correcte
			drawRectangle(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), _borderColor, 1/_borderWidth);
		}

		// Render all child widgets
		renderChildren(shader2D);
	}
}

