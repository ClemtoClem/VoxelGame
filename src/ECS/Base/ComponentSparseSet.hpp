#ifndef ECS_BASE_COMPONENTSPARSESET_HPP
#define ECS_BASE_COMPONENTSPARSESET_HPP

#include "ComponentId.hpp"
#include "SparseSet.hpp"

namespace ecs {

template<typename T>
using ComponentSparseSet = SparseSet<ComponentId, T>;

} // namespace ecs

#endif // ECS_BASE_COMPONENTSPARSESET_HPP