#include "Widget.hpp"
#include "Color.hpp"
#include "../Logger.hpp"
#include <glm/gtc/matrix_transform.hpp>

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

bool Widget::isHovered() const {
    return _isHovered;
}

void Widget::setAngle(float angle) {
	_angle = angle;
}

float Widget::getAngle() const {
    return _angle;
}

void Widget::setRotation(float rotation) {
	_currentAngle = 0;
	_rotation = rotation;
}

float Widget::getRotation() const {
	return _rotation;
}

void Widget::checkMouseHovered(const glm::vec2 &mouse) {
	// Convert mouse coordinates to the widget's local space
	glm::vec4 mousePosScreenSpace(mouse.x, mouse.y, 0.0f, 1.0f);
	glm::mat4 inverseTransform = glm::inverse(_transform);
	glm::vec4 mousePosLocalSpace = inverseTransform * mousePosScreenSpace;
	
	// The widget's local space origin is (0, 0), size is (_size.x, _size.y)
    float localX = mousePosLocalSpace.x;
	float localY = mousePosLocalSpace.y;

	// Check if the mouse position is within the widget's bounds
	if (localX > 0 && localX < _size.x && localY > 0 && localY < _size.y) {
    	_isHovered = true;
	} else {
		_isHovered = false;
	}
}

void Widget::updateTransform(float dt) {
    // Create transformation matrix and initialize to identity matrix
    _transform = glm::mat4(1.0f);
    
    // Update the current angle based on the rotation speed and delta time
    _currentAngle += glm::radians(_angle) + dt * glm::radians(_rotation);

    // Translate to the widget's position
    _transform = glm::translate(_transform, glm::vec3(_position, 0.0f));

    // Apply the rotation around the center of the widget
    _transform = glm::translate(_transform, glm::vec3(0.5f * _size, 0.0f));
    _transform = glm::rotate(_transform, _currentAngle, glm::vec3(0.0f, 0.0f, 1.0f));
    _transform = glm::translate(_transform, glm::vec3(-0.5f * _size, 0.0f));

    // Scale the widget according to its size
    _transform = glm::scale(_transform, glm::vec3(_size, 1.0f));
}

void Widget::drawRectangle(const glm::vec2 &normalise_pos, const glm::vec2 &normalise_size, const glm::vec4 &color, float borderWidth) const {
    if (color.a > 0.0f) {
		// Set the color
		glColor4f(color.r, color.g, color.b, color.a);

		// Draw the border
		if (borderWidth > 0.0f) {
			glLineWidth(borderWidth);
			glBegin(GL_LINE_LOOP);
			glVertex2f(normalise_pos.x, normalise_pos.y);
			glVertex2f(normalise_pos.x + normalise_size.x, normalise_pos.y);
			glVertex2f(normalise_pos.x + normalise_size.x, normalise_pos.y + normalise_size.y);
			glVertex2f(normalise_pos.x, normalise_pos.y + normalise_size.y);
			glEnd();
		}
	}
}

void Widget::drawFillRectangle(const glm::vec2 &normalise_pos, const glm::vec2 &normalise_size, const glm::vec4 &color) const {
    if (color.a > 0.0f) {
		// Set the color
		glColor4f(color.r, color.g, color.b, color.a);

		// Draw the filled rectangle
		glBegin(GL_QUADS);
		glVertex2f(normalise_pos.x, normalise_pos.y);
		glVertex2f(normalise_pos.x + normalise_size.x, normalise_pos.y);
		glVertex2f(normalise_pos.x + normalise_size.x, normalise_pos.y + normalise_size.y);
		glVertex2f(normalise_pos.x, normalise_pos.y + normalise_size.y);
		glEnd();
	}
}

void Widget::drawLine(const glm::vec2 &normalise_pos1, const glm::vec2 &normalise_pos2, const glm::vec4 &color, float width) const {
    if (color.a > 0.0f) {
		// Set the color
		glColor4f(color.r, color.g, color.b, color.a);

		// Draw the line
		glLineWidth(width);
		glBegin(GL_LINES);
		glVertex2f(normalise_pos1.x, normalise_pos1.y);
		glVertex2f(normalise_pos2.x, normalise_pos2.y);
		glEnd();
	}
}

void Widget::handleEventChildren(SDL_Event &evt)
{
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