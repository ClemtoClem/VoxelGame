#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include "Manager.hpp"
#include "Components.hpp"
#include "SystemBase.hpp"
#include <memory>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

class PhysicsSystem : public SystemBase {
private:
    glm::vec3 gravity;
    Sphere earth;

public:
    PhysicsSystem(std::shared_ptr<Manager> manager, int priority, glm::vec3 gravity = glm::vec3(0.0f, -9.81f, 0.0f),
        glm::vec3 earth_position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 earth_scale = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 earth_rotation = glm::vec3(0.0f, 0.0f, 0.0f))
        : SystemBase(manager, priority), gravity(gravity), earth_position(earth_position), earth_scale(earth_scale), earth_rotation(earth_rotation) {}

    void preUpdate(SDL_Event *event, SDL_Renderer *renderer, float deltaTime) override {
        // No preparation needed before physics update
    }

    void update(SDL_Event *event, SDL_Renderer *renderer, float deltaTime) override {
        // Loop through entities and move them based on velocity
        for (auto& entity : manager->getEntitiesWithComponents({"Transform", "Mobile", "Shape"})) {
            TransformComponent* transform = manager->getComponent<TransformComponent>(entity, "Transform");
            MobileComponent* mobile = manager->getComponent<MobileComponent>(entity, "Mobile");
            ShapeComponent* shape = manager->getComponent<ShapeComponent>(entity, "Shape");

            if (!transform || !mobile || !shape || (mobile->mobileType == MobileComponent::MobileType::STATIC)) continue;

            // Update position based on velocity
            // Modification de l'accélération pour inclure la gravité

            // Calcul de la vélocité en fonction de l'accélération et du temps de la frame

            // calcul de la position en fonction du temps de la frame
            transform->position += mobile->velocity * deltaTime;

            // Résolution de la collision avec la Terre
            resolveCollisionWithPlane(transform->position);
            
        }

        // Check and resolve collisions between entities
        for (auto& entityA : manager->getEntitiesWithComponents({"Transform", "Mobile", "Shape"})) {
            for (auto& entityB : manager->getEntitiesWithComponents({"Transform", "Mobile", "Shape"})) {
                if (entityA == entityB) continue;
                resolveEntityCollision(entityA, entityB);
            }
        }
    }

    void postUpdate(SDL_Event *event, SDL_Renderer *renderer, float deltaTime) override {
        // No post-update logic needed for physics
    }

private:

    void resolveEntityCollision(EntityID entityA, EntityID entityB) {
        TransformComponent* transformA = manager->getComponent<TransformComponent>(entityA, "Transform");
        MobileComponent* mobileA = manager->getComponent<MobileComponent>(entityA, "Mobile");
        ShapeComponent* shapeA = manager->getComponent<ShapeComponent>(entityA, "Shape");

        TransformComponent* transformB = manager->getComponent<TransformComponent>(entityB, "Transform");
        MobileComponent* mobileB = manager->getComponent<MobileComponent>(entityB, "Mobile");
        ShapeComponent* shapeB = manager->getComponent<ShapeComponent>(entityB, "Shape");

        if (!transformA || !mobileA || !shapeA || !transformB || !mobileB || !shapeB) return;

        // Handle collision between a static and a dynamic object
        if (shapeA->shape == ShapeComponent::ShapeType::SPHERE && shapeB->shape == ShapeComponent::ShapeType::SPHERE) {
            resolveSphereSphereCollision(transformA, mobileA, transformB, mobileB);
        } else if (shapeA->shape == ShapeComponent::ShapeType::PARALLEPIPED && shapeB->shape == ShapeComponent::ShapeType::PARALLEPIPED) {
            resolveParallepipedParallepipedCollision(transformA, mobileA, transformB, mobileB);
        } else if (shapeA->shape == ShapeComponent::ShapeType::SPHERE && shapeB->shape == ShapeComponent::ShapeType::PARALLEPIPED) {
            resolveSphereParallepipedCollision(transformA, mobileA, transformB, mobileB);
        } else if (shapeA->shape == ShapeComponent::ShapeType::PARALLEPIPED && shapeB->shape == ShapeComponent::ShapeType::SPHERE) {
            resolveSphereParallepipedCollision(transformB, mobileB, transformA, mobileA);
        }
    }

    void resolveSphereSphereCollision(TransformComponent* transformA, MobileComponent* mobileA, TransformComponent* transformB, MobileComponent* mobileB) {
        float dx = transformB->position.x - transformA->position.x;
        float dy = transformB->position.y - transformA->position.y;
        float dz = transformB->position.z - transformA->position.z;
        float distanceSquared = dx * dx + dy * dy + dz * dz;
        float minDistance = (transformA->scale.x + transformB->scale.x) / 2.0f;  // Supposons que scale.x représente le diamètre

        if (distanceSquared < minDistance * minDistance) {
            float distance = std::sqrt(distanceSquared);
            float nx = dx / distance;
            float ny = dy / distance;

            // Vélocités relatives
            float relativeVelocityX = mobileB->velocity.x - mobileA->velocity.x;
            float relativeVelocityY = mobileB->velocity.y - mobileA->velocity.y;
            float dotProduct = (relativeVelocityX * nx + relativeVelocityY * ny);

            // Calculer l'impulsion
            float impulse = (2 * dotProduct) / (mobileA->mass + mobileB->mass);

            // Mettre à jour les vitesses après collision
            mobileA->velocity.x += impulse * mobileB->mass * nx;
            mobileA->velocity.y += impulse * mobileB->mass * ny;
            mobileB->velocity.x -= impulse * mobileA->mass * nx;
            mobileB->velocity.y -= impulse * mobileA->mass * ny;

            // Corriger l'interpénétration (séparer les entités)
            float overlap = 0.5f * (minDistance - distance);
            transformA->position.x -= overlap * nx;
            transformA->position.y -= overlap * ny;
            transformB->position.x += overlap * nx;
            transformB->position.y += overlap * ny;
        }
    }

    void resolveParallepipedParallepipedCollision(TransformComponent* transformA, MobileComponent* mobileA, TransformComponent* transformB, MobileComponent* mobileB) {
        glm::vec3& posA = transformA->position;
        glm::vec3& sizeA = transformA->scale;  // Largeur et hauteur du rectangle A
        glm::vec3& posB = transformB->position;
        glm::vec3& sizeB = transformB->scale;  // Largeur et hauteur du rectangle B

        if (posA.x < posB.x + sizeB.x && posA.x + sizeA.x > posB.x &&
            posA.y < posB.y + sizeB.y && posA.y + sizeA.y > posB.y) {
            
            // Collision détectée, inverser les vélocités
            mobileA->velocity.x() = -mobileA->velocity.x();
            mobileA->velocity.y() = -mobileA->velocity.y();
            mobileB->velocity.x() = -mobileB->velocity.x();
            mobileB->velocity.y() = -mobileB->velocity.y();

            // Séparer les rectangles
            float overlapX = (sizeA.x + sizeB.x) - std::abs(posA.x - posB.x);
            float overlapY = (sizeA.y + sizeB.y) - std::abs(posA.y - posB.y);

            if (overlapX < overlapY) {
                if (posA.x < posB.x) posA.x -= overlapX / 2.0f;
                else posA.x += overlapX / 2.0f;
            } else {
                if (posA.y < posB.y) posA.y -= overlapY / 2.0f;
                else posA.y += overlapY / 2.0f;
            }
        }
    }

    void resolveSphereParallepipedCollision(TransformComponent* circle, MobileComponent* mobileSphere, TransformComponent* rect, MobileComponent* mobileRect) {
        glm::vec3& circlePos = circle->position;
        glm::vec3& rectPos = rect->position;
        glm::vec3& rectSize = rect->scale;

        float circleRadius = circle->scale.x / 2.0f;  // Supposons que scale.x représente le diamètre

        // Trouver le point le plus proche du cercle sur le rectangle
        float closestX = std::max(rectPos.x, std::min(circlePos.x, rectPos.x + rectSize.x));
        float closestY = std::max(rectPos.y, std::min(circlePos.y, rectPos.y + rectSize.y));

        float dx = circlePos.x - closestX;
        float dy = circlePos.y - closestY;
        float distanceSquared = dx * dx + dy * dy;

        // Si le point le plus proche est à l'intérieur du cercle, il y a collision
        if (distanceSquared < circleRadius * circleRadius) {
            // Inverser les vélocités
            mobileSphere->velocity.x = -mobileSphere->velocity.x;
            mobileSphere->velocity.y = -mobileSphere->velocity.y;

            // Corriger la position du cercle (simple déplacement vers l'extérieur)
            float distance = std::sqrt(distanceSquared);
            float overlap = circleRadius - distance;
            float nx = dx / distance;
            float ny = dy / distance;

            circlePos.x += overlap * nx;
            circlePos.y += overlap * ny;
        }
    }

};

static void getRGBA(uint32_t rgba, uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a) {
    r = (rgba >> 24) & 0xFF;
    g = (rgba >> 16) & 0xFF;
    b = (rgba >> 8) & 0xFF;
    a = rgba & 0xFF;
}

static uint32_t setRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    return (r << 24) | (g << 16) | (b << 8) | a;
}

class RenderSystem : public SystemBase {
public:
    RenderSystem(std::shared_ptr<Manager> manager, int p, uint32_t bgColor = 0) : SystemBase(manager, p), _bgColor(bgColor) {}

    void setBackgroundColor(uint32_t rgba) { _bgColor = rgba; }

    void preUpdate(SDL_Event *event, SDL_Renderer *renderer, float deltaTime) override {
        // Prepare rendering, clear the screen, etc.
        uint8_t r, g, b, a;
        getRGBA(_bgColor, r, g, b, a);
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        SDL_RenderClear(renderer);
    }

    void update(SDL_Event *event, SDL_Renderer *renderer, float deltaTime) override {
        // Render entities that have Transform, Color, and Shape components
        for (const auto& entity : manager->getEntitiesWithComponents({"Transform", "Color", "Shape"})) {
            TransformComponent* transform = manager->getComponent<TransformComponent>(entity, "Transform");
            ColorComponent* color = manager->getComponent<ColorComponent>(entity, "Color");
            ShapeComponent* shape = manager->getComponent<ShapeComponent>(entity, "Shape");

            if (!transform || !color || !shape) continue;
            glm::vec3 pos = transform->getPosition();
            glm::vec3 rot = transform->getRotation();
            glm::vec3 size = transform->getScale();

            switch (shape->shape) {
                case ShapeComponent::CIRCLE:
                    filledSphereColor(renderer, pos.x(), pos.z(), size.x(), color->getColor());
                    break;
                case ShapeComponent::RECTANGLE:
                    boxColor(renderer, pos.x(), pos.z(), pos.x()+size.x()-1, pos.z()+size.z()-1, color->getColor());
                    break;
                case ShapeComponent::CRATE:
                    boxColor(renderer, pos.x(), pos.z(), pos.x()+size.x()-1, pos.z()+size.z()-1, color->getColor(ColorComponent::Background));
                    boxColor(renderer, pos.x(), pos.z(), pos.x()+size.x()-1, pos.z()+4, color->getColor(ColorComponent::Background));
                    boxColor(renderer, pos.x(), pos.z()+size.z()-5, pos.x()+size.x()-1, pos.z()+size.z()-1, color->getColor(ColorComponent::Background));
                    boxColor(renderer, pos.x(), pos.z()+4, pos.x()+4, pos.z()+size.z()-5, color->getColor(ColorComponent::Background));
                    boxColor(renderer, pos.x()+size.x()-5, pos.z()+4, pos.x()+size.x()-1, pos.z()+size.z()-5, color->getColor(ColorComponent::Background));
                    break;
                default:
                    break;
            }
            // Render a filled circle
            //filledSphereColor(renderer, pos, color->getRGBA());
        }
    }

    void postUpdate(SDL_Event *event, SDL_Renderer *renderer, float deltaTime) override {
        // Finish rendering, present the rendered frame
        SDL_RenderPresent(renderer);
    }

private:
    uint32_t _bgColor;
};

#endif // SYSTEMS_HPP
