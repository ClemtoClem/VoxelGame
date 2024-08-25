#include "Transform.hpp"

glm::mat4 Transform::getTransformMatrix() {
    if (!_needsUpdate) {
        return _model;
    }

    if (_eulerRot != _oldEulerRot) {
        _orientation = glm::quat(glm::radians(_eulerRot));
        _oldEulerRot = _eulerRot;
    }

    _model = glm::translate(glm::mat4(1.0f), _position) *
             glm::mat4_cast(_orientation) *
             glm::scale(glm::mat4(1.0f), glm::vec3(_scale));

    _needsUpdate = false;

    return getMatrix();
}

glm::mat4 Transform::getMatrix() const {
    if (_parent != nullptr) {
        return _parent->getTransformMatrix() * _model;
    } else {
        return _model;
    }
}

glm::vec3 Transform::getRight() const {
    return glm::normalize(glm::cross(getForward(), glm::vec3(0.0f, 1.0f, 0.0f)));
}

glm::vec3 Transform::getUp() const {
    return glm::normalize(glm::cross(getRight(), getBackward()));
}

glm::vec3 Transform::getBackward() const {
    return -1.f * getForward();
}

glm::vec3 Transform::getForward() const {
    return glm::normalize(_orientation * glm::vec3(0.0f, 0.0f, -1.0f));
}

glm::vec3 Transform::getGlobalScale() const {
    return { glm::length(getRight()), glm::length(getUp()), glm::length(getBackward()) };
}
