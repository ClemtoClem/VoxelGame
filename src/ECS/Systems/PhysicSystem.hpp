#ifndef ECS_SYSTEMS_PHYSICSYSTEM_HPP
#define ECS_SYSTEMS_PHYSICSYSTEM_HPP

#include "../Entity/EntityManager.hpp"
#include "../Components/Position3D.hpp"
#include "../Components/Velocity3D.hpp"

namespace ecs {

class PhysicsSystem {
public:
    PhysicsSystem(EntityManager& entityManager) : mEntityManager(entityManager) {
        
    }

    void update(float dt) {
        for (auto [entity, components] : mEntityManager.getEntitySet<Position, Velocity>()) {
            auto [position, velocity] = components;
            position.x += velocity.x * dt;
            position.y += velocity.y * dt;
        }
    }

private:
    EntityManager& mEntityManager;
};

} // namespace ecs

#endif // ECS_SYSTEMS_PHYSICSYSTEM_HPP