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

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Render3D {

// Default camera values
const float YAW					= -90.0f;
const float PITCH	   		    =  0.0f;
const float MIN_PITCH			= -89.0f;
const float MAX_PITCH			=  89.0f;
const float ZOOM				=  45.0f;
const float NEAR_PLANE			=  0.1f;
const float FAR_PLANE			=  200.0f;
const float MOVEMENT_LOW_SPEED	=  2.5f;
const float MOVEMENT_HIGH_SPEED	=  10.0f;
const float MOUSE_SENSITIVITY	=  0.1f;


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

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	Camera(float posX, float posY, float posZ, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f, float yaw = YAW, float pitch = PITCH);

// Projections

	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix(float aspectRatio) const;
	
// process input
	
	void processKeyboard(float deltaTime, unsigned int movementFlags);
	void processMouseMovement(float xoffset, float yoffset);
	void processMouseScroll(float yoffset);

// Getters

	const glm::vec3 &getPosition() const;

	const glm::vec3 &getFront() const;
	const glm::vec3 &getUp() const;
	const glm::vec3 &getRight() const;
	const glm::vec3 &getWorldUp() const;

	float getZoom() const;
	float getYaw() const;
	float getPitch() const;
	float getNear() const;
	float getFar() const;
	float getMovementSpeed() const;
	float getMovementLowSpeed() const;
	float getMovementHighSpeed() const;
	bool isFreeMovement() const;

// Setters

	void setPosition(float x, float  y, float  z);
	void setPosition(const glm::vec3 &position);
	void setZoom(float zoom);
	void setYaw(float yaw);
	void setPitch(float pitch);
	void setNearPlane(float nearPlane);
	void setFarPlane(float farPlane);
	void setMovementSpeed(float movementSpeed);
	void setMovementLowSpeed(float movementLowSpeed);
	void setMovementHighSpeed(float movementHighSpeed);
	void setFreeMovement(bool freeMovement);

// Methods for adjusting speed

	void movementSpeedUp();
	void movementSpeedDown();

private:
	void updateCameraVectors();

	glm::vec3 _position;
	glm::vec3 _front;	// Front vector
	glm::vec3 _up;		// camera up
	glm::vec3 _right;	// camera right
	glm::vec3 _worldUp;

	float _zoom;
	float _yaw;
	float _pitch;
	float _nearPlane;
	float _farPlane;

	float _movementSpeed; // current movement speed
	float _movementLowSpeed, _movementHighSpeed;
	float _mouseSensitivity;
	bool _freeMovement;
};

using CameraPtr = std::shared_ptr<Camera>;

}

#endif // CAMERA_HPP
