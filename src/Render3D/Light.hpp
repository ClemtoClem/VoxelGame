/**
 *    __ _       _     _   
 *   / /(_) __ _| |__ | |_ 
 *  / / | |/ _` | '_ \| __|
 * / /__| | (_| | | | | |_ 
 * \____/_|\__, |_| |_|\__|
 *         |___/           
 * 
 * @file Light.hpp
 * @author @ClemtoClem (https://github.com/ClemtoClem)
 * @date 13/07/2024
 * @brief Light class
 */

#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "../Core/Shader.hpp"

namespace Render3D {

class Light {
public:
    enum LightType {
        DIRECTIONAL,
        POINT,
        SPOT
    };

    Light();

    // Getters
    LightType getType() const;
    glm::vec3 getPosition() const;
    glm::vec3 getDirection() const;
    glm::vec3 getColor() const;

    float getConstant() const;
    float getLinear() const;
    float getQuadratic() const;
    float getCutOff() const;
    float getOuterCutOff() const;

    // Setters
    void SetDirectionalLight(const glm::vec3 &direction, const glm::vec3 &color);
    void SetPointLight(const glm::vec3 &position, const glm::vec3 &color, float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032f);
    void SetSpotLight(const glm::vec3 &position, const glm::vec3 &direction, const glm::vec3 &color, float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032f, float cutOff = glm::cos(glm::radians(12.5f)), float outerCutOff = glm::cos(glm::radians(15.0f)));

    void setPosition(const glm::vec3 &position);
    void setDirection(const glm::vec3 &direction);
    void setColor(const glm::vec3 &color);

    void setConstant(float constant);
    void setLinear(float linear);
    void setQuadratic(float quadratic);
    void setCutOff(float cutOff);
    void setOuterCutOff(float outerCutOff);

    // Uniform setters
    void setUniforms(Shader &shader, int index = 0) const;

private:
    LightType _type;
    glm::vec3 _position;
    glm::vec3 _direction;
    glm::vec3 _color;

    // Additional properties for point and spot lights
    float _constant;
    float _linear;
    float _quadratic;
    float _cutOff;
    float _outerCutOff;
};

}

#endif // LIGHT_HPP
