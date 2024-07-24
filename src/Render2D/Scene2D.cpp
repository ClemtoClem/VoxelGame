#include "Scene2D.hpp"
#include "../Core/Logger.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <SDL2/SDL.h>

namespace Render2D {

Scene2D::Scene2D(const glm::vec2 &screenSize) : _screenSize(screenSize), _enabled(true) {
	_projection = glm::ortho(0.0f, screenSize.x, 0.0f, screenSize.y);
}

Scene2D::~Scene2D() {
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
}

bool Scene2D::init() {	
	_shader2D = std::make_shared<Shader>(PATH_SHADERS_2D + "vertex_shader_2d.glsl", PATH_SHADERS_2D + "fragment_shader_2d.glsl");
	const std::string &err = _shader2D->getError();
	if (!err.empty()) {
		LOG(Error) << err;
		return false;
	}

	initRenderData();

	return true;
}

void Scene2D::initRenderData() {
	static float vertices[] = {
		// positions   // texture coords
		 0.0f,  1.0f,  0.0f, 1.0f,
		 1.0f,  0.0f,  1.0f, 0.0f,
		 0.0f,  0.0f,  0.0f, 0.0f,

		 0.0f,  1.0f,  0.0f, 1.0f,
		 1.0f,  1.0f,  1.0f, 1.0f,
		 1.0f,  0.0f,  1.0f, 0.0f
	};

	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);

	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Scene2D::reset() {
	deleteChilden();
}



void Scene2D::setScreenSize(const glm::vec2 &screenSize) {
	_screenSize = screenSize;
	_projection = glm::ortho(0.0f, screenSize.x, 0.0f, screenSize.y);
}

glm::vec2 Scene2D::getScreenSize() const {
	return _screenSize;
}

glm::mat4 Scene2D::getProjectionMatrix() const {
	return _projection;
}

void Scene2D::disable() {
	_enabled = false;
}

void Scene2D::enable() {
	_enabled = true;
}

bool Scene2D::isEnabled() const {
	return _enabled;
}

void Scene2D::drawRectangle(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color) {
	if (_enabled) {

	}
}

void Scene2D::drawImage(const Texture &texture, const glm::vec2 &position, const glm::vec2 &size) {
	if (_enabled) {

	}
}

void Scene2D::drawText(Font &font, const std::string &text, const glm::vec2 &position, const glm::vec4 &color)
{
}

void Scene2D::addChild(std::shared_ptr<Widget> widget) {
	_children.push_back(widget);
}

void Scene2D::deleteChild(const std::string &name) {
	for (auto it = _children.begin(); it!= _children.end(); ++it) {
		if ((*it)->getName() == name) {
			_children.erase(it);
			return;
		}
	}
}

std::shared_ptr<Widget> Scene2D::getChild(const std::string &name) const {
	for (auto& widget : _children) {
		if (widget->getName() == name) {
			return widget;
		}
	}
	return nullptr;
}

void Scene2D::deleteChilden() {
	_children.clear();
}

void Scene2D::handleEvent(SDL_Event& evt) {
	if (_enabled) {
		if (evt.type == SDL_WINDOWEVENT) {
			if (evt.window.event == SDL_WINDOWEVENT_RESIZED) {
				setScreenSize(glm::vec2(evt.window.data1, evt.window.data2));
			}
		}
		for (auto& widget : _children) {
			widget->handleEvent(evt);
		}
	}
}

void Scene2D::update(float dt) {
	if (_enabled) {
		for (auto& widget : _children) {
			widget->update(dt);
		}
	}
}

void Scene2D::render() const {
	if (_enabled) {
		// Sauvegarder les états OpenGL
		glPushAttrib(GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT | GL_TEXTURE_BIT);

		glDisable(GL_DEPTH_TEST); // Disable depth testing for 2D rendering
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		_shader2D->use();
		glm::mat4 projection = glm::ortho(0.0f, _screenSize.x, _screenSize.y, 0.0f, -1.0f, 1.0f);
		_shader2D->setMat4("projection", projection);

		glBindVertexArray(_vao);
		for (const auto& widget : _children) {
			widget->render(*_shader2D.get());
		}
		glBindVertexArray(0);

		// Restaurer les états OpenGL
		glPopAttrib();
	}
}

}