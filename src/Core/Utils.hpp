#ifndef UTILS_HPP
#define UTILS_HPP

#include <algorithm>
#include <stdexcept>
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <cmath>
#include "CustomException.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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
inline T throwIfNullptr(T value, LogLevel lvl, const std::string &msg) {
	if (value == nullptr) {
		THROW_CUSTOM_EXCEPTION(lvl, msg);
	}
	return value;
}

float modulo2Pi(float value);
float modulo360(float value);

/// @brief Transcript GLenum constant
/// @param constant GLenum constant
/// @return string
std::string glErrorToString(GLenum constant);

#endif // UTILS_HPP