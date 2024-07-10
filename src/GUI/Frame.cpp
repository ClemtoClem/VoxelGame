#include "Frame.hpp"

#include "Frame.hpp"
#include <GL/glew.h>

Frame::Frame() {}

Frame::~Frame() {}

void Frame::addWidget(std::shared_ptr<Widget> widget) {
    _widgets.push_back(widget);
}

void Frame::handleEvent(SDL_Event& evt) {
    if (_visible) {
        if (evt.type == SDL_MOUSEMOTION) {
            int x = evt.motion.x;
            int y = evt.motion.y;
            if (x > _position.x && x < _position.x + _size.x && y > _position.y && y < _position.y + _size.y) {
                _isHovered = true;
            } else {
                _isHovered = false;
            }
        }

        for (auto& widget : _widgets) {
            widget->handleEvent(evt);
        }
    }
}

void Frame::update(float dt) {
    if (_visible) {
        for (auto& widget : _widgets) {
            widget->update(dt);
        }
    }
}

void Frame::render() const {
    if (_visible) {
        glm::vec4 bgColor = _isHovered ? _hoverBackgroundColor : _backgroundColor;

        // Render the frame (e.g., as a colored rectangle)
        glColor4f(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        glBegin(GL_QUADS);
        glVertex2f(_position.x, _position.y);
        glVertex2f(_position.x + _size.x, _position.y);
        glVertex2f(_position.x + _size.x, _position.y + _size.y);
        glVertex2f(_position.x, _position.y + _size.y);
        glEnd();

        // Render the border
        if (_borderWidth > 0.0f) {
            glColor4f(_borderColor.r, _borderColor.g, _borderColor.b, _borderColor.a);
            glLineWidth(_borderWidth);
            glBegin(GL_LINE_LOOP);
            glVertex2f(_position.x, _position.y);
            glVertex2f(_position.x + _size.x, _position.y);
            glVertex2f(_position.x + _size.x, _position.y + _size.y);
            glVertex2f(_position.x, _position.y + _size.y);
            glEnd();
        }

        // Render all child widgets
        for (const auto& widget : _widgets) {
            widget->render();
        }
    }
}

