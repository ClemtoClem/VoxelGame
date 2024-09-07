#ifndef ECS_COMPONENTS_SIZE3D_HPP
#define ECS_COMPONENTS_SIZE3D_HPP

#include <glm/glm.hpp>
#include "../Base/Component.hpp"

namespace ecs {

struct Size3D : public Component<Size3D>, public glm::vec3 {
    Size3D(float x = 0.0f, float y = 0.0f, float z = 0.0f) : glm::vec3(x, y, z) {}
};

} // namespace ecs

#endif // ECS_COMPONENTS_SIZE3D_HPP