#include "Scene2D.hpp"
#include "../Core/Logger.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <SDL2/SDL.h>

namespace Render2D {

Scene2D::Scene2D(const glm::vec2 &screenSize) : Node(""), _screenSize(screenSize), _enabled(true) {
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
	LOG(Info) << "Shader 2D loaded";

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

	LOG(Info) << "Scene2D initialized.";
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

void Scene2D::setEnable(bool enable) {
	_enabled = enable;
}

bool Scene2D::isEnabled() const {
	return _enabled;
}

void Scene2D::handleEvent(SDL_Event& evt) {
	if (_enabled) {
		if (evt.type == SDL_WINDOWEVENT) {
			if (evt.window.event == SDL_WINDOWEVENT_RESIZED) {
				setScreenSize(glm::vec2(evt.window.data1, evt.window.data2));
			}
		}
		for (auto child = getFirstChild(); child != nullptr; child = child->getNext()) {
			auto widgetChild = std::dynamic_pointer_cast<Widget>(child);
			if (widgetChild) {
				widgetChild->handleEvent(evt);
			}
		}
	}
}

void Scene2D::update(float dt) {
	if (_enabled) {
		for (auto child = getFirstChild(); child != nullptr; child = child->getNext()) {
			auto widgetChild = std::dynamic_pointer_cast<Widget>(child);
			if (widgetChild) {
				widgetChild->update(dt);
			}
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
		for (auto child = getFirstChild(); child != nullptr; child = child->getNext()) {
			auto widgetChild = std::dynamic_pointer_cast<Widget>(child);
			if (widgetChild) {
				widgetChild->render(*_shader2D.get());
			}
		}
		glBindVertexArray(0);

		// Restaurer les états OpenGL
		glPopAttrib();
	}
}

}