#ifndef ARCHETYPES_HPP
#define ARCHETYPES_HPP

#include "Manager.hpp"
#include "Components.hpp"

EntityID createCircularObject(std::shared_ptr<Manager> manager, float x, float z, float radius, float vx, float vz, float mass, uint32_t rgba) {
    EntityID entity = manager->createEntity();
    manager->addComponent(entity, "Transform", std::make_unique<TransformComponent>(Vector3D(x,  0.0f, z), Vector3D(0.0f, 0.0f, 0.0f), Vector3D(radius, 0.0f, radius)));
    manager->addComponent(entity, "Mobile",    std::make_unique<MobileComponent>(MobileComponent::DYNAMIC, Vector3D(vx,  0.0f, vz), Vector3D(0.0f, 0.0f, 0.0f), mass));
    manager->addComponent(entity, "Shape",     std::make_unique<ShapeComponent>(ShapeComponent::CIRCLE));
    manager->addComponent(entity, "Color",     std::make_unique<ColorComponent>(rgba)); // 255 for alpha
    return entity;
}

EntityID createCrateObject(std::shared_ptr<Manager> manager, float x, float z, float width, float height, uint32_t background_color, uint32_t border_color) {
    EntityID entity = manager->createEntity();
    manager->addComponent(entity, "Transform", std::make_unique<TransformComponent>(Vector3D(x,  0.0f, z), Vector3D(0.0f, 0.0f, 0.0f), Vector3D(width, 0.0f, height)));
    manager->addComponent(entity, "Mobile",    std::make_unique<MobileComponent>(MobileComponent::STATIC, Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), 0.0f));
    manager->addComponent(entity, "Shape",     std::make_unique<ShapeComponent>(ShapeComponent::CRATE));
    manager->addComponent(entity, "Color",     std::make_unique<ColorComponent>({
        {ColorComponent::Background, background_color},
        {ColorComponent::Border, border_color}
    }));
    return entity;
}

#endif // ARCHETYPES_HPP
