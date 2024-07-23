#include "Widget.hpp"
#include "../Core/Color.hpp"
#include "../Core/Logger.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Render2D {

#include "Widget.hpp"

Widget::Widget(const std::string &name, std::shared_ptr<Widget> parent)
    : _name(name), _parent(parent), _position(0.0f), _size(1.0f), _rotatePoint(0.5f), _angle(0.0f), _visible(true), _enable(true) {
    if (parent) {
        parent->addChild(shared_from_this());
    }
    initDefaultProperties();
}

Widget::~Widget() {
    deleteChildren();
}

void Widget::initDefaultProperties() {
    _properties["position"] = Property(glm::vec2(0.0f, 0.0f), [this](const Property::Value& value) {
        _position = std::get<glm::vec2>(value);
    });
    _properties["size"] = Property(glm::vec2(1.0f, 1.0f), [this](const Property::Value& value) {
        _size = std::get<glm::vec2>(value);
    });
    _properties["rotatePoint"] = Property(glm::vec2(0.5f, 0.5f), [this](const Property::Value& value) {
        _rotatePoint = std::get<glm::vec2>(value);
    });
    _properties["angle"] = Property(0.0f, [this](const Property::Value& value) {
        _angle = std::get<float>(value);
    });
    _properties["center"] = Property(glm::vec2(0.0f), nullptr, Property::Access::READ_ONLY);
    _properties["enable"] = Property(true, [this](const Property::Value& value) {
        _enable = std::get<bool>(value);
    });
}

void Widget::setProperty(const std::string &property_name, const Property::Value &value, std::function<void(const Property::Value&)> updateFunction, Property::Access access) {
	if (hasProperty(property_name)) {
        _properties[property_name].setValue(value);
        if (updateFunction) {
            _properties[property_name].setUpdateFunction(updateFunction);
        }
    } else {
        _properties[property_name] = Property(value, updateFunction, access);
    }
}

bool Widget::hasProperty(const std::string &property_name) {
    return _properties.find(property_name) != _properties.end();
}

Widget::Value &Widget::getProperty(const std::string &property_name) {
	if (hasProperty(property_name)) {
        return _properties[property_name];
    }
    throw std::runtime_error("Property not found");
}

void Widget::updateProperties() {
    _properties["center"].setValue(center());
    for (auto& [name, property] : _properties) {
        if (property.isModified()) {
            property.update();
            property.resetModified();
        }
    }
}

void Widget::position(const glm::vec2 &vec) {
    _position = vec;
}

void Widget::position(float x, float y) {
    _position = glm::vec2(x, y);
}

glm::vec2 Widget::position() const {
    return _position;
}

void Widget::size(const glm::vec2 &vec) {
    _size = vec;
}

void Widget::size(float w, float h) {
    _size = glm::vec2(w, h);
}

glm::vec2 Widget::size() const {
    return _size;
}

glm::vec2 Widget::center() const {
    return _position + _size * 0.5f;
}

void Widget::rotatePoint(const glm::vec2 &vec) {
    _rotatePoint = vec;
}

glm::vec2 Widget::rotatePoint() const {
    return _rotatePoint;
}

void Widget::angle(float degree) {
    _angle = degree;
}

float Widget::angle() const {
    return _angle;
}

void Widget::enable(bool state) {
    _enable = state;
}

bool Widget::enable() const {
    return _enable;
}

void Widget::addChild(std::shared_ptr<Widget> child) {
    _children.push_back(child);
}

size_t Widget::getNumberOfChildren() const {
    return _children.size();
}

std::shared_ptr<Widget> Widget::getChild(const std::string &name) {
    for (auto &child : _children) {
        if (child->getName() == name) {
            return child;
        }
    }
    return nullptr;
}

std::shared_ptr<Widget> Widget::findWidget(const std::string &path) {
    if (path == _name) {
        return shared_from_this();
    }
    for (auto &child : _children) {
        auto widget = child->findWidget(path);
        if (widget) {
            return widget;
        }
    }
    return nullptr;
}

void Widget::setParent(std::shared_ptr<Widget> parent) {
    _parent = parent;
}

bool Widget::hasParent() const {
    return _parent != nullptr;
}

std::shared_ptr<Widget> Widget::getParent() const {
    return _parent;
}

std::shared_ptr<Widget> Widget::detachChild(const std::string &name) {
    auto it = std::remove_if(_children.begin(), _children.end(), [&](const std::shared_ptr<Widget> &child) {
        return child->getName() == name;
    });

    if (it != _children.end()) {
        auto child = *it;
        _children.erase(it);
        return child;
    }
    return nullptr;
}

void Widget::deleteChild(const std::string &name) {
    auto it = std::remove_if(_children.begin(), _children.end(), [&](const std::shared_ptr<Widget> &child) {
        return child->getName() == name;
    });

    if (it != _children.end()) {
        _children.erase(it);
    }
}

void Widget::deleteChildren() {
    _children.clear();
}

void Widget::handleEventChildren(const SDL_Event &evt) {
    for (auto &child : _children) {
        child->handleEvent(evt);
    }
}

void Widget::updateChildren(float dt) {
    for (auto &child : _children) {
        child->update(dt);
    }
}

void Widget::renderChildren(const Shader &shader2D) const {
    for (auto &child : _children) {
        child->render(shader2D);
    }
}

const std::string &Widget::getName() const {
    return _name;
}

}