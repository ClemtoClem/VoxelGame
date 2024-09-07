#ifndef ECS_BASE_COMPONENTCONTAINER_HPP
#define ECS_BASE_COMPONENTCONTAINER_HPP

#include "ComponentSparseSet.hpp"

namespace ecs {

class BaseComponent;

struct BaseComponentContainer {
    virtual ~BaseComponentContainer() = default;

    virtual BaseComponent& get(ComponentId componentId) = 0;
    virtual void remove(ComponentId componentId) = 0;
};

template<typename T>
struct ComponentContainer : public BaseComponentContainer {
    ComponentSparseSet<T> components;

    BaseComponent& get(ComponentId componentId) override {
        if (!components.has(componentId)) {
            throw std::out_of_range("Component not found.");
        }
        return components.get(componentId);
    }

    void remove(ComponentId componentId) override {
        if (!components.has(componentId)) {
            throw std::out_of_range("Component not found for removal.");
        }
        components.erase(componentId);
    }
};

} // namespace ecs

#endif // ECS_BASE_COMPONENTCONTAINER_HPP
