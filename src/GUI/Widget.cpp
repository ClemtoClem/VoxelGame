#include "Widget.hpp"
#include "Color.hpp"
#include "../Logger.hpp"

Widget::Widget(const std::string &name)
 : _name(name), _position(0.0f, 0.0f), _size(0.0f, 0.0f),
   _color(Color::WHITE), _hoverColor(Color::WHITE), _backgroundColor(Color::BLACK),
   _borderColor(Color::BLACK), _borderWidth(0.0f),
   _isHovered(false), _visible(true), _parent(nullptr) {}

Widget::~Widget() {
	deleteChilden();
}

void Widget::setParent(Widget *parent) {
	LOG(Debug) << "Set parent" << std::endl;
	_parent = parent;
}

Widget *Widget::getParent() const {
	return _parent;
}

void Widget::addChild(std::shared_ptr<Widget> widget) {
	widget->setParent(this);
	_children.push_back(widget);
}

void Widget::deleteChilden() {
	_children.clear();
}

std::shared_ptr<Widget> Widget::getChild(const std::string &name) const {
	for (auto& widget : _children) {
		if (widget->getName() == name) {
			return widget;
		}
	}
	return nullptr;
}

std::vector<std::shared_ptr<Widget>> Widget::getChildren() const {
	return _children;
}

void Widget::deleteChild(const std::string &name) {
	for (auto it = _children.begin(); it!= _children.end(); ++it) {
		if ((*it)->getName() == name) {
			_children.erase(it);
			return;
		}
	}
}

std::string Widget::getName() const {
	return _name;
}

void Widget::setPosition(const glm::vec2& position) {
	_position = position;
}

glm::vec2 Widget::getPosition() const {
	return _position;
}

glm::vec2 Widget::getScreenPosition() const {
	if (_parent) {
		return _parent->getScreenPosition() + _position;
	} else {
		return _position;
	}
}

void Widget::setSize(const glm::vec2& size) {
	_size = size;
}

glm::vec2 Widget::getSize() const {
	return _size;
}

void Widget::setColor(const glm::vec4& color) { 
	_color = color;
}

glm::vec4 Widget::getColor() const {
	return _color;
}

void Widget::setHoverColor(const glm::vec4 &color) {
	_hoverColorIsSet = true;
	_hoverColor = color;
}

glm::vec4 Widget::getHoverColor() const {
	return _hoverColor;
}

void Widget::setBackgroundColor(const glm::vec4& color) {
	_backgroundColor = color;
}

glm::vec4 Widget::getBackgroundColor() const {
	return _backgroundColor;
}

void Widget::setHoverBackgroundColor(const glm::vec4& color) {
	_hoverBackgroundColorIsSet = true;
	_hoverBackgroundColor = color;
}

glm::vec4 Widget::getHoverBackgroundColor() const {
	return _hoverBackgroundColor;
}

void Widget::setBorderColor(const glm::vec4& color) {
	_borderColor = color;
}

glm::vec4 Widget::getBorderColor() const {
	return _borderColor;
}

void Widget::setBorderWidth(float width) {
	_borderWidth = width;
}

float Widget::getBorderWidth() const {
	return _borderWidth;
}

void Widget::setVisible(bool visible) {
	_visible = visible;
}

bool Widget::isVisible() const {
	return _visible;
}

void Widget::disableHoverColor() {
	_hoverColorIsSet = false;
	_hoverBackgroundColorIsSet = false;
}



void Widget::handleEventChildren(SDL_Event &evt) {
	for (auto& widget : _children) {
		widget->handleEvent(evt);
	}
}

void Widget::updateChildren(float dt) {
	for (auto& widget : _children) {
		widget->update(dt);
	}
}

void Widget::renderChildren(const Shader &shader2D) const {
	for (auto& widget : _children) {
		widget->render(shader2D);
	}
}
