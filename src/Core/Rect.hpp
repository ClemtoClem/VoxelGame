#ifndef RECT_HPP
#define RECT_HPP

#include <glm/glm.hpp>

class Rect {
private:
    glm::vec2 point;
    glm::vec2 size;

public:
    Rect() noexcept;
    Rect(const glm::vec2& p1, const glm::vec2& p2) noexcept;
    Rect(glm::vec4 & v) noexcept;
    Rect(float x1, float y1, float x2, float y2) noexcept;
    Rect(const Rect& other) noexcept;

    // Getters

    glm::vec2 getCenter() const;
    glm::vec2 getSize() const;
    glm::vec2 getTopLeft() const;
    glm::vec2 getTopRight() const;
    glm::vec2 getBottomRight() const;
    glm::vec2 getBottomLeft() const;

    float getWidth() const;
    float getHeight() const;
    float getArea() const;

    // Setters

    void setSize(const glm::vec2& size);
    void setTopLeft(const glm::vec2& topLeft);
    void setTopRight(const glm::vec2& topRight);
    void setBottomRight(const glm::vec2& bottomRight);
    void setBottomLeft(const glm::vec2& bottomLeft);

    // Compare

    bool contains(const glm::vec2& point) const;
    bool contains(const Rect& other) const;
    bool overlaps(const Rect& other) const;

    // Translate

    void translate(float offset);
    void translate(const glm::vec2& offset);
    void translateX(float offset);
    void translateY(float offset);

    // Scale

    void scale(float factor);
    void scale(const glm::vec2& factor);
    void scaleX(float factor);
    void scaleY(float factor);

    // Operators

    Rect& operator=(const Rect& other);
    bool operator==(const Rect& other) const;
    bool operator!=(const Rect& other) const;

    Rect operator+(const glm::vec2& offset) const;
    Rect operator-(const glm::vec2& offset) const;
    Rect operator*(float factor) const;
    Rect operator/(float factor) const;

    Rect operator+(const Rect& other) const;
    Rect operator-(const Rect& other) const;

    Rect &operator+=(const glm::vec2& offset);
    Rect &operator-=(const glm::vec2& offset);
    Rect &operator*=(float factor);
    Rect &operator/=(float factor);

    Rect &operator+=(const Rect& other);
    Rect &operator-=(const Rect& other);

};

#endif // RECT_HPP