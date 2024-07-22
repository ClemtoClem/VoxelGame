#ifndef UTILS_HPP
#define UTILS_HPP

#include <algorithm>
#include <stdexcept>
#include <string>
#include <memory>
#include <glm/glm.hpp>

#define AxisX		glm::vec3(1.0f, 0.0f, 0.0f)
#define AxisY		glm::vec3(0.0f, 1.0f, 0.0f)
#define AxisZ		glm::vec3(0.0f, 0.0f, 1.0f)
#define AxisXY		glm::vec3(1.0f, 1.0f, 0.0f)
#define AxisXZ		glm::vec3(1.0f, 0.0f, 1.0f)
#define AxisYZ		glm::vec3(0.0f, 1.0f, 1.0f)
#define AxisXYZ		glm::vec3(1.0f, 1.0f, 1.0f)

template<typename T>
T clamp(T value, T min, T max) {
	return std::min(std::max(value, min), max);
}

template<typename T>
T lerp(T a, T b, float t) {
	return a + (b - a) * t;
}

template<typename T>
T lerp(T a, T b, T c, float t) {
	return lerp(a, b, t) + lerp(b, c, t) * (1.0f - t);
}

template<typename T>
T throwIfNullptr(T value, const std::string &msg) {
	if (value == nullptr) {
		throw std::runtime_error(msg);
	}
	return value;
}

#endif // UTILS_HPP