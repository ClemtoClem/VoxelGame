#ifndef RENDER3D_FRUSTUM_HPP
#define RENDER3D_FRUSTUM_HPP

#include <glm/glm.hpp>
#include <cmath>
#include "Plane.hpp"

namespace Render3D {

struct Frustum {
    Plane rightPlane;
    Plane leftPlane;

    Plane topPlane;
    Plane bottomPlane;

    Plane farPlane;
    Plane nearPlane;

    void CalculatePlanes(const glm::mat4& viewProjMatrix, bool normalize = true) {
        // Left clipping plane
        rightPlane.a = viewProjMatrix[0][3] + viewProjMatrix[0][0];
        rightPlane.b = viewProjMatrix[1][3] + viewProjMatrix[1][0];
        rightPlane.c = viewProjMatrix[2][3] + viewProjMatrix[2][0];
        rightPlane.d = viewProjMatrix[3][3] + viewProjMatrix[3][0];

        // Right clipping plane
        leftPlane.a = viewProjMatrix[0][3] - viewProjMatrix[0][0];
        leftPlane.b = viewProjMatrix[1][3] - viewProjMatrix[1][0];
        leftPlane.c = viewProjMatrix[2][3] - viewProjMatrix[2][0];
        leftPlane.d = viewProjMatrix[3][3] - viewProjMatrix[3][0];

        // Top clipping plane
        topPlane.a = viewProjMatrix[0][3] - viewProjMatrix[0][1];
        topPlane.b = viewProjMatrix[1][3] - viewProjMatrix[1][1];
        topPlane.c = viewProjMatrix[2][3] - viewProjMatrix[2][1];
        topPlane.d = viewProjMatrix[3][3] - viewProjMatrix[3][1];

        // Bottom clipping plane
        bottomPlane.a = viewProjMatrix[0][3] + viewProjMatrix[0][1];
        bottomPlane.b = viewProjMatrix[1][3] + viewProjMatrix[1][1];
        bottomPlane.c = viewProjMatrix[2][3] + viewProjMatrix[2][1];
        bottomPlane.d = viewProjMatrix[3][3] + viewProjMatrix[3][1];

        // Near clipping plane
        nearPlane.a = viewProjMatrix[0][3] + viewProjMatrix[0][2];
        nearPlane.b = viewProjMatrix[1][3] + viewProjMatrix[1][2];
        nearPlane.c = viewProjMatrix[2][3] + viewProjMatrix[2][2];
        nearPlane.a = viewProjMatrix[3][3] + viewProjMatrix[3][2];

        // Far clipping plane
        farPlane.a = viewProjMatrix[0][3] - viewProjMatrix[0][2];
        farPlane.b = viewProjMatrix[1][3] - viewProjMatrix[1][2];
        farPlane.c = viewProjMatrix[2][3] - viewProjMatrix[2][2];
        farPlane.d = viewProjMatrix[3][3] - viewProjMatrix[3][2];

        // Normalize the plane equations, if requested
        if (normalize) {
            rightPlane.Normalize();
            leftPlane.Normalize();
            topPlane.Normalize();
            bottomPlane.Normalize();
            nearPlane.Normalize();
            farPlane.Normalize();
        }
    }

    bool PointIsInside(const glm::vec3& point) const {
        /// Vérifier si le point est devant chaque plan du frustum
        for (const auto& plane : {rightPlane, leftPlane, topPlane, bottomPlane, farPlane, nearPlane}) {
            if (plane.ClassifyPoint(point) == Render3D::Plane::NEGATIVE) {
                // Si le point est derrière un des plans, il est en dehors du frustum
                return false;
            }
        }
        // Si le point est devant tous les plans, il est dans le frustum
        return true;
    }

    bool PointsAreInside(const std::vector<glm::vec3>& points) const {
        for (const auto& point : points) {
            if (!PointIsInside(point)) {
                return false;
            }
        }
        return true;
    }

    bool PointsAreOutside(const std::vector<glm::vec3>& points) const {
        for (const auto& point : points) {
            if (!PointIsInside(point)) {
                return true;
            }
        }
        return false;
    }

    bool LeastOnePointIsInside(const std::vector<glm::vec3>& points) const {
        for (const auto& point : points) {
            if (PointIsInside(point)) {
                return true;
            }
        }
        return false;
    }

};

} // namespace Render3D

#endif // RENDER3D_FRUSTUM_HPP