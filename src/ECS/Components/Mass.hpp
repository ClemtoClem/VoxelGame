#ifndef ECS_COMPONENTS_MASS_HPP
#define ECS_COMPONENTS_MASS_HPP

#include "../Base/Component.hpp"

namespace ecs {

struct Mass : public Component<Mass> {
    float value;

    Mass(float value) : value(value) {}
};

} // namespace ecs

#endif // ECS_COMPONENTS_MASS_HPP