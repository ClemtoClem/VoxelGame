#ifndef ECS_COMPONENTS_VELOCITY3D_HPP
#define ECS_COMPONENTS_VELOCITY3D_HPP

#include <glm/glm.hpp>
#include "../Base/Component.hpp"

namespace ecs {

struct Velocity3D : public Component<Velocity3D>, public glm::vec3 {
    Velocity3D(float x = 0.0f, float y = 0.0f, float z = 0.0f) : glm::vec3(x, y, z) {}
};

} // namespace ecs

#endif // ECS_COMPONENTS_VELOCITY3D_HPP