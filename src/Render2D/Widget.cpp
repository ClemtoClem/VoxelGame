#include <glm/gtc/matrix_transform.hpp>
#include "../Core/Color.hpp"
#include "../Core/Logger.hpp"
#include "../Core/Utils.hpp"
#include "Property.hpp"
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

void Widget::initDefaultProperties() {
	createProperty("position", glm::vec2(0.0f, 0.0f), Property::Access::READ_WRITE,
		[this](const Property::Value& value) {
			_position = std::get<glm::vec2>(value);
		},
		[this]() {
			return _position;
		},
		false
	);
	createProperty("size", glm::vec2(1.0f, 1.0f), Property::Access::READ_WRITE,
		[this](const Property::Value& value) {
			setSize(std::get<glm::vec2>(value));
		},
		[this]() {
			return _size;
		},
		false
	);
	createProperty("rotatePoint", glm::vec2(0.5f, 0.5f), Property::Access::READ_WRITE,
		[this](const Property::Value& value) {
			_rotatePoint = std::get<glm::vec2>(value);
		},
		[this]() {
			return _rotatePoint;
		}
	);
	createProperty("angle", 0.0f, Property::Access::READ_WRITE,
		[this](const Property::Value& value) {
			setAngle(std::get<float>(value));
		},
		[this]() {
			return _angle;
		}
	);
	createProperty("center", getCenter(), Property::Access::READ_ONLY, nullptr,
		[this]() {
			return getCenter();
		},
		false
	);
	createProperty("enable", true, Property::Access::READ_WRITE,
		[this](const Property::Value& value) {
			_enable = std::get<bool>(value);
		},
		[this]() {
			return _enable;
		}
	);
}

void Widget::reset() {
	resetProperties();
}

void Widget::createProperty(const std::string &property_name, const Property::Value &default_value, Property::Access access, std::function<void(const Property::Value&)> setterFunction, std::function<Property::Value(void)> getterFunction, bool authorize_reset) {
	if (hasProperty(property_name)) {
		_properties[property_name].setParameters(default_value, access, setterFunction, getterFunction, authorize_reset);
	} else {
		_properties[property_name] = Property(default_value, setterFunction, getterFunction, access);
	}
}

bool Widget::setProperty(const std::string &property_name, const Property::Value &value) {
	if (hasProperty(property_name)) {
		_properties[property_name].setValue(value);
		return true;
	}
	return false;
}

Widget::Value &Widget::getProperty(const std::string &property_name) {
	if (hasProperty(property_name)) {
		return _properties[property_name];
	}
	THROW_CUSTOM_EXCEPTION(Error, "Property not found");
}

bool Widget::hasProperty(const std::string &property_name) {
	return _properties.find(property_name) != _properties.end();
}

bool Widget::resetProperty(const std::string &property_name) {
	if (hasProperty(property_name)) {
		_properties[property_name].reset();
		return true;
	}
	return false;
}

void Widget::resetProperties() {
	for (auto &property : _properties) {
		property.second.reset();
	}
}

void Widget::setPosition(const glm::vec2 &vec) {
	_position = vec;
}

void Widget::setSize(const glm::vec2 &vec) {
	if (vec.x > 0.0f || vec.y > 0.0f) {
		_size = vec;
	}
}

void Widget::setRotatePoint(const glm::vec2 &vec) {
	_rotatePoint = vec;
}

void Widget::setAngle(float degree) {
	_angle = modulo360(degree);
}

void Widget::setEnable(bool state) {
	_enable = state;
}

glm::vec2 Widget::getPosition() const {
	return _position;
}

glm::vec2 Widget::getSize() const {
	return _size;
}

glm::vec2 Widget::getCenter() const {
	return _position + _size * 0.5f;
}

glm::vec2 Widget::getRotatePoint() const {
	return _rotatePoint;
}

float Widget::getAngle() const {
	return _angle;
}

bool Widget::isEnable() const {
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

}