/**
 *    ___      _       _       __ _       _     _   
 *   / _ \___ (_)_ __ | |_    / /(_) __ _| |__ | |_ 
 *  / /_)/ _ \| | '_ \| __|  / / | |/ _` | '_ \| __|
 * / ___/ (_) | | | | | |_  / /__| | (_| | | | | |_ 
 * \/    \___/|_|_| |_|\__| \____/_|\__, |_| |_|\__|
 *                                  |___/
 * 
 * @file Light.hpp
 * @author @ClemtoClem (https://github.com/ClemtoClem)
 * @date 15/08/2024
 * @brief Inherits light base class
 *        Point light has a position and attenuation constants
 */

#ifndef RENDER3D_POINT_LIGHT_HPP
#define RENDER3D_POINT_LIGHT_HPP

#include "Light.hpp"

namespace Render3D {

class PointLight : public Light {
public:
    PointLight() :
		Light(Light::Type::POINT, glm::vec3(1.0f, 1.0f, 1.0f)), _position(0.0f, 0.0f, 0.0f), _constants(1.0f, 0.0f, 0.0f) {}

    PointLight(const glm::vec3& color, const glm::vec3& position, const glm::vec3& constants) :
        Light(Light::Type::POINT, color), _position(position), _constants(constants) {}

    void setLightUniforms(const Shader &shader, unsigned int id = 0) const override;

	void setPosition(float x, float y, float z) { _position = glm::vec3(x, y, z); }
    void setPosition(const glm::vec3& position) { _position = position; }
	void setConstants(float x, float y, float z) { _constants = glm::vec3(x, y, z); }
    void setConstants(const glm::vec3& constants) { _constants = constants; }

    const glm::vec3& getPosition() const { return _position; }
    const glm::vec3& getConstants() const { return _constants; }

protected:
    glm::vec3 _position;
    glm::vec3 _constants; // x = constant, y = linear, z = quadratic
};

} // namespace Render3D

#endif // RENDER3D_POINT_LIGHT_HPP
