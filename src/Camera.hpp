/**
 *    ___                               
 *   / __\__ _ _ __ ___   ___ _ __ __ _ 
 *  / /  / _` | '_ ` _ \ / _ \ '__/ _` |
 * / /__| (_| | | | | | |  __/ | | (_| |
 * \____/\__,_|_| |_| |_|\___|_|  \__,_|
 * 
 * @file Camera.hpp
 * @author ClemtoClem
 * @date 09/07/2024
 */

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);

	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix(float aspectRatio) const;
	void processKeyboard(float deltaTime, bool forward, bool backward, bool left, bool right);
	void processMouseMovement(float xoffset, float yoffset);
	void processMouseScroll(float yoffset);

	glm::vec3 getPosition() const;

private:
	void updateCameraVectors();

	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_worldUp;

	float m_yaw;
	float m_pitch;
	float m_movementSpeed;
	float m_mouseSensitivity;
	float m_zoom;
};

#endif // CAMERA_HPP
