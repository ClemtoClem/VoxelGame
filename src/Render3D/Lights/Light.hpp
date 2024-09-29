/**
 *    __ _       _     _   
 *   / /(_) __ _| |__ | |_ 
 *  / / | |/ _` | '_ \| __|
 * / /__| | (_| | | | | |_ 
 * \____/_|\__, |_| |_|\__|
 *         |___/		   
 * 
 * @file Light.hpp
 * @author @ClemtoClem (https://github.com/ClemtoClem)
 * @date 15/08/2024
 * @brief Base class for all lights only stores the color
 *        and if light is active.
 */

#ifndef RENDER3D_LIGHT_HPP
#define RENDER3D_LIGHT_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Core/Shader.hpp"
#include <string>

namespace Render3D {

class Light {
public:
	enum Type {
		DIRECTIONAL,
		POINT,
		SPOT
	};

    // Constructor takes color value as vec3
    Light(Type type, const glm::vec3& color) : _type(type), _color(color), _enabled(true) {}

    // Updates the uniforms for the light in a given shader
    virtual void setLightUniforms(const Shader &shader, unsigned int id = 0) const = 0;

    // Setters for color and if light is enabled
	void setColor(float r, float g, float b) { _color = glm::vec3(r, g, b); }
    void setColor(const glm::vec3& color) { _color = color; }

    void setEnabled(bool enabled) { _enabled = enabled; }

    // Getters for color and if light is enabled
	Type getType() const { return _type; }
    const glm::vec3& getColor() const { return _color; }
    bool isEnabled() const { return _enabled; }

    // Toggle if light is enabled
    void toggleEnabled() { _enabled = !_enabled; }

protected:
	Type _type;
    glm::vec3 _color;
    bool _enabled;
};

} // namespace Render3D

#endif // RENDER3D_LIGHT_HPP
