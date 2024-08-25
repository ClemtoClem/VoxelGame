/**
 *    ___           _   
 *   / __\__  _ __ | |_ 
 *  / _\/ _ \| '_ \| __|
 * / / | (_) | | | | |_ 
 * \/   \___/|_| |_|\__|
 *
 * @file Font.hpp
 * @author @ClemtoClem (https://github.com/ClemtoClem)
 * @date 09/07/2024
 * @brief Font class
 */

#ifndef FONT_HPP
#define FONT_HPP

#include <string>
#include <memory>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <glm/glm.hpp>
#include "Texture.hpp"
#include "Color.hpp"

class Font {
public:
	Font();
	~Font();

	bool hasError() const;
	const std::string &getError() const;

	bool loadFromFile(const std::string &path);
	TexturePtr renderText(const std::string &text) const;

	void setSize(int size);
	int getSize() const;

private:
	TTF_Font* _sdl_font;
	int _sdl_fontSize;
	mutable std::string _error;

	void free();
};

using FontPtr = std::shared_ptr<Font>;

#endif // FONT_HPP
