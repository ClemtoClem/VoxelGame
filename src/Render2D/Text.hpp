/**
 *  _____          _   
 * /__   \_____  _| |_ 
 *   / /\/ _ \ \/ / __|
 *  / / |  __/>  <| |_ 
 *  \/   \___/_/\_\\__|
 *
 * @file Text.cpp
 * @author @ClemtoClem (https://github.com/ClemtoClem)
 * @date 09/07/2024
 */

#ifndef TEXT_HPP
#define TEXT_HPP

#include <SDL2/SDL_ttf.h>
#include <glm/glm.hpp>
#include <string>
#include <memory>
#include "../Core/Font.hpp"
#include "../Core/Texture.hpp"
#include "../Core/Color.hpp"
#include "Widget.hpp"

namespace Render2D {

class Text : public Widget, public std::enable_shared_from_this<Text> {
public:
	static std::shared_ptr<Text> create(const std::string &name, WidgetPtr parent = nullptr,
		const glm::vec2 &position = glm::vec2(0.0f), const glm::vec2 &scale = glm::vec2(0.0f),
		const std::string &text = "", const std::string &font_name = "arial", int font_size = 12, const glm::vec4 &color = Color::BLACK, const glm::vec4 &hover_color = Color::BLACK);

	Text(const std::string &name, WidgetPtr parent = nullptr,
		const glm::vec2 &position = glm::vec2(0.0f), const glm::vec2 &scale = glm::vec2(0.0f),
		const std::string &text = "", const std::string &font_name = "arial", int font_size = 12, const glm::vec4 &color = Color::BLACK, const glm::vec4 &hover_color = Color::BLACK);

public:
	~Text();

/* -------- PROPERTIES ------- */

	void setText(const std::string &text);

	void setFontName(const std::string &font_name);

	void setFontSize(int size);

	void setColor(const glm::vec4 &color);

	void setHoverColor(const glm::vec4 &color);

	const std::string &getText() const;

	const std::string &getFontName() const;

	int getFontSize() const;

	const glm::vec4 &getColor() const;

	const glm::vec4 &getHoverColor() const;

/* --------- EVENTS ---------- */

	/// @brief Handle an event
	/// @param[in] evt Event
	void handleEvent(SDL_Event& evt) override;

/* --------- UPDATE ---------- */

	/// @brief Update the widget
	/// @param[in] dt Delta time
	void update(float dt) override;

/* --------- RENDER ---------- */

	/// @brief Render the widget
	/// @param[in] shader2D Shader
	void render(const Shader &shader2D) const override;

private:
	std::string _text;
	std::string _font_name;
	int         _font_size;
	glm::vec4   _color;
	glm::vec4   _hover_color;

	FontPtr _font;
	TexturePtr _texture;
};

} // namespace Render2D

#endif // TEXT_HPP

