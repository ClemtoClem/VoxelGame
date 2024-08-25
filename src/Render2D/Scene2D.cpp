#include "Scene2D.hpp"
#include "../Core/Logger.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "../Core/Utils.hpp"

namespace Render2D {

Scene2D::Scene2D(const glm::vec2 &screenSize) : Widget("@", nullptr), _screenSize(screenSize), _enabled(true) {
	_projection = glm::ortho(0.0f, screenSize.x, 0.0f, screenSize.y, -1.0f, 1.0f);
}

Scene2D::~Scene2D() {
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
}

bool Scene2D::initialize() {
	if (!Widget::initialize()) {
		return false;
	}
	_shader2D = std::make_shared<Shader>(PATH_SHADERS_2D + "shader_2d.vert", PATH_SHADERS_2D + "shader_2d.frag");
	const std::string &err = _shader2D->getError();
	if (!err.empty()) {
		LOG(Error) << err;
		return false;
	}
	//LOG(Info) << "Shader 2D loaded";

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

	//LOG(Info) << "Scene 2D initialized";

	return true;
}

void Scene2D::setScale(const glm::vec2 &screenSize) {
	Widget::setScale(screenSize);
	_projection = glm::ortho(0.0f, screenSize.x, 0.0f, screenSize.y, -1.0f, 1.0f);
}

glm::mat4 Scene2D::getProjectionMatrix() const {
	return _projection;
}

void Scene2D::handleEvent(SDL_Event& evt) {
	if (_enabled) {
		if (evt.type == SDL_WINDOWEVENT) {
			if (evt.window.event == SDL_WINDOWEVENT_RESIZED) {
				setScale(glm::vec2(evt.window.data1, evt.window.data2));
			}
		}
		handleEventChildren(evt);
	}
}

void Scene2D::update(float dt) {
	if (_enabled) {
		updateTransform();
		updateChildren(dt);
	}
}

void Scene2D::render() const {
	if (_enabled) {
		// Sauvegarder les états OpenGL
		glPushAttrib(GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT | GL_TEXTURE_BIT | GL_TRANSFORM_BIT | GL_VIEWPORT_BIT);

		glDisable(GL_DEPTH_TEST); // Disable depth testing for 2D rendering
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		_shader2D->use();
		_shader2D->setMat4("projection", _projection);

		glBindVertexArray(_vao);
		renderChildren(*_shader2D.get());
		glBindVertexArray(0);

		// Restaurer les états OpenGL
		glPopAttrib();
	}
}

void Scene2D::render(const Shader &shader2D) const {
	LOG(Warning) << "Scene2D::render(const Shader &shader2D) const is not implemented.";
	render();
}

}
