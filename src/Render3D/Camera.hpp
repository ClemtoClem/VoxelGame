/**
 *    ___                               
 *   / __\__ _ _ __ ___   ___ _ __ __ _ 
 *  / /  / _` | '_ ` _ \ / _ \ '__/ _` |
 * / /__| (_| | | | | | |  __/ | | (_| |
 * \____/\__,_|_| |_| |_|\___|_|  \__,_|
 * 
 * @file Camera.hpp
 * @author @ClemtoClem (https://github.com/ClemtoClem)
 * @date 09/07/2024
 * @brief Camera class
 */

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Render3D {

// Default camera values
const float YAW					= -90.0f;
const float PITCH       		=  0.0f;
const float MOVEMENT_LOW_SPEED	=  2.5f;
const float MOVEMENT_HIGH_SPEED	=  10.0f;
const float MOUSE_SENSITIVITY	=  0.1f;
const float ZOOM				=  45.0f;


class Camera {
public:
	enum Movement {
		FORWARD		= 1U,
		BACKWARD	= 2U,
		LEFT		= 4U,
		RIGHT		= 8U,
		UP			= 16U,
		DOWN		= 32U
	};

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	Camera(float posX, float posY, float posZ, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f, float yaw = YAW, float pitch = PITCH);

	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix(float aspectRatio) const;
	void processKeyboard(float deltaTime, unsigned int movementFlags);
	void processMouseMovement(float xoffset, float yoffset);
	void processMouseScroll(float yoffset);

	void setPosition(glm::vec3 position);
	const glm::vec3 &getPosition() const;

	const glm::vec3 &getFront() const;
	const glm::vec3 &getUp() const;
	const glm::vec3 &getRight() const;
	const glm::vec3 &getWorldUp() const;

	void setMovementSpeed(float movementSpeed);
	float getMovementSpeed() const;

	void setMovementLowSpeed(float movementLowSpeed);
	float getMovementLowSpeed() const;

	void setMovementHighSpeed(float movementHighSpeed);
	float getMovementHighSpeed() const;

	void movementSpeedUp();
	void movementSpeedDown();

private:
	void updateCameraVectors();

	glm::vec3 _position;
	glm::vec3 _front;
	glm::vec3 _up;
	glm::vec3 _right;
	glm::vec3 _worldUp;

	float _yaw;
	float _pitch;
	float _movementSpeed, _movementLowSpeed, _movementHighSpeed;
	float _mouseSensitivity;
	float _zoom;
};

}

#endif // CAMERA_HPP
