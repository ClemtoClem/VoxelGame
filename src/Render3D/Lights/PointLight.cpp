#include "PointLight.hpp"
#include <string>

#include "PointLight.hpp"

namespace Render3D {

void PointLight::setLightUniforms(const Shader &shader, unsigned int id) const {
    shader.use();
    shader.setBool("pointLights[" + std::to_string(id) + "].enabled", _enabled);
    shader.setVec3("pointLights[" + std::to_string(id) + "].color", _color);
    shader.setVec3("pointLights[" + std::to_string(id) + "].position", _position);
    shader.setVec3("pointLights[" + std::to_string(id) + "].constants", _constants);
}

} // namespace Render3D