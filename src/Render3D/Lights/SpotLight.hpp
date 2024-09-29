/**
 *  __             _       __ _       _     _   
 * / _\_ __   ___ | |_    / /(_) __ _| |__ | |_ 
 * \ \| '_ \ / _ \| __|  / / | |/ _` | '_ \| __|
 * _\ \ |_) | (_) | |_  / /__| | (_| | | | | |_ 
 * \__/ .__/ \___/ \__| \____/_|\__, |_| |_|\__|
 *    |_|                       |___/
 * 
 * @file Light.hpp
 * @author @ClemtoClem (https://github.com/ClemtoClem)
 * @date 15/08/2024
 * @brief Inherits point light class
 *        Point light has a position and attenuation constants.
 *        Spot light has additional direction and radii
 */

#ifndef RENDER3D_SPOT_LIGHT_HPP
#define RENDER3D_SPOT_LIGHT_HPP

#include "PointLight.hpp"

namespace Render3D {

class SpotLight : public PointLight {
public:
    SpotLight() :
		PointLight(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)), 
        _direction(0.0f, 0.0f, 0.0f), _radii(0.0f, 0.0f) {
			_type = Light::Type::SPOT;
		}

    SpotLight(const glm::vec3& color, const glm::vec3& position, const glm::vec3& constants,
              const glm::vec3& direction, const glm::vec2& radii) :
        PointLight(color, position, constants), _direction(direction), _radii(radii) {
			_type = Light::Type::SPOT;
		}

    void setLightUniforms(const Shader &shader, unsigned int id = 0) const override;

	void setDirection(float x, float y, float z) { _direction = glm::vec3(x, y, z); }
    void setDirection(const glm::vec3& direction) { _direction = direction; }
	void setRadii(float x, float y) { _radii = glm::vec2(x, y); }
    void setRadii(const glm::vec2& radii) { _radii = radii; }

    const glm::vec3& getDirection() const { return _direction; }
    const glm::vec2& getRadii() const { return _radii; }

protected:
    glm::vec3 _direction;
    glm::vec2 _radii; // x = inner radius, y = outer radius
};

} // namespace Render3D

#endif // RENDER3D_SPOT_LIGHT_HPP
