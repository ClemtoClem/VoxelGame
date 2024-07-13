#include "GUI.hpp"
#include "../Logger.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <SDL2/SDL.h>

GUI::GUI() {}

GUI::~GUI() {
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
}

bool GUI::init() {	
	_shader2D = std::make_shared<Shader>("./shaders/vertex_shader_2d.glsl", "./shaders/fragment_shader_2d.glsl");
	const std::string &err = _shader2D->getError();
	if (!err.empty()) {
		LOG(Error) << err;
		return false;
	}

	initRenderData();

	return true;
}

void GUI::addChild(std::shared_ptr<Widget> widget) {
	_children.push_back(widget);
}

void GUI::deleteChild(const std::string &name) {
	for (auto it = _children.begin(); it!= _children.end(); ++it) {
		if ((*it)->getName() == name) {
			_children.erase(it);
			return;
		}
	}
}

std::shared_ptr<Widget> GUI::getChild(const std::string &name) const {
	for (auto& widget : _children) {
		if (widget->getName() == name) {
			return widget;
		}
	}
	return nullptr;
}

void GUI::deleteChilden() {
	_children.clear();
}

void GUI::handleEvent(SDL_Event& evt) {
	if (evt.type == SDL_WINDOWEVENT) {
		if (evt.window.event == SDL_WINDOWEVENT_RESIZED) {
			setScreenSize(evt.window.data1, evt.window.data2);
		}
	}
	for (auto& widget : _children) {
		widget->handleEvent(evt);
	}
}

void GUI::update(float dt) {
	for (auto& widget : _children) {
		widget->update(dt);
	}
}

void GUI::render() const {
	// Sauvegarder les états OpenGL
	glPushAttrib(GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT | GL_TEXTURE_BIT);

	glDisable(GL_DEPTH_TEST); // Disable depth testing for 2D rendering
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	_shader2D->use();
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(_screenWidth), static_cast<float>(_screenHeight), 0.0f, -1.0f, 1.0f);
	_shader2D->setMat4("projection", projection);

	glBindVertexArray(_vao);
	for (const auto& widget : _children) {
		widget->render(*_shader2D.get());
	}
	glBindVertexArray(0);

	// Restaurer les états OpenGL
	glPopAttrib();
}

void GUI::setScreenSize(int width, int height) {
	_screenWidth = width;
	_screenHeight = height;
}

void GUI::initRenderData() {
	float vertices[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};
	unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);

	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}
