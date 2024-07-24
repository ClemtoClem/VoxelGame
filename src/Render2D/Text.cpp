#include "Text.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <iostream>
#include "../Core/Color.hpp"

namespace Render2D {

Text::Text(const std::string &name, WidgetPtr parent, FontPtr font, const std::string& text, const glm::vec4& color)
 : Widget(name, parent), _text(text), _color(color), _font(font) {
	if (!_font) {
		_texture = _font->renderText(_text, Color::WHITE);
	}
	
	initDefaultProperties();
}

Text::~Text() {
}

void Text::initDefaultProperties() {
	Widget::initDefaultProperties();
	createProperty("text", _text, Property::Access::READ_WRITE,
		[this](const Property::Value& value) {
			setText(std::get<std::string>(value));
		},
		[this]() {
			return _text;
		}
	);
	createProperty("color", _color, Property::Access::READ_WRITE,
		[this](const Property::Value& value) {
			_color = std::get<glm::vec4>(value);
		},
		[this]() {
			return _color;
		}
	);
}

void Text::reset() {
	Widget::reset();
}

void Text::setText(const std::string& text) {
	_text = text;
	if (!_font) {
		_texture = _font->renderText(_text, Color::WHITE);
	}
}

void Text::handleEvent(const SDL_Event& evt) {
	if (!_enable) return;
	handleEventChildren(evt);
}

void Text::update(float dt) {
	if (!_enable) return;
	updateChildren(dt);
}

void Text::render(const Shader &shader2D) const {
	if (!_enable) return;

	if (_texture && _color.a > 0.0f) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _texture->getTextureID());

		shader2D.setVec4("color", _color);
		shader2D.setInt("textTexture", 0);

		glDisable(GL_TEXTURE_2D);
	}

	renderChildren(shader2D);
}

} // namespace Render2D
