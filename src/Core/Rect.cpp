#include "Rect.hpp"

// Constructors

Rect::Rect() noexcept
    : point(0.0f, 0.0f), size(0.0f, 0.0f) {}

Rect::Rect(const glm::vec2& p1, const glm::vec2& p2) noexcept
    : point(p1), size(p2 - p1) {}

Rect::Rect(glm::vec4& v) noexcept
    : point(v.x, v.y), size(v.z - v.x, v.w - v.y) {}

Rect::Rect(float x1, float y1, float x2, float y2) noexcept
    : point(x1, y1), size(x2 - x1, y2 - y1) {}

Rect::Rect(const Rect& other) noexcept
    : point(other.point), size(other.size) {}

// Getters

glm::vec2 Rect::getCenter() const {
    return point + size * 0.5f;
}

glm::vec2 Rect::getSize() const {
    return size;
}

glm::vec2 Rect::getTopLeft() const {
    return point;
}

glm::vec2 Rect::getTopRight() const {
    return point + glm::vec2(size.x, 0.0f);
}

glm::vec2 Rect::getBottomRight() const {
    return point + size;
}

glm::vec2 Rect::getBottomLeft() const {
    return point + glm::vec2(0.0f, size.y);
}

float Rect::getWidth() const {
    return size.x;
}

float Rect::getHeight() const {
    return size.y;
}

float Rect::getArea() const {
    return size.x * size.y;
}

// Setters

void Rect::setSize(const glm::vec2& newSize) {
    size = newSize;
}

void Rect::setTopLeft(const glm::vec2& topLeft) {
    size += point - topLeft;
    point = topLeft;
}

void Rect::setTopRight(const glm::vec2& topRight) {
    size.x = topRight.x - point.x;
    size.y += point.y - topRight.y;
    point.y = topRight.y;
}

void Rect::setBottomRight(const glm::vec2& bottomRight) {
    size = bottomRight - point;
}

void Rect::setBottomLeft(const glm::vec2& bottomLeft) {
    size.y = bottomLeft.y - point.y;
    size.x += point.x - bottomLeft.x;
    point.x = bottomLeft.x;
}

// Compare

bool Rect::contains(const glm::vec2& pt) const {
    return pt.x >= point.x && pt.x <= point.x + size.x &&
           pt.y >= point.y && pt.y <= point.y + size.y;
}

bool Rect::contains(const Rect& other) const {
    return contains(other.getTopLeft()) && contains(other.getBottomRight());
}

bool Rect::overlaps(const Rect& other) const {
    return point.x < other.point.x + other.size.x && point.x + size.x > other.point.x &&
           point.y < other.point.y + other.size.y && point.y + size.y > other.point.y;
}

// Translate

void Rect::translate(float offset) {
    point.x += offset;
    point.y += offset;
}

void Rect::translate(const glm::vec2& offset) {
    point.x += offset.x;
    point.y += offset.y;
}

void Rect::translateX(float offset) {
    point.x += offset;
}

void Rect::translateY(float offset) {
    point.y += offset;
}

// Scale

void Rect::scale(float factor) {
    size.x *= factor;
    size.y *= factor;
}

void Rect::scale(const glm::vec2& factor) {
    size.x *= factor.x;
    size.y *= factor.y;
}

void Rect::scaleX(float factor) {
    size.x *= factor;
}

void Rect::scaleY(float factor) {
    size.y *= factor;
}

// Operators

Rect& Rect::operator=(const Rect& other) {
    if (this != &other) {
        point = other.point;
        size = other.size;
    }
    return *this;
}

bool Rect::operator==(const Rect& other) const {
    return point == other.point && size == other.size;
}

bool Rect::operator!=(const Rect& other) const {
    return !(*this == other);
}

Rect Rect::operator+(const glm::vec2& offset) const {
    return Rect(point + offset, size);
}

Rect Rect::operator-(const glm::vec2& offset) const {
    return Rect(point - offset, size);
}

Rect Rect::operator*(float factor) const {
    return Rect(point, size * factor);
}

Rect Rect::operator/(float factor) const {
    return Rect(point, size / factor);
}

Rect Rect::operator+(const Rect& other) const {
    return Rect(point + other.point, size + other.size);
}

Rect Rect::operator-(const Rect& other) const {
    return Rect(point - other.point, size - other.size);
}

Rect& Rect::operator+=(const glm::vec2& offset) {
    point.x += offset.x;
    point.y += offset.y;
    return *this;
}

Rect& Rect::operator-=(const glm::vec2& offset) {
    point.x -= offset.x;
    point.y -= offset.y;
    return *this;
}

Rect& Rect::operator*=(float factor) {
    size.x *= factor;
    size.y *= factor;
    return *this;
}

Rect& Rect::operator/=(float factor) {
    size.x /= factor;
    size.y /= factor;
    return *this;
}

Rect& Rect::operator+=(const Rect& other) {
    point.x += other.point.x;
    point.y += other.point.y;
    size.x += other.size.x;
    size.y += other.size.y;
    return *this;
}

Rect& Rect::operator-=(const Rect& other) {
    point.x -= other.point.x;
    point.y -= other.point.y;
    size.x -= other.size.x;
    size.y -= other.size.y;
    return *this;
}
