#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <SDL2/SDL.h>

#include "Entity.hpp"
#include "ComponentBase.hpp"
#include "SystemBase.hpp"

// System comparison based on priority (lower value = higher priority)
bool compareSystems(const std::unique_ptr<SystemBase>& a, const std::unique_ptr<SystemBase>& b) {
    return a->getPriority() < b->getPriority();
}

// Manager class to handle entities and systems
class Manager {
private:
    EntityID nextEntityID;
    std::unordered_map<EntityID, std::unordered_map<std::string, std::unique_ptr<ComponentBase>>> entities;
    std::vector<std::unique_ptr<SystemBase>> systems;

public:
    Manager() : nextEntityID(0) {}

    // Entity management
    EntityID createEntity() {
        EntityID id = nextEntityID++;
        entities[id] = std::unordered_map<std::string, std::unique_ptr<ComponentBase>>();
        return id;
    }

    void deleteEntity(EntityID entity) {
        entities.erase(entity);
    }

    // Retrieve entities that have all the specified components
    std::vector<EntityID> getEntitiesWithComponents(const std::vector<std::string>& componentTypes) {
        std::vector<EntityID> matchingEntities;
        for (const auto& [entityID, components] : entities) {
            bool allComponentsPresent = true;
            for (const auto& componentType : componentTypes) {
                if (components.find(componentType) == components.end()) {
                    allComponentsPresent = false;
                    break;
                }
            }
            if (allComponentsPresent) {
                matchingEntities.push_back(entityID);
            }
        }
        return matchingEntities;
    }

    template<typename T>
    void addComponent(EntityID entity, const std::string& componentType, std::unique_ptr<T> component) {
        entities[entity][componentType] = std::move(component);
    }

    template<typename T>
    T* getComponent(EntityID entity, const std::string& componentType) {
        auto& components = entities[entity];
        if (components.find(componentType) != components.end()) {
            return dynamic_cast<T*>(components[componentType].get());
        }
        return nullptr;
    }

    // System management
    void addSystem(std::unique_ptr<SystemBase> system) {
        systems.push_back(std::move(system));
        std::sort(systems.begin(), systems.end(), compareSystems);
    }

    void deleteSystem(SystemBase* system) {
        systems.erase(std::remove_if(systems.begin(), systems.end(),
            [system](const std::unique_ptr<SystemBase>& s) { return s.get() == system; }), systems.end());
    }

    void updateSystems(SDL_Event *event, SDL_Renderer *renderer, float deltaTime) {
        for (auto& system : systems) {
            system->preUpdate(event, renderer, deltaTime);
        }
        for (auto& system : systems) {
            system->update(event, renderer, deltaTime);
        }
        for (auto& system : systems) {
            system->postUpdate(event, renderer, deltaTime);
        }
    }
};

#endif // MANAGER_HPP
