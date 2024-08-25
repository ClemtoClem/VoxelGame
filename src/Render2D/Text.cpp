#include "Text.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../Core/Color.hpp"
#include "../Core/ResourcesManager.hpp"

namespace Render2D {
std::shared_ptr<Text> Text::create(const std::string &name, WidgetPtr parent,
	const glm::vec2 &position, const glm::vec2 &scale,
	const std::string &text, const std::string &font_name, int font_size, const glm::vec4 &color, const glm::vec4 &hover_color) {
	auto text_ptr = std::make_shared<Text>(name, parent, position, scale, text, font_name, font_size, color, hover_color);
	text_ptr->initialize();
	return text_ptr;
}

Text::Text(const std::string &name, WidgetPtr parent,
	const glm::vec2 &position, const glm::vec2 &scale,
	const std::string &text, const std::string &font_name, int font_size, const glm::vec4 &color, const glm::vec4 &hover_color)
 : Widget(name, parent, position, scale), _text(text), _font_name(font_name), _font_size(font_size), _color(color), _hover_color(hover_color) {
}

Text::~Text() {
}

/* -------- PROPERTIES ------- */

void Text::setText(const std::string &text) {
	if (_text!= text) {
		_text = text;
		_texture = nullptr;
	}
}

void Text::setFontName(const std::string &font_name) {
	if (_font_name!= font_name) {
		_font_name = font_name;
		_font = nullptr;
		_texture = nullptr;
	}
}

void Text::setFontSize(int size) {
	if (_font_size!= size) {
		_font_size = size;
		_font = nullptr;
		_texture = nullptr;
	}
}

void Text::setColor(const glm::vec4 &color) {
	if (_color!= color) {
		_color = color;
		_texture = nullptr;
	}
}

void Text::setHoverColor(const glm::vec4 &color) {
	_hover_color = color;
}

const std::string &Text::getText() const {
	return _text;
}

const std::string &Text::getFontName() const {
	return _font_name;
}

int Text::getFontSize() const {
    return _font_size;
}

const glm::vec4 &Text::getColor() const {
	return _color;
}

const glm::vec4 &Text::getHoverColor() const {
	return _hover_color;
}

/* --------- EVENTS ---------- */

void Text::handleEvent(SDL_Event& evt) {
	if (!_enabled) return;
	if (evt.type == SDL_MOUSEMOTION) {
		glm::vec2 mouse_pos = glm::vec2(evt.motion.x, evt.motion.y);
		if (containsPoint(mouse_pos)) {
			_is_hovered = true;
		} else {
			_is_hovered = false;
		}
	}

	handleEventChildren(evt);
}

/* --------- UPDATE ---------- */

void Text::update(float dt) {
    if (!_enabled) return;

    if (_font == nullptr) {
        _font = ResourcesManager::getInstance()->getFont(_font_name);
		if (_font == nullptr) {
           LOG(Error) << "Could not load font \"" << _font_name << "\".";
            return;
        }
		_font->setSize(_font_size);
    }
    if (_texture == nullptr) {
        _texture = _font->renderText(_text);
    }

    updateTransform();
    updateChildren(dt);
}

/* --------- RENDER ---------- */

void Text::render(const Shader &shader2D) const {
	if (!_enabled) return;

	glm::vec4 color = (_is_hovered)? _hover_color : _color;

	if (_texture && color.a > 0.0f) {
		_texture->bind();

		shader2D.setVec4("color", color);
		shader2D.setInt("textTexture", 0);

		_texture->unbind();
	}

	renderChildren(shader2D);
}

} // namespace Render2D
