#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <iostream>
#include <cstdint>
#include <map>
#include "ComponentBase.hpp"
#include <glm/glm.hpp>

class TransformComponent : public ComponentBase {
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    TransformComponent(glm::vec3 pos = glm::vec3(0, 0, 0), glm::vec3 rot = glm::vec3(0, 0, 0), glm::vec3 sc = glm::vec3(1, 1, 1)) :
        position(pos), rotation(rot), scale(sc) {}

    void setPosition(glm::vec3 pos) {
        position = pos;
    }

    void setRotation(glm::vec3 rot) {
        rotation = rot;
    }

    void setScale(glm::vec3 sc) {
        scale = sc;
    }

    glm::vec3 getPosition() const {
        return position;
    }

    glm::vec3 getRotation() const {
        return rotation;
    }

    glm::vec3 getScale() const {
        return scale;
    }

    void setXPosition(float x) {
        position.x = x;
    }

    void setYPosition(float y) {
        position.y = y;
    }

    void setZPosition(float z) {
        position.z = z;
    }

    float getXPosition() const {
        return position.x;
    }

    float getYPosition() const {
        return position.y;
    }

    float getZPosition() const {
        return position.z;
    }

    void setXRotation(float x) {
        rotation.x = x;
    }

    void setYRotation(float y) {
        rotation.y = y;
    }

    void setZRotation(float z) {
        rotation.z = z;
    }

    float getXRotation() const {
        return rotation.x;
    }

    float getYRotation() const {
        return rotation.y;
    }

    float getZRotation() const {
        return rotation.z;
    }

    void setXScale(float x) {
        scale.x = x;
    }

    void setYScale(float y) {
        scale.y = y;
    }

    void setZScale(float z) {
        scale.z = z;
    }

    float getXScale() const {
        return scale.x;
    }

    float getYScale() const {
        return scale.y;
    }

    float getZScale() const {
        return scale.z;
    }
};

class MobileComponent : public ComponentBase {
public:
    enum MobileType { STATIC, DYNAMIC, MOVABLE };

    MobileType mobileType;
	glm::vec3 velocity;
	glm::vec3 acceleration;
    float mass;

    MobileComponent(MobileType mobileType, glm::vec3 vel = glm::vec3(0, 0, 0), glm::vec3 acc = glm::vec3(0, 0, 0), float mass = 1.0) :
        mobileType(mobileType), velocity(vel), acceleration(acc), mass(mass) {}

    void setVelocity(glm::vec3 vel) {
        velocity = vel;
    }

    void setAcceleration(glm::vec3 acc) {
        acceleration = acc;
    }

    void setMass(float m) {
        mass = m;
    }

    glm::vec3 getVelocity() const {
        return velocity;
    }

    glm::vec3 getAcceleration() const {
        return acceleration;
    }

    float getMass() const {
        return mass;
    }
};

class ShapeComponent : public ComponentBase {
public:
    enum ShapeType {
        SPHERE,
        PARALLEPIPED,
        CYLINDER,
        CONE,
    };
    ShapeType shape;

    ShapeComponent(ShapeType s = SPHERE) : shape(s) {}
};

class ColorComponent : public ComponentBase {
public:
    enum ColorType {
        Background = 0,
        Border = 1,
        Foreground = 2,
        User3 = 3,
        User4 = 4,
        User5 = 5
    };

    std::map<ColorType, uint32_t> colors;

    ColorComponent(uint32_t rgba) : colors({ColorType::Background, rgba}) {}

    ColorComponent(std::map<ColorType, uint32_t> colors) : colors(colors) {}

    void getColor(uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a) {
        uint32_t rgba = colors[ColorType::Background];
        r = (rgba >> 24) & 0xFF;
        g = (rgba >> 16) & 0xFF;
        b = (rgba >>  8) & 0xFF;
        a =  rgba        & 0xFF;
    }

    void getColor(ColorType type, uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a) {
        uint32_t rgba = colors[type];
        r = (rgba >> 24) & 0xFF;
        g = (rgba >> 16) & 0xFF;
        b = (rgba >>  8) & 0xFF;
        a =  rgba        & 0xFF;
    }

    uint32_t getColor(ColorType type = ColorType::Background) {
        return colors[type];
    }

    void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        colors[ColorType::Background] = (r << 24) | (g << 16) | (b << 8) | a;
    }

    void setColor(ColorType type, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        colors[type] = (r << 24) | (g << 16) | (b << 8) | a;
    }

    void setColor(ColorType type, uint32_t rgba) {
        colors[type] = rgba;
    }

    void setColor(uint32_t rgba) {
        colors[ColorType::Background] = rgba;
    }
};

#endif // COMPONENTS_HPP