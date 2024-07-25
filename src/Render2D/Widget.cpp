#include <glm/gtc/matrix_transform.hpp>
#include "../Core/Color.hpp"
#include "../Core/Logger.hpp"
#include "../Core/Utils.hpp"
#include "../Core/Property.hpp"
#include "Widget.hpp"

namespace Render2D {

Widget::Widget(const std::string &name, std::shared_ptr<Widget> parent)
	: _name(name), _parent(parent), _position(0.0f), _size(1.0f), _rotatePoint(0.5f), _angle(0.0f), _enable(true) {
	if (parent) {
		parent->addChild(shared_from_this());
	}
}

Widget::~Widget() {
	deleteChildren();
}

const std::string &Widget::getName() const {
	return _name;
}

void Widget::initProperties() {
	createProperty("position", BaseProperty::Access::READ_WRITE, glm::vec2(0.0f));
	createProperty("size", BaseProperty::Access::READ_WRITE, glm::vec2(1.0f));
	createProperty("enable", BaseProperty::Access::READ_WRITE, true);
}

void Widget::reset() {
}

bool Widget::hasProperty(const std::string &property_name) {
	return _properties.find(property_name) != _properties.end();
}

void Widget::addChild(std::shared_ptr<Widget> child) {
	if (child) {
        child->setParent(shared_from_this());
        _children.push_back(child);
    }
}

size_t Widget::getNumberOfChildren() const {
	return _children.size();
}

std::shared_ptr<Widget> Widget::getChild(const std::string &name) {
	auto it = std::find_if(_children.begin(), _children.end(), [&](const std::shared_ptr<Widget> &child) {
        return child->getName() == name;
    });
    if (it != _children.end()) {
        return *it;
    }
    return nullptr;
}

std::shared_ptr<Widget> Widget::findWidget(const std::string &path) {
	size_t pos = path.find('/');
    std::string current = path.substr(0, pos);
    std::string remaining = pos == std::string::npos ? "" : path.substr(pos + 1);

    if (current == _name) {
        if (remaining.empty()) {
            return shared_from_this();
        } else {
            for (auto &child : _children) {
                std::shared_ptr<Widget> found = child->findWidget(remaining);
                if (found) {
                    return found;
                }
            }
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

}