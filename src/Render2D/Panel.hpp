#ifndef PANEL_HPP
#define PANEL_HPP

#include <glm/glm.hpp>
#include <vector>
#include <memory>

#include "Widget.hpp"
#include "../Core/Color.hpp"

namespace Render2D {

class Panel : public Widget {
public:
	Panel(const std::string &name, WidgetPtr parent = nullptr);

	void initDefaultProperties();
	void reset();

	void setColor(const glm::vec4 &color);
	void setBorderColor(const glm::vec4 &color);
	void setBorderWidth(int width);

	glm::vec4 getColor() const;
	glm::vec4 getBorderColor() const;
	int getBorderWidth() const;

	void handleEvent(const SDL_Event &evt) override;
	void update(float dt) override;
	void render(const Shader &shader2D) const override;

private:
	glm::vec4 _color;
	glm::vec4 _border_color;
	int _border_width;
};

}

#endif // PANEL_HPP
