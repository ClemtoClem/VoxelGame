#include "Camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
	: _position(position), _worldUp(up), _yaw(yaw), _pitch(pitch), 
	  _movementSpeed(2.5f), _mouseSensitivity(0.1f), _zoom(45.0f) {
	updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
	return glm::lookAt(_position, _position + _front, _up);
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const {
	return glm::perspective(glm::radians(_zoom), aspectRatio, 0.1f, 100.0f);
}

void Camera::processKeyboard(float deltaTime, bool forward, bool backward, bool left, bool right,  bool down, bool up) {
	float velocity = _movementSpeed * deltaTime;
	if (forward)
		_position += _front * velocity;
	if (backward)
		_position -= _front * velocity;
	if (left)
		_position -= _right * velocity;
	if (right)
		_position += _right * velocity;
	if (up)
        _position += _up * velocity;     // Déplacement vers le haut
    if (down)
        _position -= _up * velocity;     // Déplacement vers le bas
}

void Camera::processMouseMovement(float xoffset, float yoffset) {
	xoffset *= _mouseSensitivity;
	yoffset *= _mouseSensitivity;

	_yaw += xoffset;
	_pitch += yoffset;

	if (_pitch > 89.0f)
		_pitch = 89.0f;
	if (_pitch < -89.0f)
		_pitch = -89.0f;

	updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset) {
	if (_zoom >= 1.0f && _zoom <= 45.0f)
		_zoom -= yoffset;
	if (_zoom <= 1.0f)
		_zoom = 1.0f;
	if (_zoom >= 45.0f)
		_zoom = 45.0f;
}

void Camera::setPosition(glm::vec3 position) {
	_position = position;
}

glm::vec3 Camera::getPosition() const
{
    return _position;
}

void Camera::setMovementSpeed(float movementSpeed) {
	_movementSpeed = movementSpeed;
}

float Camera::getMovementSpeed() const {
    return _movementSpeed;
}

void Camera::updateCameraVectors() {
	glm::vec3 front;
	front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	front.y = sin(glm::radians(_pitch));
	front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_front = glm::normalize(front);
	_right = glm::normalize(glm::cross(_front, _worldUp));
	_up    = glm::normalize(glm::cross(_right, _front));
}