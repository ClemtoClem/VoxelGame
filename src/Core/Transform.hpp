#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class Transform {
public:
    Transform(const glm::vec3& pos = glm::vec3(0.0f), const glm::vec3& rot = glm::vec3(0.0f), float sc = 1.0f)
        : _position(pos), _eulerRot(rot), _scale(sc), _parent(nullptr), _model(1.0f), _needsUpdate(true) {}

    glm::mat4 getTransformMatrix();
    bool hasChanged() { return _needsUpdate; }

    void translatePosition(const glm::vec3& translation) {
        _position += translation;
        _needsUpdate = true;
    }

    float getScale() const { return _scale; }
    const glm::vec3& getPos() const { return _position; }
    const glm::vec3& getEulerRot() const { return _eulerRot; }
    const glm::quat& getOrientation() const { return _orientation; }
    float* getScalePtr() { return &_scale; }

    void setEulerRot(float x, float y, float z) {
        _oldEulerRot = _eulerRot;
        _eulerRot = glm::vec3(x, y, z);
        _needsUpdate = true;
    }

    void setPos(const glm::vec3& pos) {
        _position = pos;
        _needsUpdate = true;
    }

    void setRot(const glm::quat& rot) {
        _orientation = rot;
        _needsUpdate = true;
    }

    void setScale(float sc) {
        _scale = sc;
        _needsUpdate = true;
    }

    void setParent(Transform* p) {
        _parent = p;
    }

    glm::vec3 getRight() const;
    glm::vec3 getUp() const;
    glm::vec3 getBackward() const;
    glm::vec3 getForward() const;
    glm::vec3 getGlobalScale() const;

private:
    glm::mat4 getMatrix() const;

    glm::vec3 _position;
    glm::quat _orientation;
    glm::vec3 _eulerRot;
    float _scale;

    glm::vec3 _oldPos;
    glm::vec3 _oldEulerRot;
    glm::quat _oldOrientation;
    float _oldScale;

    Transform* _parent;

    glm::mat4 _model;
    bool _needsUpdate;
};

#endif // TRANSFORM_HPP