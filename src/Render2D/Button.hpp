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
	Button(const std::string &name, std::shared_ptr<Widget> parent = nullptr);

	void initDefaultProperties() ;
	void reset() ;

	void handleEvent(const SDL_Event &evt) ;
	void update(float dt) ;
	void render(const Shader &shader2D) ;

	void setText(const std::string &text);
	void setFont(const std::shared_ptr<Font> &font);
	void setTextColor(const glm::vec4 &color);
	void setBackgroundColor(const glm::vec4 &color);

private:
	std::shared_ptr<Panel> _background;
	std::shared_ptr<Text> _text;
};

}

#endif // BUTTON_HPP

