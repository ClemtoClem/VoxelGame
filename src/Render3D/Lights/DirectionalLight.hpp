/**
 *     ___ _               _   _                   _     __ _       _     _   
 *    /   (_)_ __ ___  ___| |_(_) ___  _ __   __ _| |   / /(_) __ _| |__ | |_ 
 *   / /\ / | '__/ _ \/ __| __| |/ _ \| '_ \ / _` | |  / / | |/ _` | '_ \| __|
 *  / /_//| | | |  __/ (__| |_| | (_) | | | | (_| | | / /__| | (_| | | | | |_ 
 * /___,' |_|_|  \___|\___|\__|_|\___/|_| |_|\__,_|_| \____/_|\__, |_| |_|\__|
 *                                                            |___/
 * 
 * @file Light.hpp
 * @author @ClemtoClem (https://github.com/ClemtoClem)
 * @date 15/08/2024
 * @brief Inherits light base class
 *        Directional light has a direction and an ambient factor
 */

#ifndef RENDER3D_DIRECTIONAL_LIGHT_HPP
#define RENDER3D_DIRECTIONAL_LIGHT_HPP

#include "Light.hpp"

namespace Render3D {

class DirectionalLight : public Light {
public:
    DirectionalLight() :
		Light(Light::Type::DIRECTIONAL, glm::vec3(1.0f, 1.0f, 1.0f)), _direction(0.0f, -1.0f, 0.0f), _ambient(0.0f) {}

    DirectionalLight(const glm::vec3& color, const glm::vec3& direction, float ambient = 0.5f) :
        Light(Light::Type::DIRECTIONAL, color), _direction(direction), _ambient(ambient) {}

    void setLightUniforms(const Shader &shader, unsigned int id = 0) const override;

	void setDirection(float x, float y, float z) { _direction = glm::vec3(x, y, z); }
    void setDirection(const glm::vec3& direction) { _direction = direction; }
    void setAmbient(float ambient) { _ambient = ambient; }

    const glm::vec3& getDirection() const { return _direction; }
    float getAmbient() const { return _ambient; }

protected:
    glm::vec3 _direction;
    float _ambient = 0.5f;
};

} // namespace Render3D

#endif // RENDER3D_DIRECTIONAL_LIGHT_HPP
