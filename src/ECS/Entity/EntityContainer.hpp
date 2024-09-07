#ifndef ECS_ENTITY_ENTITYCONTAINER_HPP
#define ECS_ENTITY_ENTITYCONTAINER_HPP

#include <unordered_map>
#include <unordered_set>
#include "../Base/ComponentId.hpp"
#include "../Base/ComponentType.hpp"
#include "Entity.hpp"
#include "EntitySetType.hpp"
#include "SparseSet.hpp"

namespace ecs {

class EntityData {
    using ComponentIdMap = std::unordered_map<ComponentType, ComponentId>;
    using EntitySetTypeSet = std::unordered_set<EntitySetType>;

public:
    // Components

    template<typename T>
    bool hasComponent() const {
        return findComponent<T>() != mComponentIds.end();
    }

    template<typename ...Ts>
    bool hasComponents() const {
        return (hasComponent<Ts>() && ...);
    }

    template<typename T>
    ComponentId getComponent() const {
        auto it = findComponent<T>();
        if (it != mComponentIds.end()) {
            return it->second;
        }
        throw std::runtime_error("Component not found");
    }

    const ComponentIdMap& getComponents() const {
        return mComponentIds;
    }

    template<typename T>
    void addComponent(ComponentId componentId) {
        mComponentIds[T::Type] = componentId;
    }

    template<typename T>
    ComponentId removeComponent() {
        auto it = findComponent<T>();
        if (it == mComponentIds.end()) {
            throw std::runtime_error("Component not found to remove");
        }
        ComponentId componentId = it->second;
        mComponentIds.erase(it);
        return componentId;
    }

    // Entity sets

    const EntitySetTypeSet& getEntitySets() const {
        return mEntitySetTypes;
    }

    void addEntitySet(EntitySetType entitySetType) {
        mEntitySetTypes.insert(entitySetType);
    }

    void removeEntitySet(EntitySetType entitySetType) {
        mEntitySetTypes.erase(entitySetType);
    }

private:
    ComponentIdMap mComponentIds;
    EntitySetTypeSet mEntitySetTypes;

    template<typename T>
    typename ComponentIdMap::const_iterator findComponent() const {
        return mComponentIds.find(T::Type);
    }
};

using EntityContainer = SparseSet<Entity, EntityData>;

} // namespace ecs

#endif // ECS_ENTITY_ENTITYCONTAINER_HPP
