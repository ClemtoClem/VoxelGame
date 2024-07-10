/**
 *   __      _   _ _         
 *   /__\ __ | |_(_) |_ _   _ 
 *  /_\| '_ \| __| | __| | | |
 * //__| | | | |_| | |_| |_| |
 * \__/|_| |_|\__|_|\__|\__, |
 *                      |___/ 
 * 
 * @file Entity.hpp
 * @author @ClemtoClem
 * @date 09/07/2024
 */

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <array>
#include <glm/glm.hpp>
#include "Shader.hpp"

class Entity {
public:
	virtual ~Entity() = default;

	virtual std::array<glm::vec3, 8> getBoundingBoxCorners() const = 0;

	virtual glm::vec3 &position() = 0;
	virtual void position(const glm::vec3 &point) = 0;
	virtual void position(const float x, const float y, const float z) {
		position(glm::vec3(x, y, z));
	}

	virtual void update(float dt) = 0;
	virtual void render(const Shader &shader) const = 0;
};

#endif // ENTITY_HPP
