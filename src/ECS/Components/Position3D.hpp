#ifndef ECS_COMPONENTS_POSITION3D_HPP
#define ECS_COMPONENTS_POSITION3D_HPP

#include <glm/glm.hpp>
#include "../Base/Component.hpp"

namespace ecs {

struct Position3D : public Component<Position3D>, public glm::vec3 {
    Position3D(float x = 0.0f, float y = 0.0f, float z = 0.0f) : glm::vec3(x, y, z) {}
};

} // namespace ecs

#endif // ECS_COMPONENTS_POSITION3D_HPP