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

    void initDefaultProperties() override;
    void reset() override;

    void handleEvent(const SDL_Event &evt) override;
    void update(float dt) override;
    void render(const Shader &shader2D) override;

private:
	glm::vec4 _color;
};

}

#endif // PANEL_HPP
