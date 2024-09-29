#include "SpotLight.hpp"

namespace Render3D {

void SpotLight::setLightUniforms(const Shader &shader, unsigned int id) const {
    shader.use();
    shader.setBool("spotLights[" + std::to_string(id) + "].enabled", isEnabled());
    shader.setVec3("spotLights[" + std::to_string(id) + "].color", getColor());
    shader.setVec3("spotLights[" + std::to_string(id) + "].position", getPosition());
    shader.setVec3("spotLights[" + std::to_string(id) + "].constants", getConstants());
    shader.setVec3("spotLights[" + std::to_string(id) + "].direction", _direction);
    shader.setVec2("spotLights[" + std::to_string(id) + "].radii", _radii);
}

} // namespace Render3D