#include "GUI.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

GUI::GUI() {}

GUI::~GUI() {}

void GUI::reset() {
    _widgets.clear();
}

void GUI::addWidget(std::shared_ptr<Widget> widget) {
    _widgets.push_back(widget);
}

void GUI::handleEvent(SDL_Event& evt) {
    if (evt.type == SDL_WINDOWEVENT) {
        if (evt.window.event == SDL_WINDOWEVENT_RESIZED ||
            evt.window.event == SDL_WINDOWEVENT_SIZE_CHANGED ||
            evt.window.event == SDL_WINDOWEVENT_MAXIMIZED ||
            evt.window.event == SDL_WINDOWEVENT_RESTORED) {
            _screenWidth = evt.window.data1;
            _screenHeight = evt.window.data2;
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
    disableProjection();
    for (const auto& widget : _widgets) {
        widget->render();
    }
    enableProjection();
}

void GUI::disableProjection() const {
    // Configurer OpenGL pour le rendu 2D
    glDisable(GL_DEPTH_TEST);

    glMatrixMode (GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0, _screenWidth, _screenHeight, 0, -1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
}

void GUI::enableProjection() const {
    // Restaurer les états OpenGL
    glMatrixMode(GL_PROJECTION);
        glPopMatrix();

    glMatrixMode (GL_MODELVIEW);
        glPopMatrix();

    glEnable(GL_DEPTH_TEST);
}
