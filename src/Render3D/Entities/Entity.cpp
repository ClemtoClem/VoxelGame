#include "Entity.hpp"
#include <algorithm>
#include <vector>

namespace Render3D {

inline glm::vec3 getMin(const std::vector<glm::vec3>& corners) {
    glm::vec3 minCorner = corners[0];
    for (const auto& corner : corners) {
        minCorner = glm::min(minCorner, corner);
    }
    return minCorner;
}

inline glm::vec3 getMax(const std::vector<glm::vec3>& corners) {
    glm::vec3 maxCorner = corners[0];
    for (const auto& corner : corners) {
        maxCorner = glm::max(maxCorner, corner);
    }
    return maxCorner;
}

bool Entity::contains(const glm::vec3 &point) const {
    auto corners = getBoundingBoxCorners();
    glm::vec3 minCorner = getMin(corners);
    glm::vec3 maxCorner = getMax(corners);

    return (point.x >= minCorner.x && point.x <= maxCorner.x &&
            point.y >= minCorner.y && point.y <= maxCorner.y &&
            point.z >= minCorner.z && point.z <= maxCorner.z);
}

bool Entity::overlaps(const Entity &other) const {
    auto corners1 = getBoundingBoxCorners();
    auto corners2 = other.getBoundingBoxCorners();

    glm::vec3 minCorner1 = getMin(corners1);
    glm::vec3 maxCorner1 = getMax(corners1);
    glm::vec3 minCorner2 = getMin(corners2);
    glm::vec3 maxCorner2 = getMax(corners2);

    return (minCorner1.x <= maxCorner2.x && maxCorner1.x >= minCorner2.x &&
            minCorner1.y <= maxCorner2.y && maxCorner1.y >= minCorner2.y &&
            minCorner1.z <= maxCorner2.z && maxCorner1.z >= minCorner2.z);
}

bool Entity::contains(const Entity &other) const {
    auto corners = other.getBoundingBoxCorners();
    for (const auto& corner : corners) {
        if (!contains(corner)) {
            return false;
        }
    }
    return true;
}

bool Entity::outOfBounds(const Entity &other) const {
    auto corners = other.getBoundingBoxCorners();
    for (const auto &corner : corners) {
        if (!contains(corner)) {
            return true;
        }
    }
    return false;
}

bool Entity::isAbove(const Entity &other) const {
    return position().y > other.position().y;
}

bool Entity::isBelow(const Entity &other) const {
    return position().y < other.position().y;
}

bool Entity::isLeftOf(const Entity &other) const {
    return position().x < other.position().x;
}

bool Entity::isRightOf(const Entity &other) const {
    return position().x > other.position().x;
}

bool Entity::isFrontOf(const Entity &other) const {
    return position().z > other.position().z;
}

bool Entity::isBehindOf(const Entity &other) const {
    return position().z < other.position().z;
}

} // namespace Render3D
