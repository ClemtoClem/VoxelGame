#include "Text.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <iostream>
#include "../Core/Color.hpp"
#include "../Core/ResourcesManager.hpp"

namespace Render2D {

Text::Text(const std::string &name, WidgetPtr parent)
 : Widget(name, parent), _text(text), _color(color), _fontName(font) {	
	initProperties();
}

Text::~Text() {
}

void Text::initProperties() {
	Widget::initProperties();
	createProperty("text", BaseProperty::Access::READ_WRITE, _text);
	createProperty("color", BaseProperty::Access::READ_WRITE, _color);
	createProperty("font", BaseProperty::Access::READ_WRITE, _fontName);
}

void Text::reset() {
	Widget::reset();
}

void Text::handleEvent(const SDL_Event& evt) {
	if (!_enable) return;
	handleEventChildren(evt);
}

void Text::update(float dt) {
	if (!_enable) return;
	if (_texture) {
		std::shared_ptr<Font> font = ResourcesManager::getInstance().getFont(_fontName);
		if (font) {
			_texture = font->renderText(_text, _color);
		}
	}
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
