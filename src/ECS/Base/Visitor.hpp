#ifndef ECS_BASE_VISITOR_HPP
#define ECS_BASE_VISITOR_HPP

#include <functional>
#include <unordered_map>
#include "Component.h"

namespace ecs {

class Visitor {
public:
    Visitor() = default;

    template<typename T, typename Callable>
    void setHandler(Callable&& callable) {
        checkComponentType<T>();
        // Vérification pour éviter d'écraser un handler existant
        if (mHandlers.find(T::Type) != mHandlers.end()) {
            throw std::logic_error("Handler for this component type is already set.");
        }
        mHandlers[T::Type] = [callable = std::forward<Callable>(callable)](BaseComponent& component) {
            callable(static_cast<T&>(component));
        };
    }

    void handle(ComponentType componentType, BaseComponent& component) const {
        auto it = mHandlers.find(componentType);
        if (it != mHandlers.end()) {
            it->second(component);
        } else {
            throw std::runtime_error("No handler for this component type.");
        }
    }

private:
    std::unordered_map<ComponentType, std::function<void(BaseComponent&)>> mHandlers;
};

} // namespace ecs

#endif  // ECS_BASE_VISITOR_HPP
