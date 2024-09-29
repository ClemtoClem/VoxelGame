#ifndef RENDER3D_PLANE_HPP
#define RENDER3D_PLANE_HPP

#include <glm/glm.hpp>
#include <cmath>

namespace Render3D {

struct Plane {
	float a, b, c, d;
	
	enum Halfspace {
		NEGATIVE = -1,
		ON_PLANE = 0,
		POSITIVE = 1,
	};

	void Normalize() {
		float mag;
		mag = std::sqrt(a * a + b * b + c * c);
		a = a / mag;
		b = b / mag;
		c = c / mag;
		d = d / mag;
	}

	float DistanceToPoint(const glm::vec3 &pt) const {
		return a * pt.x + b * pt.y + c * pt.z + d;
	}

	Halfspace ClassifyPoint(const glm::vec3 &pt) const {
		float dist = DistanceToPoint(pt);
		if (dist < 0) {
			return NEGATIVE;
		} else if (dist > 0) {
			return POSITIVE;
		} else {
			return ON_PLANE;
		}
	}
};

} // namespace Render3D

#endif // RENDER3D_PLANE_HPP