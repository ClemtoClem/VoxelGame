#include "Text.hpp"
#include "Color.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <iostream>

Text::Text(const std::string &name, const std::string& fontPath, int fontSize, const std::string& text, const glm::vec4& color)
	: Widget(name), _text(text) {
	_color = color;
	_backgroundColor = Color::TRANSPARENT;
	_font = TTF_OpenFont(fontPath.c_str(), fontSize);
	if (!_font) {
		std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
		exit(1);
	}
	setText(text);
}

Text::~Text() {
	if (_font) {
		TTF_CloseFont(_font);
	}
	if (_texture) {
		glDeleteTextures(1, &_texture);
	}
}

void Text::setText(const std::string& text) {
	_text = text;
	if (_texture) {
		glDeleteTextures(1, &_texture);
	}

	SDL_Color sdlColor = { 
		static_cast<Uint8>(_color.r * 255), 
		static_cast<Uint8>(_color.g * 255), 
		static_cast<Uint8>(_color.b * 255), 
		static_cast<Uint8>(_color.a * 255) 
	};
	SDL_Surface* surface = TTF_RenderText_Blended(_font, text.c_str(), sdlColor);
	if (!surface) {
		std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
		return;
	}

	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Débinding de la texture
    glBindTexture(GL_TEXTURE_2D, 0);

	_textSize = glm::ivec2(surface->w, surface->h);
	_size = glm::vec2(_textSize); // Update widget size

	SDL_FreeSurface(surface);
}

void Text::handleEvent(SDL_Event& evt) {
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

void Text::update(float dt) {
	if (_visible) {
		updateChildren(dt);
	}
}

void Text::render(const Shader &shader2D) const {
	if (_visible) {
		glm::vec2 pos = getScreenPosition();
			
		// Render background
		// Render the frame (e.g., as a colored rectangle)
		glm::vec4 bgColor = (_isHovered && _hoverBackgroundColorIsSet) ? _hoverBackgroundColor : _backgroundColor;
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

		// Render border
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

		// Render text
		glm::vec4 color = (_isHovered && _hoverColorIsSet) ? _hoverColor : _color;
		if (color.a > 0.0f) {
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _texture);

			shader2D.setVec4("color", color);
			shader2D.setInt("textTexture", 0);
			glColor4f(color.r, color.g, color.b, color.a);

			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f); glVertex2f(pos.x, pos.y);
			glTexCoord2f(1.0f, 1.0f); glVertex2f(pos.x + _textSize.x, pos.y);
			glTexCoord2f(1.0f, 0.0f); glVertex2f(pos.x + _textSize.x, pos.y + _textSize.y);
			glTexCoord2f(0.0f, 0.0f); glVertex2f(pos.x, pos.y + _textSize.y);
			glEnd();

			glDisable(GL_TEXTURE_2D);
		}

		renderChildren(shader2D);
	}
}