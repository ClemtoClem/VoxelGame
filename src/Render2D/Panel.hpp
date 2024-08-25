#ifndef PANEL_HPP
#define PANEL_HPP

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "../Core/Color.hpp"
#include "Widget.hpp"

namespace Render2D {

class Panel : public Widget {
public:
	static std::shared_ptr<Panel> create(const std::string &name, WidgetPtr parent = nullptr,
		const glm::vec2 &position = glm::vec2(0.0f), const glm::vec2 &scale = glm::vec2(1.0f),
		const glm::vec4 &color = Color::WHITE, const glm::vec4 &border_color = Color::BLACK, float border_width = 1.0f, float border_radius = 0.0f, const glm::vec4 &hover_color = glm::vec4(0.0f), const glm::vec4 &hover_border_color = glm::vec4(0.0f));

	Panel(const std::string &name, WidgetPtr parent = nullptr,
		const glm::vec2 &position = glm::vec2(0.0f), const glm::vec2 &scale = glm::vec2(1.0f),
		const glm::vec4 &color = Color::WHITE, const glm::vec4 &border_color = Color::BLACK, float border_width = 1.0f, float border_radius = 0.0f, const glm::vec4 &hover_color = glm::vec4(0.0f), const glm::vec4 &hover_border_color = glm::vec4(0.0f));

public:
	~Panel();

	virtual bool initialize() override;
	
/* -------- PROPERTIES ------- */

	void setColor(const glm::vec4 &color);

	void setHoverColor(const glm::vec4 &color);

	void setBorderColor(const glm::vec4 &color);

	void setHoverBorderColor(const glm::vec4 &color);

	void setBorderWidth(float width);

	void setBorderRadius(float radius);

	const glm::vec4 &getColor() const;

	const glm::vec4 &getHoverColor() const;

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
	glm::vec4 _color;
	glm::vec4 _hover_color;
	glm::vec4 _border_color;
	glm::vec4 _hover_border_color;
	float _border_width;
	float _border_radius;
};

}

#endif // PANEL_HPP
