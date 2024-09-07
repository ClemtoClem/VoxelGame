#ifndef ECS_BASE_COMPONENT_HPP
#define ECS_BASE_COMPONENT_HPP

#include <memory>
#include <mutex>
#include "ComponentContainer.hpp"
#include "ComponentType.hpp"

namespace ecs {

class BaseComponent {
public:
    static std::size_t getComponentCount() {
        return sFactories.size();
    }

    static std::unique_ptr<BaseComponentContainer> createComponentContainer(std::size_t type) {
        if (type >= sFactories.size()) {
            throw std::out_of_range("Invalid component type.");
        }
        return sFactories[type]();
    }

protected:
    template<typename T>
    static ComponentType generateComponentType() {
        static std::once_flag flag;
        std::call_once(flag, []() {
            sFactories.push_back([]() -> std::unique_ptr<BaseComponentContainer> {
                return std::make_unique<ComponentContainer<T>>();
            });
        });
        return static_cast<ComponentType>(sFactories.size() - 1);
    }

private:
    using ComponentContainerFactory = std::unique_ptr<BaseComponentContainer>(*)();
    static std::vector<ComponentContainerFactory> sFactories;
};

inline std::vector<BaseComponent::ComponentContainerFactory> BaseComponent::sFactories;

template<typename T>
class Component : public BaseComponent {
public:
    static const ComponentType Type;
};

template<typename T>
const ComponentType Component<T>::Type = BaseComponent::generateComponentType<T>();

template<typename T>
constexpr void checkComponentType() {
    static_assert(std::is_base_of_v<Component<T>, T>, "A component of type T must inherit from Component<T>");
}

template<typename ...Ts>
constexpr void checkComponentTypes() {
    (checkComponentType<Ts>(), ...);
}

} // namespace ecs

#endif // ECS_BASE_COMPONENT_HPP
