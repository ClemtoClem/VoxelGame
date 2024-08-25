#include "Panel.hpp"
#include "../Core/Color.hpp"
#include <GL/glew.h>

namespace Render2D {

std::shared_ptr<Panel> Panel::create(const std::string &name, WidgetPtr parent, const glm::vec2 &position, const glm::vec2 &scale, const glm::vec4 &color, const glm::vec4 &border_color, float border_width, float border_radius, const glm::vec4 &hover_color, const glm::vec4 &hover_border_color) {
    auto panel_ptr = std::make_shared<Panel>(name, parent, position, scale, color, border_color, border_width, border_radius, hover_color, hover_border_color);
	panel_ptr->initialize();
	return panel_ptr;
}

Panel::Panel(const std::string &name, WidgetPtr parent,
	const glm::vec2 &position, const glm::vec2 &scale,
	const glm::vec4 &color, const glm::vec4 &border_color, float border_width, float border_radius, const glm::vec4 &hover_color, const glm::vec4 &hover_border_color)
	: Widget(name, parent, position, scale),
	 _color(color), _hover_color(hover_color), _border_color(border_color), _hover_border_color(hover_border_color), _border_width(border_width), _border_radius(border_radius) {
}

Panel::~Panel() {
}

bool Panel::initialize() {
	if (!Widget::initialize()) {
		return false;
	}

	// Define vertices and texture coordinates for a full-screen quad
    GLfloat vertices[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};

    glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);

	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

    return true;
}

/* -------- PROPERTIES ------- */

void Panel::setColor(const glm::vec4 &color)
{
    _color = color;
}

void Panel::setHoverColor(const glm::vec4 &color) {
	_hover_color = color;
}

void Panel::setBorderColor(const glm::vec4 &color) {
	_border_color = color;
}

void Panel::setHoverBorderColor(const glm::vec4 &color) {
	_hover_border_color = color;
}

void Panel::setBorderWidth(float width) {
	_border_width = width;
}

void Panel::setBorderRadius(float radius) {
	_border_radius = radius;
}

const glm::vec4 &Panel::getColor() const {
	return _color;
}

const glm::vec4 &Panel::getHoverColor() const {
	return _hover_color;
}

const glm::vec4 &Panel::getBorderColor() const {
	return _border_color;
}

const glm::vec4 &Panel::getHoverBorderColor() const {
	return _hover_border_color;
}

float Panel::getBorderWidth() const {
	return _border_width;
}

float Panel::getBorderRadius() const {
    return _border_radius;
}

void Panel::handleEvent(SDL_Event& evt) {
	if (!_enabled) return;
	if (evt.type == SDL_MOUSEMOTION) {
		glm::vec2 mouse_pos = glm::vec2(evt.motion.x, evt.motion.y);
		if (containsPoint(mouse_pos)) {
			_is_hovered = true;
		} else {
			_is_hovered = false;
		}
	}
	handleEventChildren(evt);
}

void Panel::update(float dt) {
	if (!_enabled) return;
	updateTransform();
	updateChildren(dt);
}

// Render the panel
void Panel::render(const Shader &shader2D) const {
	if (!_enabled) return;

	// Activate the shader
	shader2D.use();

	// Drawing
	shader2D.setMat4("transform", _transform);

	// Draw rectangle
	/*glm::vec4 color = (_is_hovered) ? _hover_color : _color;
	if (color.a > 0.0f) {
		shader2D.setVec4("color", color);
		glBindVertexArray(_vao);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glBindVertexArray(0);
	}

	// Draw borders lines
	glm::vec4 bdcolor = (_is_hovered) ? _hover_border_color : _border_color;
	if (_border_width > 0 && bdcolor.a > 0.0f) {
		shader2D.setVec4("color", bdcolor);
		glLineWidth(_border_width);
		glBindVertexArray(_vao);
		glDrawArrays(GL_LINE_LOOP, 0, 4);
		glBindVertexArray(0);
	}*/

	// Draw rectangle
	glm::vec4 color = (_is_hovered)? _hover_color : _color;
	if (color.a > 0.0f) {
		shader2D.setVec4("color", color);
		glBegin(GL_QUADS);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, 1.0f);
		glVertex2f(1.0f, 1.0f);
		glVertex2f(1.0f, 0.0f);
		glEnd();
	}

	// Draw borders lines
	glm::vec4 bdcolor = (_is_hovered)? _hover_border_color : _border_color;
	if (_border_width > 0 && bdcolor.a > 0.0f) {
		shader2D.setVec4("color", bdcolor);
		glLineWidth(_border_width);
		glBegin(GL_LINE_LOOP);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, 1.0f);
		glVertex2f(1.0f, 1.0f);
		glVertex2f(1.0f, 0.0f);
		glEnd();
	};
	
	// Render code here, using _color for the panel color
	renderChildren(shader2D);
}


}