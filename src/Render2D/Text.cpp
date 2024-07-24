#include "Text.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <iostream>
#include "../Core/Color.hpp"

namespace Render2D {

Text::Text(const std::string &name, std::shared_ptr<Font> font, const std::string& text, const glm::vec4& color)
	: Widget(name), _text(text), _color(color), _font(font) {
	_texture = _font->renderText(_text, Color::WHITE);
}

Text::~Text() {
}

void Text::initDefaultProperties() {
	Widget::initDefaultProperties();
	_properties["text"] = Property(_text, Property::Access::READ_WRITE,
		[this](const Property::Value& value) {
			setText(std::get<std::string>(value));
		},
		[this]() {
			return _text;
		}
	);
	_properties["color"] = Property(_color, Property::Access::READ_WRITE,
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
	_text = "";
	_color = Color::WHITE;
	_texture = nullptr;
}

void Text::setText(const std::string& text) {
	_text = text;
	_texture = _font->renderText(_text, Color::WHITE);
}

void Text::handleEvent(const SDL_Event& evt) {
	if (!_enable) return;
	handleEventChildren(evt);
}

void Text::update(float dt) {
	if (!_enable) return;
	updateProperties();
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
