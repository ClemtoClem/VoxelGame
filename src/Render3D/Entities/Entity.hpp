/**
 *    __      _   _ _         
 *   /__\ __ | |_(_) |_ _   _ 
 *  /_\| '_ \| __| | __| | | |
 * //__| | | | |_| | |_| |_| |
 * \__/|_| |_|\__|_|\__|\__, |
 *                      |___/ 
 * 
 * @file Entity.hpp
 * @author @ClemtoClem (https://github.com/ClemtoClem)
 * @date 09/07/2024
 * @brief Entity class
 */

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <array>
#include <glm/glm.hpp>
#include "../Core/Shader.hpp"

namespace Render3D {

class Entity {
public:
	Entity(const std::string &typeName) : _typeName(typeName) {}

	virtual ~Entity() = default;

	const std::string &getTypeName() const { return _typeName; }

	virtual std::array<glm::vec3, 8> getBoundingBoxCorners() const = 0;

	virtual glm::vec3 &position() = 0;
	virtual const glm::vec3 &position() const = 0;
	virtual void position(const glm::vec3 &point) = 0;
	virtual void position(const float x, const float y, const float z) {
		position(glm::vec3(x, y, z));
	}

	virtual void rotate(float angle, const glm::vec3 &axis) = 0;
	virtual void rotate(float angle, float x, float y, float z) {
		rotate(angle, glm::vec3(x, y, z));
	}

	virtual float &angle() = 0;
	virtual float const &angle() const = 0;
	virtual void angle(float angle) = 0;

	virtual glm::vec3 &rotateAxis() = 0;
	virtual const glm::vec3 &rotateAxis() const = 0;
	virtual void rotateAxis(const glm::vec3 &axis) = 0;

	virtual const glm::mat4 &modelMatrix() const = 0;

	virtual void update(float dt) = 0;
	virtual void render(const Shader &shader) const = 0;

protected:

	std::string _typeName;
};

}

#endif // ENTITY_HPP
