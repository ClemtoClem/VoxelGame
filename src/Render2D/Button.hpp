#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <functional>
#include <string>
#include <memory>

#include "Widget.hpp"
#include "Panel.hpp"
#include "Text.hpp"

namespace Render2D {

class Button : public Widget {
public:
	static std::shared_ptr<Button> create(const std::string &name, WidgetPtr parent = nullptr,
		const glm::vec2 &position = glm::vec2(0.0f), const glm::vec2 &scale = glm::vec2(100.0f, 30.0f),
		const std::string &text = "", const glm::vec4 &textColor = glm::vec4(1.0f), const glm::vec4 &backgroundColor = glm::vec4(0.0f));

	Button(const std::string &name, WidgetPtr parent = nullptr, 
		const glm::vec2 &position = glm::vec2(0.0f), const glm::vec2 &scale = glm::vec2(100.0f, 30.0f),
		const std::string &text = "", const glm::vec4 &textColor = glm::vec4(1.0f), const glm::vec4 &backgroundColor = glm::vec4(0.0f));

public:
	~Button();

/* -------- PROPERTIES ------- */

	/// @brief Set position of the widget
	/// @param[in] position New position
	void setPosition(const glm::vec2 &position) override;

	/// @brief Set size of the widget
	/// @param[in] scale New size
	void setScale(const glm::vec2 &scale) override;

	/// @brief Set rotation around the origin of the widget
	/// @param[in] rotation New rotation
	void setRotate(float rotation) override;

	/// @brief Set rotation origin of the widget
	/// @param[in] origin New rotation origin
	void setRotateOrigin(const glm::vec2 &origin) override;

	/// @brief Set the widget as enabled or disabled
	/// @param[in] enable True if the widget is enabled
	void setText(const std::string &text);

	/// @brief Set the font name used to display the text
	/// @param[in] font_name New font name
	void setFontName(const std::string &font_name);

	/// @brief Set the text color
	/// @param[in] color New text color
	void setTextColor(const glm::vec4 &color);

	/// @brief Set the text color when the mouse is hovering the button
	/// @param[in] color New text color
	void setHoverTextColor(const glm::vec4 &color);

	/// @brief Set the background color
	/// @param[in] color New background color
	void setBackgroundColor(const glm::vec4 &color);

	/// @brief Set the background color when the mouse is hovering the button
	/// @param[in] color New background color
	void setHoverBackgroundColor(const glm::vec4 &color);

	/// @brief Set the border color
	/// @param[in] color New border color
	void setBorderColor(const glm::vec4 &color);

	/// @brief Set the border color when the mouse is hovering the button
	/// @param[in] color New border color
	void setHoverBorderColor(const glm::vec4 &color);

	/// @brief Set the border width
	/// @param[in] width New border width
	void setBorderWidth(float width);

	/// @brief Set the border radius
	/// @param[in] radius New border radius
	void setBorderRadius(float radius);

	const std::string &getText() const;
	const std::string &getFontName() const;
	const glm::vec4 &getTextColor() const;
	const glm::vec4 &getHoverTextColor() const;
	const glm::vec4 &getBackgroundColor() const;
	const glm::vec4 &getHoverBackgroundColor() const;
	const glm::vec4 &getBorderColor() const;
	const glm::vec4 &getHoverBorderColor() const;
	float getBorderWidth() const;
	float getBorderRadius() const;


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
	std::shared_ptr<Panel> _background;
	std::shared_ptr<Text> _text;

	bool _need_update;
};

}

#endif // BUTTON_HPP

