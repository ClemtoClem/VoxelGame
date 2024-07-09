#include "Camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
	: m_position(position), m_worldUp(up), m_yaw(yaw), m_pitch(pitch), 
	  m_movementSpeed(2.5f), m_mouseSensitivity(0.1f), m_zoom(45.0f) {
	updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const {
	return glm::perspective(glm::radians(m_zoom), aspectRatio, 0.1f, 100.0f);
}

void Camera::processKeyboard(float deltaTime, bool forward, bool backward, bool left, bool right) {
	float velocity = m_movementSpeed * deltaTime;
	if (forward)
		m_position += m_front * velocity;
	if (backward)
		m_position -= m_front * velocity;
	if (left)
		m_position -= m_right * velocity;
	if (right)
		m_position += m_right * velocity;
}

void Camera::processMouseMovement(float xoffset, float yoffset) {
	xoffset *= m_mouseSensitivity;
	yoffset *= m_mouseSensitivity;

	m_yaw += xoffset;
	m_pitch += yoffset;

	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;

	updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset) {
	if (m_zoom >= 1.0f && m_zoom <= 45.0f)
		m_zoom -= yoffset;
	if (m_zoom <= 1.0f)
		m_zoom = 1.0f;
	if (m_zoom >= 45.0f)
		m_zoom = 45.0f;
}

glm::vec3 Camera::getPosition() const {
	return m_position;
}

void Camera::updateCameraVectors() {
	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(front);
	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}