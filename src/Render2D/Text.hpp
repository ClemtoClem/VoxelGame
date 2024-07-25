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

#include <GL/glew.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <memory>
#include "../Core/Font.hpp"
#include "../Core/Texture.hpp"
#include "../Core/Color.hpp"
#include "Widget.hpp"
#include "Property.hpp"

namespace Render2D {

class Text : public Widget {
public:
	Text(const std::string &name, WidgetPtr parent);
	~Text();

	void initProperties();
	void reset();

	void handleEvent(const SDL_Event& evt) override;
	void update(float dt) override;
	void render(const Shader &shader2D) const override;

private:
	std::shared_ptr<Texture> _texture;
};

} // namespace Render2D

#endif // TEXT_HPP

