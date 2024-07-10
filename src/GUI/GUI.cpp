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
    LOG(Debug) << "GUI::init()";
    _shader2D = std::make_shared<Shader>("./shaders/vertex_shader_2d.glsl", "./shaders/fragment_shader_2d.glsl");
    initRenderData();

    return true;
}

void GUI::reset() {
    _widgets.clear();
}

void GUI::addWidget(std::shared_ptr<Widget> widget) {
    _widgets.push_back(widget);
}

void GUI::handleEvent(SDL_Event& evt) {
    if (evt.type == SDL_WINDOWEVENT) {
        if (evt.window.event == SDL_WINDOWEVENT_RESIZED) {
            setScreenSize(evt.window.data1, evt.window.data2);
        }
    }
    for (auto& widget : _widgets) {
        widget->handleEvent(evt);
    }
}

void GUI::update(float dt) {
    for (auto& widget : _widgets) {
        widget->update(dt);
    }
}

void GUI::render() const {
    glDisable(GL_DEPTH_TEST); // Disable depth testing for 2D rendering

    _shader2D->use();
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(_screenWidth), static_cast<float>(_screenHeight), 0.0f, -1.0f, 1.0f);
    _shader2D->setMat4("projection", projection);

    glBindVertexArray(_vao);
    for (const auto& widget : _widgets) {
        widget->render();
    }
    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST); // Re-enable depth testing
}

void GUI::setScreenSize(int width, int height) {
    _screenWidth = width;
    _screenHeight = height;
}

void GUI::initRenderData() {
    float vertices[] = {
        // positions   // texCoords
        0.0f, 1.0f,    0.0f, 1.0f,
        1.0f, 0.0f,    1.0f, 0.0f,
        0.0f, 0.0f,    0.0f, 0.0f,

        0.0f, 1.0f,    0.0f, 1.0f,
        1.0f, 1.0f,    1.0f, 1.0f,
        1.0f, 0.0f,    1.0f, 0.0f
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
