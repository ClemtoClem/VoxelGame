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
	Panel(const std::string &name, std::shared_ptr<Widget> parent = nullptr);

	void initDefaultProperties() ;
	void reset() ;

	void handleEvent(const SDL_Event &evt) ;
	void update(float dt) ;
	void render(const Shader &shader2D) ;

private:
	glm::vec4 _color;
	glm::vec4 _border_color;
	int _border_width
};

}

#endif // PANEL_HPP
