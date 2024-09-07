#ifndef ECS_ENTITY_ENTITYSET_HPP
#define ECS_ENTITY_ENTITYSET_HPP

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>
#include <tuple>
#include "../Base/ComponentContainer.hpp"
#include "EntitySetIterator.hpp"
#include "EntitySetType.hpp"
#include "EntityContainer.hpp"

namespace ecs {

template<typename ...Ts>
class EntitySet;

class BaseEntitySet {
public:
    static std::size_t getEntitySetCount() {
        return sFactories.size();
    }

    static std::unique_ptr<BaseEntitySet> createEntitySet(std::size_t type,
        EntityContainer& entities,
        const std::vector<std::unique_ptr<BaseComponentContainer>>& componentContainers,
        std::vector<std::vector<BaseEntitySet*>>& componentToEntitySets) {
        return sFactories[type](entities, componentContainers, componentToEntitySets);
    }

    virtual ~BaseEntitySet() = default;

    bool hasEntity(Entity entity) const {
        return mEntityToIndex.find(entity) != mEntityToIndex.end();
    }

    void onEntityUpdated(Entity entity) {
        bool requirementsSatisfied = satisfyRequirements(entity);
        bool entityManaged = hasEntity(entity);

        if (requirementsSatisfied && !entityManaged) {
            addEntity(entity);
        } else if (!requirementsSatisfied && entityManaged) {
            removeEntity(entity, true);
        }
    }

    void onEntityRemoved(Entity entity) {
        removeEntity(entity, false);
    }

protected:
    virtual bool satisfyRequirements(Entity entity) = 0;
    virtual void addEntity(Entity entity) = 0;
    virtual void removeEntity(Entity entity, bool updateEntity) = 0;

    std::unordered_map<Entity, std::size_t> mEntityToIndex;

    template<typename ...Ts>
    static EntitySetType generateEntitySetType() {
        sFactories.push_back([](EntityContainer& entities,
            const std::vector<std::unique_ptr<BaseComponentContainer>>& componentContainers,
            std::vector<std::vector<BaseEntitySet*>>& componentToEntitySets)
            -> std::unique_ptr<BaseEntitySet>
        {
            auto entitySet = std::make_unique<EntitySet<Ts...>>(entities,
                std::tie(static_cast<ComponentContainer<Ts>*>(componentContainers[Ts::Type].get())->components...));
            (componentToEntitySets[Ts::Type].push_back(entitySet.get()), ...);
            return entitySet;
        });
        return sFactories.size() - 1;
    }

private:
    using EntitySetFactory = std::unique_ptr<BaseEntitySet>(*)(
        EntityContainer&,
        const std::vector<std::unique_ptr<BaseComponentContainer>>&,
        std::vector<std::vector<BaseEntitySet*>>&);

    static std::vector<EntitySetFactory> sFactories;
};

std::vector<BaseEntitySet::EntitySetFactory> BaseEntitySet::sFactories;

template<typename ...Ts>
class EntitySet : public BaseEntitySet
{
    using ValueType = std::pair<Entity, std::array<ComponentId, sizeof...(Ts)>>;
    using UIterator = typename std::vector<ValueType>::iterator;
    using UConstIterator = typename std::vector<ValueType>::const_iterator;
    using ComponentContainers = std::tuple<ComponentSparseSet<Ts>&...>;

public:
    using Iterator = EntitySetIterator<UIterator, Ts...>;
    using ConstIterator = EntitySetIterator<UConstIterator, const Ts...>;
    using ListenerId = uint32_t;
    using EntityAddedListener = std::function<void(Entity)>;
    using EntityRemovedListener = std::function<void(Entity)>;

    static const EntitySetType Type;

    EntitySet(EntityContainer& entities, const ComponentContainers& componentContainers) :
        mEntities(entities), mComponentContainers(componentContainers) {}

    std::size_t getSize() const {
        return mManagedEntities.size();
    }

    Iterator begin() {
        return Iterator(mManagedEntities.begin(), mComponentContainers);
    }

    ConstIterator begin() const {
        return ConstIterator(mManagedEntities.begin(), mComponentContainers);
    }

    Iterator end() {
        return Iterator(mManagedEntities.end(), mComponentContainers);
    }

    ConstIterator end() const {
        return ConstIterator(mManagedEntities.end(), mComponentContainers);
    }

    ListenerId addEntityAddedListener(EntityAddedListener listener) {
        return mEntityAddedListeners.emplace(std::move(listener)).first;
    }

    void removeEntityAddedListener(ListenerId listenerId) {
        mEntityAddedListeners.erase(listenerId);
    }

    ListenerId addEntityRemovedListener(EntityRemovedListener listener) {
        return mEntityRemovedListeners.emplace(std::move(listener)).first;
    }

    void removeEntityRemovedListener(ListenerId listenerId) {
        mEntityRemovedListeners.erase(listenerId);
    }

protected:
    bool satisfyRequirements(Entity entity) override {
        return mEntities.get(entity).template hasComponents<Ts...>();
    }

    void addEntity(Entity entity) override {
        mEntityToIndex[entity] = mManagedEntities.size();
        auto& entityData = mEntities.get(entity);
        entityData.addEntitySet(Type);
        mManagedEntities.emplace_back(entity, std::array<ComponentId, sizeof...(Ts)>{entityData.template getComponent<Ts>()...});

        for (const auto& listener : mEntityAddedListeners.getObjects()) {
            listener(entity);
        }
    }

    void removeEntity(Entity entity, bool updateEntity) override {
        auto it = mEntityToIndex.find(entity);
        if (it != mEntityToIndex.end()) {
            std::size_t index = it->second;
            mEntityToIndex[mManagedEntities.back().first] = index;
            mEntityToIndex.erase(it);

            mManagedEntities[index] = mManagedEntities.back();
            mManagedEntities.pop_back();

            if (updateEntity) {
                mEntities.get(entity).removeEntitySet(Type);
            }

            for (const auto& listener : mEntityRemovedListeners.getObjects()) {
                listener(entity);
            }
        }
    }

private:
    std::vector<ValueType> mManagedEntities;
    EntityContainer& mEntities;
    ComponentContainers mComponentContainers;
    SparseSet<ListenerId, EntityAddedListener> mEntityAddedListeners;
    SparseSet<ListenerId, EntityRemovedListener> mEntityRemovedListeners;
};

template<typename ...Ts>
const EntitySetType EntitySet<Ts...>::Type = BaseEntitySet::generateEntitySetType<Ts...>();

} // namespace ecs

#endif // ECS_ENTITY_ENTITYSET_HPP
