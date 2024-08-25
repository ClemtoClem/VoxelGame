#include "DirectionalLight.hpp"

namespace Render3D {

void DirectionalLight::setLightUniforms(const Shader &shader, unsigned int id) const {
    shader.use();
    shader.setBool("directionalLight.enabled", _enabled);
    shader.setVec3("directionalLight.color", _color);
    shader.setVec3("directionalLight.direction", _direction);
    shader.setFloat("directionalLight.ambient", _ambient);
}

} // namespace Render3D