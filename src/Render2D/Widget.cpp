#include "Widget.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "../Core/Logger.hpp"

namespace Render2D {
Widget::Widget(const std::string &name, std::shared_ptr<Widget> parent,
    const glm::vec2 &position, const glm::vec2 &scale, float rotation, const glm::vec2 &rotateOrigin)
    : Node(name), _position(position), _scale(scale), _angle(rotation), _rotateOrigin(rotateOrigin), _enabled(true), _needs_update_transform(true), _is_init(false) {}

Widget::~Widget() {
    deleteAllChildren();
}

bool Widget::initialize() {
    if (getParent() && !_is_init) {
        LOG(Info) << "Added widget \"" << getName() << "\" to parent \"" << getParent()->getName() << "\"";
        if (!getParent()->insertChildToBottom(shared_from_this())) {
            LOG(Error) << "Failed to add widget \"" << getName() << "\" to parent \"" << getParent()->getName() << "\"";
            return false;
        }
        _is_init = true;
    }
    return true;
}

/* -------- PROPERTIES -------- */

void Widget::setPosition(const glm::vec2 &position) {
    _position = position;
    _needs_update_transform = true;
}

void Widget::setScale(const glm::vec2 &scale) {
    _scale = scale;
    _needs_update_transform = true;
}

void Widget::setRotate(float rotation) {
    _angle = rotation;
    _needs_update_transform = true;
}

void Widget::setRotateOrigin(const glm::vec2 &origin) {
    _rotateOrigin = origin;
    _needs_update_transform = true;
}

void Widget::setEnable(bool enable) {
    _enabled = enable;
}

glm::vec2 Widget::getPosition() const {
    return _position;
}

glm::vec2 Widget::getAbsolutePosition() const {
    if (getParent()) {
        return _position + std::dynamic_pointer_cast<Widget>(getParent())->getAbsolutePosition();
    } else {
        return _position;
    }
}

glm::vec2 Widget::getScale() const {
    return _scale;
}

float Widget::getRotate() const {
    return _angle;
}

glm::vec2 Widget::getRotateOrigin() const {
    return _rotateOrigin;
}

bool Widget::isEnable() const {
    return _enabled;
}

/* ------ BOUNDING BOX ------- */

std::array<glm::vec2, 4> Widget::getTransformedBoundingBox() const {
    glm::vec2 halfSize = _scale * 0.5f;

    // Local corners of the bounding box
    std::array<glm::vec2, 4> corners = {
        glm::vec2(-halfSize.x, -halfSize.y),
        glm::vec2(halfSize.x, -halfSize.y),
        glm::vec2(halfSize.x, halfSize.y),
        glm::vec2(-halfSize.x, halfSize.y)
    };

    std::array<glm::vec2, 4> transformedCorners;
    glm::mat4 transform = _transform;
    for (int i = 0; i < 4; ++i) {
        glm::vec4 transformedCorner = transform * glm::vec4(corners[i], 0.0f, 1.0f);
        transformedCorners[i] = glm::vec2(transformedCorner);
    }

    return transformedCorners;
}

bool Widget::overlapsWith(const Widget &other) const {
    auto bbox1 = getAABB(getTransformedBoundingBox());
    auto bbox2 = getAABB(other.getTransformedBoundingBox());

    // Check for overlap
    return !(bbox1.z < bbox2.x || bbox1.x > bbox2.z || bbox1.w < bbox2.y || bbox1.y > bbox2.w);
}

bool Widget::containsPoint(const glm::vec2 &point) const {
    glm::vec4 transformedPoint = glm::inverse(_transform) * glm::vec4(point, 0.0f, 1.0f);
    glm::vec2 localPoint = glm::vec2(transformedPoint);

    glm::vec2 halfSize = _scale * 0.5f;
    return localPoint.x >= -halfSize.x && localPoint.x <= halfSize.x && localPoint.y >= -halfSize.y && localPoint.y <= halfSize.y;
}

void Widget::updateTransform() {
    if (_needs_update_transform) {
	    glm::vec2 absolute_pos = getAbsolutePosition();
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(absolute_pos, 0.0f));
        glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(_angle), glm::vec3(_rotateOrigin, 0.0f));
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(_scale, 1.0f));
        _transform = translate * rotate * scale;
        _needs_update_transform = false;
    }
}

glm::vec4 Widget::getAABB(const std::array<glm::vec2, 4> &corners) const {
    glm::vec2 min = corners[0];
    glm::vec2 max = corners[0];
    for (const auto &corner : corners) {
        min = glm::min(min, corner);
        max = glm::max(max, corner);
    }
    return glm::vec4(min, max);
}

/* -------- EVENTS ---------- */

void Widget::handleEventChildren(SDL_Event& evt) {
    for (auto child = getFirstChild(); child != nullptr; child = child->getNext()) {
        auto widgetChild = std::dynamic_pointer_cast<Widget>(child);
        if (widgetChild) {
            widgetChild->handleEvent(evt);
        }
    }
}

bool Widget::isHovered() const {
    return _is_hovered;
}

bool Widget::isSelected() const
{
    return false;
}

/* -------- UPDATE ---------- */

void Widget::updateChildren(float dt) {
    for (auto child = getFirstChild(); child != nullptr; child = child->getNext()) {
        auto widgetChild = std::dynamic_pointer_cast<Widget>(child);
        if (widgetChild) {
            widgetChild->update(dt);
        }
    }
}

/* -------- RENDER ---------- */

void Widget::renderChildren(const Shader &shader2D) const {
    for (auto child = getFirstChild(); child != nullptr; child = child->getNext()) {
        auto widgetChild = std::dynamic_pointer_cast<Widget>(child);
        if (widgetChild) {
            widgetChild->render(shader2D);
        }
    }
}

} // namespace Render2D
