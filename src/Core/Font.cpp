#include "Font.hpp"
#include <iostream>
#include <sstream>

#include "Font.hpp"
#include <iostream>
#include <sstream>

Font::Font() : _sdl_font(nullptr), _sdl_fontSize(24) {
}

Font::~Font() {
	free();
}

void Font::free() {
	if (_sdl_font) {
		TTF_CloseFont(_sdl_font);
		_sdl_font = nullptr;
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
	_sdl_font = TTF_OpenFont(path.c_str(), _sdl_fontSize);
	if (!_sdl_font) {
		_error = "Failed to load font: " + std::string(TTF_GetError());
		return false;
	}
	return true;
}

TexturePtr Font::renderText(const std::string &text) const {
	if (!_sdl_font) {
		_error = "Font not loaded!";
		return nullptr;
	}

	SDL_Surface* surface = TTF_RenderText_Blended(_sdl_font, text.c_str(), SDL_Color{ 0xFF, 0xFF, 0xFF, 0xFF});
	if (!surface) {
		_error = "Failed to render text: " + std::string(TTF_GetError());
		return nullptr;
	}

	auto texture = std::make_shared<Texture>(surface);
	SDL_FreeSurface(surface);

	return texture;
}

void Font::setSize(int size) {
	_sdl_fontSize = size;
	if (_sdl_font) {
		TTF_SetFontSize(_sdl_font, _sdl_fontSize);
	}
}

int Font::getSize() const {
	return _sdl_fontSize;
}