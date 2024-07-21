#ifndef FRAME_HPP
#define FRAME_HPP

#include "Widget.hpp"
#include "../Core/Color.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <memory>

class Frame : public Widget {
public:
	Frame(const std::string &name);
	Frame(const std::string &name, const glm::vec2& position, const glm::vec2& size, const glm::vec4& backgroundColor, const glm::vec4& borderColor = Color::BLACK, float borderWidth = 1.0f);

	~Frame();

	virtual void handleEvent(SDL_Event& evt) override;
	virtual void update(float dt) override;
	virtual void render(const Shader &shader2D) const override;

private:
};

#endif // FRAME_HPP
