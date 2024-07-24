#include "Panel.hpp"
#include <GL/glew.h>

namespace Render2D {

Panel::Panel(const std::string &name, std::shared_ptr<Widget> parent)
	: Widget(name, parent), _color(Color::WHITE), _border_color(Color::BLACK), _border_width(0) {
	initDefaultProperties();
}

void Panel::initDefaultProperties() {
	Widget::initDefaultProperties();
	setProperty("color", _color, Property::Access::READ_WRITE,
		[this](const Property::Value &value) {
			_color = std::get<glm::vec4>(value);
		},
		[this]() {
			return _color;
		}
	);

	setProperty("border_color", _color, Property::Access::READ_WRITE,
		[this](const Property::Value &value) {
			_border_color = std::get<glm::vec4>(value);
		},
		[this]() {
			return _border_color;
		}
	);
	setProperty("border_width", _color, Property::Access::READ_WRITE,
		[this](const Property::Value &value) {
			_border_width = std::get<int>(value);
		},
		[this]() {
			return _border_width;
		}
	);
}

void Panel::reset() {
	Widget::reset();
	_color = glm::vec4(Color::WHITE);
	_border_color = glm::vec4(Color::BLACK);
	_border_width = 1;
}

void Panel::handleEvent(const SDL_Event &evt) {
	if (!_enable) return;
	// Handle
	handleEventChildren(evt);
}

void Panel::update(float dt) {
	if (!_enable) return;
	// Update properties
	updateProperties();
	updateChildren(dt);
	
}

void Panel::render(const Shader &shader2D) {
	if (!_enable) return;
	// Render the panel

	// Draw rectangle
	if (_color.a > 0.0f) {
		   
	}

	// Render code here, using _color for the panel color
	renderChildren(shader2D);
}


}