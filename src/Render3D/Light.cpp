#include "Light.hpp"
#include "../Core/Shader.hpp"

namespace Render3D {

Light::Light() : _type(DIRECTIONAL), _position(glm::vec3(0.0f)), _direction(glm::vec3(0.0f, -1.0f, 0.0f)), _color(glm::vec3(1.0f)), _constant(1.0f), _linear(0.09f), _quadratic(0.032f) {}

Light::LightType Light::getType() const {
	return _type;
}

glm::vec3 Light::getPosition() const {
	return _position;
}

glm::vec3 Light::getDirection() const {
	return _direction;
}

glm::vec3 Light::getColor() const {
	return _color;
}

float Light::getConstant() const {
	return _constant;
}

float Light::getLinear() const {
	return _linear;
}

float Light::getQuadratic() const {
	return _quadratic;
}

float Light::getCutOff() const {
	return _cutOff;
}

float Light::getOuterCutOff() const {
	return _outerCutOff;
}

void Light::SetDirectionalLight(const glm::vec3 &direction, const glm::vec3 &color) {
	_type = DIRECTIONAL;
	_direction = direction;
	_color = color;
}

void Light::SetPointLight(const glm::vec3 &position, const glm::vec3 &color, float constant, float linear, float quadratic) {
	_type = POINT;
	_position = position;
	_color = color;
	_constant = constant;
	_linear = linear;
	_quadratic = quadratic;
}

void Light::SetSpotLight(const glm::vec3 &position, const glm::vec3 &direction, const glm::vec3 &color, float constant, float linear, float quadratic, float cutOff, float outerCutOff) {
	_type = SPOT;
	_position = position;
	_direction = direction;
	_color = color;
	_constant = constant;
	_linear = linear;
	_quadratic = quadratic;
	_cutOff = cutOff;
	_outerCutOff = outerCutOff;
}

void Light::setPosition(const glm::vec3 &position) {
	_position = position;
}

void Light::setDirection(const glm::vec3 &direction) {
	_direction = direction;
}

void Light::setColor(const glm::vec3 &color) {
	_color = color;
}

void Light::setConstant(float constant) {
	_constant = constant;
}

void Light::setLinear(float linear) {
	_linear = linear;
}

void Light::setQuadratic(float quadratic) {
	_quadratic = quadratic;
}

void Light::setCutOff(float cutOff) {
	_cutOff = cutOff;
}

void Light::setOuterCutOff(float outerCutOff) {
	_outerCutOff = outerCutOff;
}

void Light::setUniforms(Shader &shader, int index) const {
	std::string name;
	if (_type == DIRECTIONAL) {
		name = "directionalLight";
		shader.setVec3(name + ".direction", _direction);
		shader.setVec3(name + ".color", _color);
	} else if (_type == POINT) {
		name = "pointLights[" + std::to_string(index) + "]";
		shader.setVec3(name + ".position", _position);
		shader.setVec3(name + ".color", _color);
		shader.setFloat(name + ".constant", _constant);
		shader.setFloat(name + ".linear", _linear);
		shader.setFloat(name + ".quadratic", _quadratic);
	} else if (_type == SPOT) {
		name = "spotLights[" + std::to_string(index) + "]";
		shader.setVec3(name + ".position", _position);
		shader.setVec3(name + ".direction", _direction);
		shader.setVec3(name + ".color", _color);
		shader.setFloat(name + ".cutOff", _cutOff);
		shader.setFloat(name + ".outerCutOff", _outerCutOff);
		shader.setFloat(name + ".constant", _constant);
		shader.setFloat(name + ".linear", _linear);
		shader.setFloat(name + ".quadratic", _quadratic);
	}
}

}