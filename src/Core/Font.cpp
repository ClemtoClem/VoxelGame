#include "Font.hpp"
#include <iostream>
#include <sstream>

#include "Font.hpp"
#include <iostream>
#include <sstream>

Font::Font() : _font(nullptr), _fontSize(24) {
}

Font::~Font() {
	free();
}

void Font::free() {
	if (_font) {
		TTF_CloseFont(_font);
		_font = nullptr;
	}
}

bool Font::hasError() const {
	return !_error.empty();
}

const std::string &Font::getError() const {
	return _error;
}

bool Font::loadFromFile(const std::string &path) {
	free();
	_font = TTF_OpenFont(path.c_str(), _fontSize);
	if (!_font) {
		_error = "Failed to load font: " + std::string(TTF_GetError());
		return false;
	}
	return true;
}

TexturePtr Font::renderText(const std::string &text, const glm::vec4 &color) const {
	if (!_font) {
		_error = "Font not loaded!";
		return nullptr;
	}

	SDL_Color sdlcolor = {
		static_cast<Uint8>(color.r * 255),
		static_cast<Uint8>(color.g * 255),
		static_cast<Uint8>(color.b * 255),
		static_cast<Uint8>(color.a * 255)
	};

	SDL_Surface* surface = TTF_RenderText_Blended(_font, text.c_str(), sdlcolor);
	if (!surface) {
		_error = "Failed to render text: " + std::string(TTF_GetError());
		return nullptr;
	}

	auto texture = std::make_shared<Texture>(surface);
	SDL_FreeSurface(surface);

	return texture;
}

void Font::fontSize(int size) {
	_fontSize = size;
	if (_font) {
		TTF_SetFontSize(_font, _fontSize);
	}
}

int Font::fontSize() const {
	return _fontSize;
}