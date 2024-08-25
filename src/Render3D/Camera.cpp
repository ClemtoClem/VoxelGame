#include "Camera.hpp"
#include "../Core/Utils.hpp"

namespace Render3D {

/// Constructors

Camera::Camera(glm::vec3 position, glm::vec3 worldUp, float yaw, float pitch)
	: _position(position), _worldUp(worldUp), 
	  _zoom(ZOOM), _yaw(yaw), _pitch(pitch),
	  _nearPlane(NEAR_PLANE), _farPlane(FAR_PLANE), 
	  _movementSpeed(MOVEMENT_LOW_SPEED), _movementLowSpeed(MOVEMENT_LOW_SPEED), _movementHighSpeed(MOVEMENT_HIGH_SPEED), 
	  _mouseSensitivity(MOUSE_SENSITIVITY), 
	  _freeMovement(true) {
	updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
	: Camera(glm::vec3(posX, posY, posZ), glm::vec3(upX, upY, upZ), yaw, pitch) {}

// Projections

glm::mat4 Camera::getViewMatrix() const {
	return glm::lookAt(_position, _position + _front, _worldUp);
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const {
	return glm::perspective(glm::radians(_zoom), aspectRatio, 0.1f, 100.0f);
}

// process input

void Camera::processKeyboard(float deltaTime, unsigned int movementFlags) {
	float velocity = _movementSpeed * deltaTime;
	if (movementFlags & Movement::FORWARD)
		_position += _front * velocity;
	if (movementFlags & Movement::BACKWARD)
		_position -= _front * velocity;
	if (movementFlags & Movement::LEFT)
		_position -= _right * velocity;
	if (movementFlags & Movement::RIGHT)
		_position += _right * velocity;
	if (movementFlags & Movement::UP)
		_position += _up * velocity;	 // Déplacement vers le haut
	if (movementFlags & Movement::DOWN)
		_position -= _up * velocity;	 // Déplacement vers le bas
	
	//updateCameraVectors();
}

void Camera::processMouseMovement(float xoffset, float yoffset) {
	xoffset *= _mouseSensitivity;
	yoffset *= _mouseSensitivity;

	_yaw += xoffset;
	_pitch += yoffset;

	if (_pitch > MAX_PITCH)
		_pitch = MAX_PITCH;
	if (_pitch < MIN_PITCH)
		_pitch = MIN_PITCH;

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

// Getters et Setters

// Getters

const glm::vec3& Camera::getPosition() const {
	return _position;
}

const glm::vec3& Camera::getFront() const {
	return _front;
}

const glm::vec3& Camera::getUp() const {
	return _up;
}

const glm::vec3& Camera::getRight() const {
	return _right;
}

const glm::vec3& Camera::getWorldUp() const {
	return _worldUp;
}

float Camera::getZoom() const {
	return _zoom;
}

float Camera::getYaw() const {
	return _yaw;
}

float Camera::getPitch() const {
	return _pitch;
}

float Camera::getNearPlane() const {
	return _nearPlane;
}

float Camera::getFarPlane() const {
	return _farPlane;
}

float Camera::getMovementSpeed() const {
	return _movementSpeed;
}

float Camera::getMovementLowSpeed() const {
	return _movementLowSpeed;
}

float Camera::getMovementHighSpeed() const {
	return _movementHighSpeed;
}

bool Camera::isFreeMovement() const {
	return _freeMovement;
}

// Setters

void Camera::setPosition(float x, float y, float z) {
	_position = glm::vec3(x, y, z);
}

void Camera::setPosition(const glm::vec3 &position) {
	_position = position;
}

void Camera::setZoom(float zoom)
{
    if (zoom >= 1.0f && zoom <= 45.0f)
		_zoom = zoom;
}

void Camera::setYaw(float yaw) {
	_yaw = yaw;
	updateCameraVectors();
}

void Camera::setPitch(float pitch) {
	if (pitch > MAX_PITCH)
		_pitch = MAX_PITCH;
	else if (pitch < MIN_PITCH)
		_pitch = MIN_PITCH;
	else
		_pitch = pitch;

	updateCameraVectors();
}

void Camera::setNearPlane(float nearPlane) {
	_nearPlane = nearPlane;
}

void Camera::setFarPlane(float farPlane) {
	_farPlane = farPlane;
}

void Camera::setMovementSpeed(float movementSpeed) {
	_movementSpeed = movementSpeed;
}

void Camera::setMovementLowSpeed(float movementLowSpeed) {
	_movementLowSpeed = movementLowSpeed;
}

void Camera::setMovementHighSpeed(float movementHighSpeed) {
	_movementHighSpeed = movementHighSpeed;
}

void Camera::setFreeMovement(bool freeMovement) {
	_freeMovement = freeMovement;
}

// Methods for adjusting speed

void Camera::movementSpeedUp() {
	_movementSpeed = _movementHighSpeed;
}

void Camera::movementSpeedDown() {
	_movementSpeed = _movementLowSpeed;
}

// Private methods

void Camera::updateCameraVectors() {
	if (_freeMovement) {
		glm::vec3 front;
		front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		front.y = sin(glm::radians(_pitch));
		front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

		_front = glm::normalize(front);
		_right = glm::normalize(glm::cross(_front, _worldUp));
		_up	= glm::normalize(glm::cross(_right, _front));
	} else {
		
	}
}

}