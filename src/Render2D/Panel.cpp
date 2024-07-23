#include "Panel.hpp"
#include <GL/glew.h>

namespace Render2D {

Panel::Panel(const std::string &name, std::shared_ptr<Widget> parent)
    : Widget(name, parent), _color(Color::WHITE) {
    initDefaultProperties();
}

void Panel::initDefaultProperties() {
	Widget::initDefaultProperties();
    setProperty("color", _color, [this](const Property::Value &value) {
        _color = std::get<glm::vec4>(value);
    });
}

void Panel::reset() {
    _color = glm::vec4(Color::WHITE);
    // Reset other properties as needed
}

void Panel::handleEvent(const SDL_Event &evt) {
    if (!_enable) return;
    // Handle
    handleEventChildren(evt);
}

void Panel::update(float dt) {
    if (!_enable) return;
    // Update properties
    updateProperties();
    updateChildren(dt);
    
}

void Panel::render(const Shader &shader2D) {
    if (!_enable) return;
    // Render the panel

    // Draw rectangle
    if (_color.a > 0.0f) {
           
    }

    // Render code here, using _color for the panel color
    renderChildren(shader2D);
}


}