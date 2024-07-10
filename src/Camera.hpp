/**
 *    ___                               
 *   / __\__ _ _ __ ___   ___ _ __ __ _ 
 *  / /  / _` | '_ ` _ \ / _ \ '__/ _` |
 * / /__| (_| | | | | | |  __/ | | (_| |
 * \____/\__,_|_| |_| |_|\___|_|  \__,_|
 * 
 * @file Camera.hpp
 * @author @ClemtoClem
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
	void processKeyboard(float deltaTime, bool forward, bool backward, bool left, bool right, bool down, bool up);
	void processMouseMovement(float xoffset, float yoffset);
	void processMouseScroll(float yoffset);

	void setPosition(glm::vec3 position);
	glm::vec3 getPosition() const;

	void setMovementSpeed(float movementSpeed);
	float getMovementSpeed() const;

private:
	void updateCameraVectors();

	glm::vec3 _position;
	glm::vec3 _front;
	glm::vec3 _up;
	glm::vec3 _right;
	glm::vec3 _worldUp;

	float _yaw;
	float _pitch;
	float _movementSpeed;
	float _mouseSensitivity;
	float _zoom;
};

#endif // CAMERA_HPP
